/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "font/glyphs_cache.h"
#include "font/font_ram_allocator.h"
#include "font/ui_font_builder.h"
#include "gfx_utils/graphic_log.h"
#include "securec.h"

namespace OHOS {
GlyphsCache::GlyphsCache()
    : nodeCache_(nullptr),
      cacheStatus_(nullptr),
      hasInit_(false)
{
}
GlyphsCache::~GlyphsCache() {}

int8_t GlyphsCache::CacheInit()
{
    if (hasInit_) {
        return RET_VALUE_OK;
    }

    cacheStatus_ = reinterpret_cast<CacheState*>(FontRamAllocator::GetInstance().DynamicAllocate(sizeof(CacheState)));
    if (cacheStatus_ == nullptr) {
        GRAPHIC_LOGE("GlyphsCache::CacheInit allocate cache status failed");
        return INVALID_RET_VALUE;
    }

    if (memset_s(cacheStatus_, sizeof(CacheState), 0, sizeof(CacheState)) != EOK) {
        GRAPHIC_LOGE("GlyphsCache::CacheInit init cache status failed");
        return INVALID_RET_VALUE;
    }

    nodeCache_ = reinterpret_cast<CacheType*>(FontRamAllocator::GetInstance().DynamicAllocate(sizeof(CacheType)));
    if (nodeCache_ == nullptr) {
        GRAPHIC_LOGE("GlyphsCache::CacheInit allocate node cache failed");
        return INVALID_RET_VALUE;
    }

    if (memset_s(nodeCache_, sizeof(CacheType), 0, sizeof(CacheType)) != EOK) {
        GRAPHIC_LOGE("GlyphsCache::CacheInit init node cache failed");
        return INVALID_RET_VALUE;
    }

    hasInit_ = true;
    return RET_VALUE_OK;
}

void GlyphsCache::ClearCacheFlag()
{
    hasInit_ = false;
}

GlyphCacheNode* GlyphsCache::GetNodeFromCache(uint32_t unicode, uint16_t fontKey, uint16_t cacheType)
{
    if (!hasInit_) {
        return nullptr;
    }

    GlyphCacheNode* node = nullptr;

    uint8_t font = (fontKey ^ unicode) & FONT_HASH_MASK;
    uint8_t uc = unicode & UNICODE_HASH_MASK;
    for (uint8_t i = 0; i < NODE_HASH_NR; i++) {
        GlyphCacheNode* p = &((*nodeCache_)[font][uc][i]);
        if ((p->node.unicode == unicode) && (p->node.fontId == fontKey)) {
            if (!cacheType || p->cacheType == cacheType) {
                node = p;
                break;
            }
        }
    }
    return node;
}

GlyphCacheNode* GlyphsCache::GetNodeCacheSpace(uint32_t unicode, uint16_t fontKey)
{
    if (!hasInit_) {
        return nullptr;
    }

    uint8_t font = (fontKey ^ unicode) & FONT_HASH_MASK;
    uint8_t uc = unicode & UNICODE_HASH_MASK;
    uint8_t i = (*cacheStatus_)[font][uc];
    GlyphCacheNode* node = &((*nodeCache_)[font][uc][i]);

    i++;
    if (i >= NODE_HASH_NR) {
        i = 0;
    }
    (*cacheStatus_)[font][uc] = i;

    return node;
}
} // namespace OHOS
