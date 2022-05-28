/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "font/glyphs_manager.h"
#include "font/ui_font_builder.h"
#include "gfx_utils/file.h"
#include "gfx_utils/graphic_log.h"
#include "securec.h"

namespace OHOS {
GlyphsManager::GlyphsManager()
    : binHeader_{{0}},
      fontNum_(0),
      start_(0),
      fontHeaderSectionStart_(0),
      fontIndexSectionStart_(0),
      glyphNodeSectionStart_(0),
      bitMapSectionStart_(0),
      ramAddr_(nullptr),
      ramUsedLen_(0),
      fontHeaderCache_(nullptr),
      indexCache_(nullptr),
      nodeCache_(nullptr),
      cacheStatus_(nullptr),
      fp_(-1),
      isRamSet_(false),
      isFileSet_(false)
{
}
GlyphsManager::~GlyphsManager() {}

int8_t GlyphsManager::GlyphNodeCacheInit()
{
    uint32_t size = 0;
    for (int32_t i = 0; i < fontNum_; i++) {
        size += fontHeaderCache_[i].indexLen;
    }

    indexCache_ = ramAddr_ + ramUsedLen_;
    ramUsedLen_ += size;
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);

    int32_t ret = read(fp_, indexCache_, size);
    if (ret != static_cast<int32_t>(size)) {
        GRAPHIC_LOGE("GlyphsManager::GlyphNodeCacheInit read failed");
        return INVALID_RET_VALUE;
    }

    cacheStatus_ = reinterpret_cast<CacheState*>(ramAddr_ + ramUsedLen_);
    ramUsedLen_ += sizeof(CacheState);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);
    for (int32_t font = 0; font < FONT_HASH_NR; font++) {
        for (int32_t uc = 0; uc < UNICODE_HASH_NR; uc++) {
            (*cacheStatus_)[font][uc] = 0;
        }
    }

    nodeCache_ = reinterpret_cast<CacheType*>(ramAddr_ + ramUsedLen_);
    ramUsedLen_ += sizeof(CacheType);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);
    for (int32_t font = 0; font < FONT_HASH_NR; font++) {
        for (int32_t uc = 0; uc < UNICODE_HASH_NR; uc++) {
            for (int32_t node = 0; node < NODE_HASH_NR; node++) {
                (*nodeCache_)[font][uc][node].unicode = 0;
            }
        }
    }

    return RET_VALUE_OK;
}

GlyphNode* GlyphsManager::GetNodeFromCache(uint32_t unicode, uint8_t fontId)
{
    GlyphNode* node = nullptr;

    uint8_t font = fontId & FONT_HASH_MASK;
    uint8_t uc = unicode & UNICODE_HASH_MASK;
    for (uint8_t i = 0; i < NODE_HASH_NR; i++) {
        GlyphNode* p = &((*nodeCache_)[font][uc][i]);
        if ((p->unicode == unicode) && (p->fontId == fontId)) {
            node = p;
            break;
        }
    }
    return node;
}

GlyphNode* GlyphsManager::GetNodeCacheSpace(uint32_t unicode, uint8_t fontId)
{
    uint8_t font, uc, i;
    GlyphNode* node = nullptr;

    font = fontId & FONT_HASH_MASK;
    uc = unicode & UNICODE_HASH_MASK;
    i = (*cacheStatus_)[font][uc];
    node = &((*nodeCache_)[font][uc][i]);

    i++;
    if (i >= NODE_HASH_NR) {
        i = 0;
    }
    (*cacheStatus_)[font][uc] = i;

    return node;
}

GlyphNode* GlyphsManager::GetNodeFromFile(uint32_t unicode, uint8_t fontId)
{
    uint16_t idx = 0;
    uint8_t key;
    uint32_t offset;
    GlyphInfo glyphInfo;
    int8_t result = GetGlyphInfo(fontId, glyphInfo);
    if (result != RET_VALUE_OK) {
        return nullptr;
    }
    for (int32_t i = RADIX_SHIFT_START; i >= 0; i -= RADIX_TREE_BITS) {
        offset = idx * sizeof(IndexNode);
        key = static_cast<uint8_t>((unicode >> static_cast<uint8_t>(i)) & RADIX_TREE_MASK);
        offset += key * sizeof(uint16_t);
        idx = *(reinterpret_cast<uint16_t*>(glyphInfo.indexCache + offset));
        if (idx == 0) {
            return nullptr;
        }
    }

    offset = glyphInfo.glyphNodeSectionStart + (idx - 1) * sizeof(GlyphNode);
    int32_t ret = lseek(fp_, offset, SEEK_SET);
    if (ret != static_cast<int32_t>(offset)) {
        GRAPHIC_LOGE("GlyphsManager::GetNodeFromFile lseek failed");
        return nullptr;
    }
    GlyphNode* node = GetNodeCacheSpace(unicode, fontId);
    ret = read(fp_, node, sizeof(GlyphNode));
    if (ret < 0) {
        GRAPHIC_LOGE("GlyphsManager::GetNodeFromFile read failed");
        return nullptr;
    }

    return node;
}

void GlyphsManager::SetRamBuffer(uintptr_t ramAddr)
{
    ramAddr_ = reinterpret_cast<uint8_t*>(ramAddr);
    isRamSet_ = true;
}

int8_t GlyphsManager::SetFile(int32_t fp, uint32_t start)
{
    if (!isRamSet_) {
        GRAPHIC_LOGE("GlyphsManager::SetFile Ram not set");
        return INVALID_RET_VALUE;
    }

    fp_ = fp;
    start_ = start;
    int32_t ret = lseek(fp_, start_, SEEK_SET);
    if (ret < 0) {
        GRAPHIC_LOGE("GlyphsManager::SetFile lseek failed");
        return INVALID_RET_VALUE;
    }
    ret = read(fp_, &binHeader_, sizeof(binHeader_));
    if (ret != sizeof(binHeader_)) {
        GRAPHIC_LOGE("GlyphsManager::SetFile read failed");
        return INVALID_RET_VALUE;
    }
    if (strncmp(binHeader_.fontMagic, FONT_MAGIC_NUMBER, FONT_MAGIC_NUM_LEN) != 0) {
        return INVALID_RET_VALUE;
    }
    if (binHeader_.fontNum > UIFontBuilder::GetInstance()->GetBitmapFontIdMax()) {
        GRAPHIC_LOGE("GlyphsManager::SetFile data error, fontNum need less than max fontId");
        return INVALID_RET_VALUE;
    }

    fontNum_ = binHeader_.fontNum;
    fontHeaderSectionStart_ = start_ + sizeof(binHeader_);
    int32_t size = sizeof(FontHeader) * fontNum_;
    fontIndexSectionStart_ = fontHeaderSectionStart_ + size;

    fontHeaderCache_ = reinterpret_cast<FontHeader*>(ramAddr_);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(size, 2);

    ret = read(fp_, fontHeaderCache_, size);
    if (ret != size) {
        GRAPHIC_LOGE("GlyphsManager::SetFile read failed");
        return INVALID_RET_VALUE;
    }

    FontHeader* last = fontHeaderCache_ + fontNum_ - 1;
    size = last->indexOffset + last->indexLen;
    glyphNodeSectionStart_ = fontIndexSectionStart_ + size;

    size = 0;
    for (uint32_t i = 0; i < fontNum_; i++) {
        size += fontHeaderCache_[i].glyphNum * sizeof(GlyphNode);
    }
    bitMapSectionStart_ = glyphNodeSectionStart_ + size;
    ret = GlyphNodeCacheInit();
    if (ret == RET_VALUE_OK) {
        isFileSet_ = true;
    }

    return ret;
}

int8_t GlyphsManager::GetGlyphInfo(uint8_t fontId, GlyphInfo& glyphInfo)
{
    uint16_t fontIdx = 0;
    if (fontId > UIFontBuilder::GetInstance()->GetBitmapFontIdMax()) {
        GRAPHIC_LOGE("GlyphsManager::GetGlyphInfo fontId need less than max fontId");
        return INVALID_RET_VALUE;
    }

    if (!isFileSet_) {
        GRAPHIC_LOGE("GlyphsManager::GetGlyphInfo file not set");
        return INVALID_RET_VALUE;
    }

    int32_t low = 0;
    int32_t high = binHeader_.fontNum - 1;
    bool found = false;

    while (low <= high) {
        int32_t mid = (low + high) / 2; // 2 means half
        if (fontHeaderCache_[mid].fontId == fontId) {
            fontIdx = mid;
            found = true;
            break;
        } else if (fontHeaderCache_[mid].fontId > fontId) {
            high = mid - 1;
        } else if (fontHeaderCache_[mid].fontId < fontId) {
            low = mid + 1;
        }
    }
    if (!found) {
        glyphInfo.fontHeader = nullptr;
        glyphInfo.fontId = UIFontBuilder::GetInstance()->GetBitmapFontIdMax();
        return INVALID_RET_VALUE;
    }

    uint32_t size = 0;
    glyphInfo.fontId = fontId;
    glyphInfo.fontHeader = fontHeaderCache_ + fontIdx;
    glyphInfo.fontIndexSectionStart = fontIndexSectionStart_ + glyphInfo.fontHeader->indexOffset;
    for (uint32_t i = 0; i < fontIdx; i++) {
        size += fontHeaderCache_[i].glyphNum * sizeof(GlyphNode);
    }
    glyphInfo.glyphNodeSectionStart = glyphNodeSectionStart_ + size;
    glyphInfo.bitMapSectionStart = bitMapSectionStart_ + glyphInfo.fontHeader->glyphOffset;
    glyphInfo.indexCache = indexCache_ + glyphInfo.fontHeader->indexOffset;

    return RET_VALUE_OK;
}

int32_t GlyphsManager::GetRamUsedLen() const
{
    if (!isFileSet_) {
        GRAPHIC_LOGE("GlyphsManager::GetRamUsedLen file not set");
        return INVALID_RET_VALUE;
    }
    return ramUsedLen_;
}

int8_t GlyphsManager::GetFontVersion(char* version, uint8_t len) const
{
    if (!isFileSet_ || (version == nullptr) || (len > FONT_VERSION_LEN)) {
        GRAPHIC_LOGE("GlyphsManager::GetFontVersion invalid parameters");
        return INVALID_RET_VALUE;
    }
    if (memset_s(version, len, 0, len) != EOK) {
        GRAPHIC_LOGE("GlyphsManager::GetFontVersion memset_s failed");
        return INVALID_RET_VALUE;
    }
    if (strcpy_s(version, len, binHeader_.fontVersion) != EOK) {
        GRAPHIC_LOGE("GlyphsManager::GetFontVersion strcpy_s failed");
        return INVALID_RET_VALUE;
    }
    return RET_VALUE_OK;
}

const FontHeader* GlyphsManager::GetFontHeader(uint8_t fontId)
{
    GlyphInfo glyphInfo;
    int8_t ret = GetGlyphInfo(fontId, glyphInfo);
    if (ret != RET_VALUE_OK) {
        return nullptr;
    }

    return glyphInfo.fontHeader;
}

const GlyphNode* GlyphsManager::GetGlyphNode(uint32_t unicode, uint8_t fontId)
{
    GlyphInfo glyphInfo;
    int8_t ret = GetGlyphInfo(fontId, glyphInfo);
    if (ret != RET_VALUE_OK) {
        return nullptr;
    }
    GlyphNode* node = GetNodeFromCache(unicode, fontId);
    if (node == nullptr) {
        node = GetNodeFromFile(unicode, fontId);
        if (node != nullptr) {
            node->fontId = fontId;
        }
    }
    return node;
}

int16_t GlyphsManager::GetFontHeight(uint8_t fontId)
{
    GlyphInfo glyphInfo;
    int8_t ret = GetGlyphInfo(fontId, glyphInfo);
    if (ret != RET_VALUE_OK) {
        return INVALID_RET_VALUE;
    }

    return glyphInfo.fontHeader->fontHeight;
}

int16_t GlyphsManager::GetFontWidth(uint32_t unicode, uint8_t fontId)
{
    const GlyphNode* node = GetGlyphNode(unicode, fontId);
    if (node == nullptr) {
        return INVALID_RET_VALUE;
    }
    return node->advance;
}

int8_t GlyphsManager::GetBitmap(uint32_t unicode, uint8_t* bitmap, uint8_t fontId)
{
    if (bitmap == nullptr) {
        GRAPHIC_LOGE("GlyphsManager::GetBitmap invalid parameter");
        return INVALID_RET_VALUE;
    }

    GlyphInfo glyphInfo;
    int8_t result = GetGlyphInfo(fontId, glyphInfo);
    if (result != RET_VALUE_OK) {
        return INVALID_RET_VALUE;
    }
    GlyphNode* node = const_cast<GlyphNode*>(GetGlyphNode(unicode, fontId));
    uint32_t tmpBitMapSectionStart = glyphInfo.bitMapSectionStart;
    if (node == nullptr) {
        GRAPHIC_LOGE("GlyphsManager::GetBitmap node not found");
        return INVALID_RET_VALUE;
    }
    uint32_t offset = tmpBitMapSectionStart + node->dataOff;
    uint32_t size = node->kernOff - node->dataOff;
    int32_t ret = lseek(fp_, offset, SEEK_SET);
    if (ret != static_cast<int32_t>(offset)) {
        GRAPHIC_LOGE("GlyphsManager::GetBitmap lseek failed");
        return INVALID_RET_VALUE;
    }

    int32_t readSize = read(fp_, bitmap, size);
    if (readSize != static_cast<int32_t>(size)) {
        GRAPHIC_LOGE("GlyphsManager::GetBitmap read failed");
        return INVALID_RET_VALUE;
    }

    node->dataFlag = fontId;
    return RET_VALUE_OK;
}
} // namespace OHOS
