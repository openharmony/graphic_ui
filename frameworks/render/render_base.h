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
 * @file renderer_base.h
 * @brief Defines Base renderer
 * @since 1.0
 * @version 1.0.
 */

#ifndef GRAPHIC_LITE_RENDER_BASE_H
#define GRAPHIC_LITE_RENDER_BASE_H

#include "gfx_utils/diagram/common/common_basics.h"
#include "render/render_buffer.h"

namespace OHOS {
template <class PixelFormat>
class RenderBase {
public:
    using PixfmtType = PixelFormat;
    using ColorType = typename PixfmtType::ColorType;
    using RowData = typename PixfmtType::RowData;

    RenderBase() : pixfmtType_(nullptr), clipBox_(1, 1, 0, 0) {}

    explicit RenderBase(PixfmtType& ren)
        : pixfmtType_(&ren), clipBox_(0, 0, ren.GetWidth() - 1, ren.GetHeight() - 1) {}

    /**
     * @brief afferent pixfmt_type param.
     */
    void Attach(PixfmtType& ren)
    {
        pixfmtType_ = &ren;
        clipBox_ = RectI(0, 0, ren.GetWidth() - 1, ren.GetHeight() - 1);
    }

    /**
     * @brief Gets the width to render.
     */
    uint32_t GetWidth() const
    {
        return pixfmtType_->GetWidth();
    }

    /**
     * @brief Gets the height to render.
     */
    uint32_t GetHeight() const
    {
        return pixfmtType_->GetHeight();
    }

    /**
     * @brief ClipBox Sets the size of the clipping box.
     * @param x1 rectangular starting point x coordinate.
     * @param y1 rectangular starting point y coordinate.
     * @param x2 rectangular diagonal x coordinate.
     * @param y2 rectangular diagonal y coordinate.
     * @return Returns whether the rectangle was created successfully.
     */
    bool ClipBox(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    {
        RectI cb(x1, y1, x2, y2);
        cb.Normalize();
        if (cb.Clip(RectI(0, 0, GetWidth() - 1, GetHeight() - 1))) {
            clipBox_ = cb;
            return true;
        }
        ClipBoxNaked(1, 1, 0, 0);
        return false;
    }

    /**
     * @brief ResetClipping Set the size of the clipping box according to the visibility,
     *  The visibility is set to normal, and the invisibility is set to one pixel.
     * @param visibility Visible.
     */
    void ResetClipping(bool visibility)
    {
        if (visibility) {
            ClipBoxNaked(0, 0, GetWidth() - 1, GetHeight() - 1);
        } else {
            ClipBoxNaked(1, 1, 0, 0);
        }
    }

    /**
     * @brief ClipBoxNaked Sets the size of the box.
     * @param x1 rectangular starting point x coordinate.
     * @param y1 rectangular starting point y coordinate.
     * @param x2 rectangular starting point x coordinate.
     * @param y2 rectangular starting point y coordinate.
     */
    void ClipBoxNaked(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    {
        clipBox_.x1 = x1;
        clipBox_.y1 = y1;
        clipBox_.x2 = x2;
        clipBox_.y2 = y2;
    }

    /**
     * @brief inbox determines whether the point (x, y) is within the rectangle.
     * @param x coordinate of x point.
     * @param y coordinate of y point.
     * @return Return whether.
     */
    bool Inbox(int32_t x, int32_t y) const
    {
        return x >= clipBox_.x1 && y >= clipBox_.y1 && x <= clipBox_.x2 && y <= clipBox_.y2;
    }

    /**
     * @brief GetClipBox Get cut box.
     * @return Return to the corresponding box.
     */
    const RectI& GetClipBox() const
    {
        return clipBox_;
    }

    /**
     * @return Returns the minimum value of the x-axis of the box.
     */
    int32_t GetXMin() const
    {
        return clipBox_.x1;
    }

    /**
     * @return Returns the minimum value of the y-axis of the box.
     */
    int32_t GetYMin() const
    {
        return clipBox_.y1;
    }

    /**
     * @return Returns the maximum value of the x-axis of the box.
     */
    int32_t GetXMax() const
    {
        return clipBox_.x2;
    }

    /**
     * @return Returns the maximum value of the Y-axis of the box.
     */
    int32_t GetYMax() const
    {
        return clipBox_.y2;
    }

    /**
     * @brief Clear clear the pixels in the rectangle under getwidth() width and getheight() height with color.
     * @param color colour.
     */
    void Clear(const ColorType& color)
    {
        if (GetWidth()) {
            for (uint32_t y = 0; y < GetHeight(); y++) {
                pixfmtType_->CopyHLine(0, y, GetWidth(), color);
            }
        }
    }

    /**
     * @brief ReplaceColor Replace the color of the original colored area with color.
     * @param color colour.
     */
    void ReplaceColor(const ColorType& color)
    {
        if (GetWidth()) {
            for (uint32_t y = 0; y < GetHeight(); y++) {
                pixfmtType_->ReplaceHlineColor(0, y, GetWidth(), color);
            }
        }
    }

    /**
     * @brief fill fills the rectangle color under getwidth() width and getheight() height.
     * @param color Color to fill.
     */
    void Fill(const ColorType& color)
    {
        if (GetWidth()) {
            for (uint32_t y = 0; y < GetHeight(); y++) {
                pixfmtType_->blend_hline(0, y, GetWidth(), color, COVER_MASK);
            }
        }
    }

    /**
     * @brief BlendHLine Render scanlines within a certain range of the X axis on the Y axis.
     * @param x1 Scan line left coordinate.
     * @param y  Scan line Y-axis coordinates.
     * @param x2 Scan line right coordinate.
     * @param c The color of the rendered scanline.
     * @param colors Scan line corresponding color array.
     */
    void BlendHLine(int32_t x1, int32_t y, int32_t x2, const ColorType& color, uint8_t cover)
    {
        if (x1 > x2) {
            int32_t swapTemp = x1;
            x1 = x2;
            x2 = swapTemp;
        }
        if (y > GetYMax() || y < GetYMin() || x1 > GetXMax() || x2 < GetXMin()) {
            return;
        }
        if (x1 < GetXMin()) {
            x1 = GetXMin();
        }

        if (x2 > GetXMax()) {
            x2 = GetXMax();
        }
        pixfmtType_->BlendHLine(x1, y, x2 - x1 + 1, color, cover);
    }

    /**
     * @brief BlendSolidHSpan Renders a scan line of a solid line within a certain range of the Y axis.
     * @param x scan line X-axis start coordinate.
     * @param y scan line Y-axis start coordinate.
     * @param len Scan line length.
     * @param c The color of the rendered scanline.
     * @param colors Scan line corresponding color array.
     */
    void BlendSolidHSpan(int32_t x, int32_t y, int32_t len, const ColorType& color, const uint8_t* covers)
    {
        if (y > GetYMax() || y < GetYMin()) {
            return;
        }
        if (x < GetXMin()) {
            len -= GetXMin() - x;
            if (len <= 0) {
                return;
            }
            covers += GetXMin() - x;
            x = GetXMin();
        }
        if (x + len > GetXMax()) {
            len = GetXMax() - x + 1;
            if (len <= 0) {
                return;
            }
        }
        pixfmtType_->BlendSolidHSpan(x, y, len, color, covers);
    }

    /**
     * @brief CopyColorHSpan Copy colors within a certain Y-axis range
     * @param x Scan line X-axis start coordinate
     * @param y Scan line Y-axis start coordinate
     * @param len Scan line length.
     * @param colors Scan line corresponding color array.
     */
    void CopyColorHSpan(int32_t x, int32_t y, int32_t len, const ColorType* colors)
    {
        if (!ColorHSpanHandler(x, y, len, colors, nullptr)) {
            return;
        }
        pixfmtType_->CopyColorHSpan(x, y, len, colors);
    }

    /**
     * @brief BlendColorHSpan Mix colors within a certain height.
     * @param x Scan line X-axis start coordinate
     * @param y Scan line Y-axis start coordinate
     * @param len Scan line length.
     * @param colors Scan line corresponding color array.
     * @param covers Scan line corresponding coverage array.
     * @param cover Coverage
     */
    void BlendColorHSpan(int32_t x, int32_t y, int32_t len, const ColorType* colors, const uint8_t* covers,
                         uint8_t cover = COVER_FULL)
    {
        if (!ColorHSpanHandler(x, y, len, colors, covers)) {
            return;
        }
        pixfmtType_->BlendColorHSpan(x, y, len, colors, covers, cover);
    }

    /**
     * @brief ColorHSpanHandler Handle ColorHSpan params.
     * @param x Scan line X-axis start coordinate
     * @param y Scan line Y-axis start coordinate
     * @param len Scan line length.
     * @param colors Scan line corresponding color array.
     * @param covers Scan line corresponding coverage array.
     * @return Returns true if should run the follow programs.
     */
    bool ColorHSpanHandler(int32_t& x, int32_t& y, int32_t& len, const ColorType*& colors, const uint8_t*& covers)
    {
        if (y > GetYMax() || y < GetYMin()) {
            return false;
        }
        if (x < GetXMin()) {
            int32_t d = GetXMin() - x;
            len -= d;
            if (len <= 0) {
                return false;
            }
            if (covers) {
                covers += d;
            }
            colors += d;
            x = GetXMin();
        }
        if (x + len > GetXMax()) {
            len = GetXMax() - x + 1;
            if (len <= 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief ClipRectArea Clip rectangular area
     * @param dst destination rectangle
     * @param src source rectangle
     * @param srcW source width
     * @param srcH source height
     * @return Returns the area of the clip
     */
    RectI ClipRectArea(RectI& dst, RectI& src, int32_t srcW, int32_t srcH) const
    {
        RectI rc(0, 0, 0, 0);
        RectI cb = GetClipBox();
        ++cb.x2;
        ++cb.y2;

        if (src.x1 < 0) {
            dst.x1 -= src.x1;
            src.x1 = 0;
        }
        if (src.y1 < 0) {
            dst.y1 -= src.y1;
            src.y1 = 0;
        }

        if (src.x2 > srcW) {
            src.x2 = srcW;
        }
        if (src.y2 > srcH) {
            src.y2 = srcH;
        }
        if (dst.x1 < cb.x1) {
            src.x1 += cb.x1 - dst.x1;
            dst.x1 = cb.x1;
        }
        if (dst.y1 < cb.y1) {
            src.y1 += cb.y1 - dst.y1;
            dst.y1 = cb.y1;
        }

        if (dst.x2 > cb.x2) {
            dst.x2 = cb.x2;
        }
        if (dst.y2 > cb.y2) {
            dst.y2 = cb.y2;
        }

        rc.x2 = dst.x2 - dst.x1;
        rc.y2 = dst.y2 - dst.y1;

        if (rc.x2 > src.x2 - src.x1) {
            rc.x2 = src.x2 - src.x1;
        }

        if (rc.y2 > src.y2 - src.y1) {
            rc.y2 = src.y2 - src.y1;
        }
        return rc;
    }

    /**
     * @brief Take a segment from SRC to buffer for mixing.
     * @param src one segment buffer.
     * @param rectSrcPtr Rectangular boundary.
     * @param dx X length to be taken out
     * @param dy Y length to be taken out
     * @param cover Coverage
     */
    template <class SrcPixelFormatRenderer>
    void BlendFrom(const SrcPixelFormatRenderer& src, const RectI* rectSrcPtr = 0, int32_t dx = 0, int32_t dy = 0,
                   uint8_t cover = COVER_FULL)
    {
        RectI srcRect(0, 0, src.Width(), src.Height());
        if (rectSrcPtr) {
            srcRect.x1 = rectSrcPtr->x1;
            srcRect.y1 = rectSrcPtr->y1;
            srcRect.x2 = rectSrcPtr->x2 + 1;
            srcRect.y2 = rectSrcPtr->y2 + 1;
        }

        RectI dstRect(srcRect.x1 + dx, srcRect.y1 + dy, srcRect.x2 + dx, srcRect.y2 + dy);
        RectI rect = ClipRectArea(dstRect, srcRect, src.Width(), src.Height());
        if (rect.x2 > 0) {
            int32_t incy = 1;
            if (dstRect.y1 > srcRect.y1) {
                srcRect.y1 += rect.y2 - 1;
                dstRect.y1 += rect.y2 - 1;
                incy = -1;
            }
            while (rect.y2 > 0) {
                RowData rw = src.Row(srcRect.y1);
                if (rw.ptr) {
                    int32_t x1src = srcRect.x1;
                    int32_t x1dst = srcRect.x1;
                    int32_t len = rect.x2;
                    if (rw.x1 > x1src) {
                        x1dst += rw.x1 - x1src;
                        len -= rw.x1 - x1src;
                        x1src = rw.x1;
                    }
                    if (len > 0) {
                        if (x1src + len - 1 > rw.x2) {
                            len -= x1src + len - rw.x2 - 1;
                        }
                        if (len > 0) {
                            pixfmtType_->BlendFrom(src, x1dst, dstRect.y1, x1src, srcRect.y1, len, cover);
                        }
                    }
                }
                dstRect.y1 += incy;
                srcRect.y1 += incy;
                --rect.y2;
            }
        }
    }

private:
    PixfmtType* pixfmtType_;
    RectI clipBox_;
};
} // namespace OHOS
#endif
