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

#ifndef GLYPHS_MANAGER_FONT_H
#define GLYPHS_MANAGER_FONT_H

#include "font/ui_font_header.h"

namespace OHOS {
class GlyphsManager {
public:
    GlyphsManager();

    GlyphsManager(const GlyphsManager&) = delete;

    GlyphsManager& operator=(const GlyphsManager&) = delete;

    ~GlyphsManager();

    int32_t GetRamUsedLen() const;

    int8_t GetFontVersion(char* version, uint8_t len) const;

    int16_t GetFontHeight(uint8_t fontId);

    int16_t GetFontWidth(uint32_t unicode, uint8_t fontId);

    const FontHeader* GetFontHeader(uint8_t fontId);

    const GlyphNode* GetGlyphNode(uint32_t unicode, uint8_t fontId);

    int8_t GetBitmap(uint32_t unicode, uint8_t* bitmap, uint8_t fontId);

    void SetRamBuffer(uintptr_t ramAddr);

    int8_t SetFile(int32_t fp, uint32_t start);

private:
    static constexpr uint8_t RADIX_TREE_BITS = 4;
    static constexpr uint8_t RADIX_SHIFT_START = 32 - RADIX_TREE_BITS;
    static constexpr uint32_t RADIX_TREE_SLOT_NUM = 1 << RADIX_TREE_BITS;
    static constexpr uint32_t RADIX_TREE_MASK = RADIX_TREE_SLOT_NUM - 1;

    static constexpr uint8_t FONT_HASH_SHIFT = 3;
    static constexpr uint8_t FONT_HASH_NR = 1 << FONT_HASH_SHIFT;
    static constexpr uint32_t FONT_HASH_MASK = FONT_HASH_NR - 1;
    static constexpr uint8_t UNICODE_HASH_SHIFT = 6;
    static constexpr uint8_t UNICODE_HASH_NR = 1 << UNICODE_HASH_SHIFT;
    static constexpr uint32_t UNICODE_HASH_MASK = UNICODE_HASH_NR - 1;
    static constexpr uint8_t NODE_HASH_SHIFT = 4;
    static constexpr uint8_t NODE_HASH_NR = 1 << NODE_HASH_SHIFT;

    using CacheType = GlyphNode[FONT_HASH_NR][UNICODE_HASH_NR][NODE_HASH_NR];
    using CacheState = uint8_t[FONT_HASH_NR][UNICODE_HASH_NR];

    struct IndexNode {
        uint16_t stubs[RADIX_TREE_SLOT_NUM];
    };

    struct GlyphInfo {
        uint8_t fontId;
        uint32_t glyphNodeSectionStart;
        uint32_t bitMapSectionStart;
        uint32_t fontIndexSectionStart;
        uint8_t* indexCache;
        FontHeader* fontHeader;
    };

    int8_t GlyphNodeCacheInit();
    GlyphNode* GetNodeFromCache(uint32_t unicode, uint8_t fontId);
    GlyphNode* GetNodeCacheSpace(uint32_t unicode, uint8_t fontId);
    GlyphNode* GetNodeFromFile(uint32_t unicode, uint8_t fontId);
    uint32_t AlignUp(uint32_t addr, uint32_t align)
    {
        return (((addr + (1 << align)) >> align) << align);
    }
    int8_t GetGlyphInfo(uint8_t fontId, GlyphInfo& glyphInfo);

    BinHeader binHeader_;
    uint8_t fontNum_;
    uint32_t start_;
    uint32_t fontHeaderSectionStart_;
    uint32_t fontIndexSectionStart_;
    uint32_t glyphNodeSectionStart_;
    uint32_t bitMapSectionStart_;

    uint8_t* ramAddr_;
    uint32_t ramUsedLen_;
    FontHeader* fontHeaderCache_;
    uint8_t* indexCache_;

    CacheType* nodeCache_;
    CacheState* cacheStatus_;

    int32_t fp_;

    bool isRamSet_;
    bool isFileSet_;
};
} // namespace OHOS
#endif /* GLYPHS_MANAGER_FONT_H */
