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

/**
* @file render_scanline.h
* @brief Defines scanline renderer
* @since 1.0
* @version 1.0
*/

#ifndef GRAPHIC_LITE_RENDER_SCANLINE_H
#define GRAPHIC_LITE_RENDER_SCANLINE_H

#include <cstdlib>
#include <cstring>
#include <limits>
#include "gfx_utils/color.h"
#include "gfx_utils/diagram/spancolorfill/fill_base.h"
#include "gfx_utils/diagram/scanline/geometry_scanline.h"
#include "render/render_base.h"

namespace OHOS {
    /**
     * @brief Anti aliasing scanline for rendering solid lines.
     * Via scanline Begin gets the first span, and + + span gets the next span.
     * The corresponding function is called by renbase to draw the color to the
     * canvas where the corresponding span is located.
     * @param raster grating
     * @param scanline Scan line
     * @param renBase Renderer
     * @param color colour
     */
    template <class Rasterizer, class Scanline,
              class BaseRenderer, class ColorT>
    void RenderScanlinesAntiAliasSolid(Rasterizer& raster, Scanline& scanline,
                                       BaseRenderer& renBase, const ColorT& color)
    {
        if (!raster.RewindScanlines()) {
            return;
        }
        typename BaseRenderer::ColorType ren_color = color;
        scanline.Reset(raster.GetMinX(), raster.GetMaxX());
        while (raster.SweepScanline(scanline)) {
            int32_t y = scanline.GetYLevel();
            uint32_t num_spans = scanline.NumSpans();
            typename Scanline::ConstIterator span = scanline.Begin();
            while (true) {
                int32_t x = span->x;
                if (span->spanLength > 0) {
                    renBase.BlendSolidHSpan(x, y, static_cast<uint32_t>(span->spanLength),
                                            ren_color,
                                            span->covers);
                } else {
                    renBase.BlendHLine(x, y, static_cast<uint32_t>(x - span->spanLength - 1),
                                       ren_color,
                                       *(span->covers));
                }
                if (--num_spans == 0) {
                    break;
                }
                ++span;
            }
        }
    }

    /**
     * @brief Rendering anti aliased scanlines.
     * Via scanline Begin gets the first span, and + + span gets the next span.
     * Via allocat_ - > Resize (spanlen) allocates a color_type with the same length as span.
     * Through segment generator spangenerate_ - > Generate(colors, x, y, len); Fill the color
     * array to get the color array with values corresponding to the scan line span.
     * Finally, through renbase_ Call the corresponding function to draw the color array
     * to the canvas position of the corresponding span.
     * @param raster grating
     * @param scanline Scan line
     * @param renBase Renderer
     * @param alloc distributor
     * @param spanGen Segment generator
     */
    template <class Rasterizer, class Scanline, class BaseRenderer,
              class SpanAllocator, class SpanGenerator>
    void RenderScanlinesAntiAlias(Rasterizer& raster, Scanline& scanline, BaseRenderer& renBase,
                                  SpanAllocator& alloc, SpanGenerator& spanGen)
    {
        if (!raster.RewindScanlines()) {
            return;
        }
        scanline.Reset(raster.MinX(), raster.MaxX());
        spanGen.Prepare(); // Segment generator preparation
        while (raster.SweepScanline(scanline)) {
            int32_t y = scanline.GetYLevel();
            uint32_t num_spans = scanline.NumSpans();
            typename Scanline::ConstIterator span = scanline.Begin();
            while (true) {
                int32_t x = span->x;
                int32_t len = span->spanLength;
                const uint8_t* covers = span->covers;

                if (len < 0) {
                    len = -len;
                }
                typename BaseRenderer::ColorType* colors = alloc.Resize(len);
                spanGen.Generate(colors, x, y, len);
                renBase.BlendColorHSpan(x, y, len, colors,
                                        (span->spanLength < 0) ? 0 : covers, *covers);

                if (--num_spans == 0) {
                    break;
                }
                ++span;
            }
        }
    }
} // namespace OHOS
#endif
