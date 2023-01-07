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

#ifndef GLYPHS_CACHE_H
#define GLYPHS_CACHE_H

#include "font/ui_font_header.h"
#include "gfx_utils/heap_base.h"

namespace OHOS {
class GlyphsCache : public HeapBase {
public:
    GlyphsCache();

    GlyphsCache(const GlyphsCache&) = delete;

    GlyphsCache& operator=(const GlyphsCache&) = delete;

    GlyphsCache(const GlyphsCache&&) = delete;

    GlyphsCache& operator=(const GlyphsCache&&) = delete;

    ~GlyphsCache();

    int8_t CacheInit();
    void ClearCacheFlag();
    GlyphCacheNode* GetNodeFromCache(uint32_t unicode, uint16_t fontKey, uint16_t cacheType);
    GlyphCacheNode* GetNodeCacheSpace(uint32_t unicode, uint16_t fontId);

private:
#if (defined(ENABLE_MIX_FONT) && (ENABLE_MIX_FONT == 1))
    static constexpr uint8_t FONT_HASH_SHIFT = 3;
#else
    static constexpr uint8_t FONT_HASH_SHIFT = 4;
#endif
    static constexpr uint8_t FONT_HASH_NR = 1 << FONT_HASH_SHIFT;
    static constexpr uint32_t FONT_HASH_MASK = FONT_HASH_NR - 1;
    static constexpr uint8_t UNICODE_HASH_SHIFT = 6;
    static constexpr uint8_t UNICODE_HASH_NR = 1 << UNICODE_HASH_SHIFT;
    static constexpr uint32_t UNICODE_HASH_MASK = UNICODE_HASH_NR - 1;
    static constexpr uint8_t NODE_HASH_SHIFT = 4;
    static constexpr uint8_t NODE_HASH_NR = 1 << NODE_HASH_SHIFT;

    using CacheType = GlyphCacheNode[FONT_HASH_NR][UNICODE_HASH_NR][NODE_HASH_NR];
    using CacheState = uint8_t[FONT_HASH_NR][UNICODE_HASH_NR];

    CacheType* nodeCache_;
    CacheState* cacheStatus_;
    bool hasInit_;
};
} // namespace OHOS
#endif /* GLYPHS_CACHE_H */