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

#ifndef GRAPHIC_LITE_RENDER_PIXFMT_RGBA_BLEND_H
#define GRAPHIC_LITE_RENDER_PIXFMT_RGBA_BLEND_H

#include <cmath>
#include <cstring>

#include "engines/gfx/gfx_engine_manager.h"
#include "gfx_utils/heap_base.h"
#include "gfx_utils/graphic_log.h"
#include "render_pixfmt_rgba_gamma.h"
#include "render/render_buffer.h"
#include "render/render_pixfmt_base.h"
#include "draw/draw_utils.h"

#ifdef ARM_NEON_OPT
#include "graphic_neon_pipeline.h"
#endif
namespace OHOS {
const uint8_t NUM_COMPONENTS = 4;
const uint8_t PIX_STEP = 4;
const uint8_t PIX_WIDTH = sizeof(uint8_t) * PIX_STEP;

template <class ColorT, class Order>
struct RgbaBlender {
    using ColorType = ColorT;
    using OrderType = Order;

#ifdef ARM_NEON_OPT
    /**
     * @brief Mix the pixels with the color component.
     * @param color color,red,green,blue,alpha Color Component,cover Coverage.
     * @since 1.0
     * @version 1.0
     */
    static inline void NeonBlendPix(
        uint8_t* color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint8_t* covers)
    {
        DrawUtils::GetInstance()->BlendLerpPix(color, red, green, blue, alpha, covers);
    }

    /**
     * @brief Mix the pixels with the color component.
     * @param color color,red,green,blue,alpha Color Component,cover Coverage.
     * @since 1.0
     * @version 1.0
     */
    static inline void NeonBlendPix(
        uint8_t* color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint8_t cover)
    {
        DrawUtils::GetInstance()->BlendLerpPix(color, red, green, blue, alpha, cover);
    }

    /**
     * @brief Mix the pixels with the color component.
     * @param color color,red,green,blue,alpha Color Component
     * @since 1.0
     * @version 1.0
     */
    static inline void NeonBlendPix(
        uint8_t* color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        DrawUtils::GetInstance()->BlendLerpPix(color, red, green, blue, alpha);
    }

    static inline void NeonBlendPix(uint8_t* dstColors, uint8_t* srcColors, uint8_t srcCover)
    {
        DrawUtils::GetInstance()->BlendLerpPix(dstColors, srcColors, srcCover);
    }

    static inline void NeonBlendPix(uint8_t* dstColors, uint8_t* srcColors, uint8_t* srcCovers)
    {
        DrawUtils::GetInstance()->BlendLerpPix(dstColors, srcColors, srcCovers);
    }
#endif
    /**
     * @brief Mix the pixels with the color component.
     * @param color color,red,green,blue,alpha Color Component,cover Coverage.
     * @since 1.0
     * @version 1.0
     */
    static inline void BlendPix(
        uint8_t* color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint8_t cover)
    {
        BlendPix(color, red, green, blue, ColorType::MultCover(alpha, cover));
    }

    /**
     * @brief Mix the pixels with the color component.
     * @param color color,red,green,blue,alpha Color Component
     * @since 1.0
     * @version 1.0
     */
    static inline void BlendPix(
        uint8_t* color, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        color[Order::RED] = ColorType::Lerp(color[Order::RED], red, alpha);
        color[Order::GREEN] = ColorType::Lerp(color[Order::GREEN], green, alpha);
        color[Order::BLUE] = ColorType::Lerp(color[Order::BLUE], blue, alpha);
        color[Order::ALPHA] = ColorType::Prelerp(color[Order::ALPHA], alpha, alpha);
    }
};

template <class uint8_t, class OrderType, class ColorType>
struct PixelColorType {
    uint8_t colors[NUM_COMPONENTS];

    /**
     * @brief Set Colors.
     * @param r,g,b,a Color Component.
     * @since 1.0
     * @version 1.0
     */
    void SetPixelColor(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, uint8_t alphaValue)
    {
        colors[OrderType::RED] = redValue;
        colors[OrderType::GREEN] = greenValue;
        colors[OrderType::BLUE] = blueValue;
        colors[OrderType::ALPHA] = alphaValue;
    }

    /**
     * @brief Set Colors.
     * @param color Colors.
     * @since 1.0
     * @version 1.0
     */
    void SetPixelColor(const ColorType& color)
    {
        SetPixelColor(color.redValue, color.greenValue, color.blueValue, color.alphaValue);
    }

    /**
     * @brief Get Colors.
     * @param r,g,b,a Color Component.
     * @since 1.0
     * @version 1.0
     */
    void GetPixelColor(uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha) const
    {
        red = colors[OrderType::RED];
        green = colors[OrderType::GREEN];
        blue = colors[OrderType::BLUE];
        alpha = colors[OrderType::ALPHA];
    }

    /**
     * @brief Get Colors.
     * @return Colors
     * @since 1.0
     * @version 1.0
     */
    ColorType GetPixelColor() const
    {
        return ColorType(colors[OrderType::RED], colors[OrderType::GREEN],
                         colors[OrderType::BLUE], colors[OrderType::ALPHA]);
    }

    /**
    * @brief Gets the color component of the next pixel.
    *
    * @since 1.0
    * @version 1.0
    */
    PixelColorType* Next()
    {
        return reinterpret_cast<PixelColorType*>((colors + PIX_STEP));
    }

    /**
    * @brief Gets the first address of the color component of the next pixel.
    *
    * @since 1.0
    * @version 1.0
    */
    const PixelColorType* Next() const
    {
        return static_cast<const PixelColorType*>(colors + PIX_STEP);
    }

    /**
    * @brief Gets the first address of the color component of the nth pixe.
    * @param pixelIndex pixel offset
    * @since 1.0
    * @version 1.0
    */
    PixelColorType* Advance(int32_t pixelIndex)
    {
        return static_cast<PixelColorType*>(colors + pixelIndex * PIX_STEP);
    }

    /**
    * @brief Gets the first address of the color component of the nth pixe.
    * @param pixelIndex pixel offset
    * @since 1.0
    * @version 1.0
    */
    const PixelColorType* Advance(int32_t pixelIndex) const
    {
        return static_cast<const PixelColorType*>(colors + pixelIndex * PIX_STEP);
    }
};

template <class Blender, class RenBuf>
class RenderPixfmtRgbaBlend : public HeapBase {
public:
    using RbufType = RenBuf;
    using RowData = typename RbufType::RowData;
    using BlenderType = Blender;
    using ColorType = typename BlenderType::ColorType;
    using OrderType = typename BlenderType::OrderType;
    using PixelType = PixelColorType<uint8_t, OrderType, ColorType>;

    RenderPixfmtRgbaBlend() : rBuf_(0) {}
    explicit RenderPixfmtRgbaBlend(RbufType& rBuf) :  rBuf_(&rBuf) {}

    /**
    * @brief Attach pixels to the drawing area.
    *
    * @since 1.0
    * @version 1.0
    */
    virtual void Attach(RbufType& rBuf)
    {
        rBuf_ = &rBuf;
    }

    template <class PixFmt>
    bool Attach(PixFmt& pixf, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    {
        RectI r(x1, y1, x2, y2);
        if (r.Clip(RectI(0, 0, pixf.Width() - 1, pixf.Height() - 1))) {
            int32_t stride = pixf.Stride();
            rBuf_->Attach(pixf.PixPtr(r.x1, stride < 0 ? r.y2 : r.y1),
                          (r.x2 - r.x1) + 1, (r.y2 - r.y1) + 1, stride);
            return true;
        }
        return false;
    }

    /**
    * @brief Get the size of each screen (draw buffer).
    *
    * @since 1.0
    * @version 1.0
    */
    virtual inline uint32_t GetWidth() const
    {
        return rBuf_->GetWidth();
    }

    virtual inline uint32_t GetHeight() const
    {
        return rBuf_->GetHeight();
    }

    /**
      * @brief Returns the number of bytes in a row of the window.
      *
      * @since 1.0
      * @version 1.0
      */
    virtual inline int32_t Stride() const
    {
        return rBuf_->GetStride();
    }

    /**
      * @brief Returns the row address of a window row.
      *
      * @since 1.0
      * @version 1.0
      */
    virtual inline uint8_t* GetRowPtr(int32_t y)
    {
        return rBuf_->GetRowPtr(y);
    }

    /**
      * @brief Returns the row address of a window row.
      *
      * @since 1.0
      * @version 1.0
      */
    virtual inline const uint8_t* GetRowPtr(int32_t y) const
    {
        return rBuf_->GetRowPtr(y);
    }

    /**
      * @brief Returns the row data of one row of the window.
      *
      * @since 1.0
      * @version 1.0
      */
    virtual inline RowData GetRow(int32_t y) const
    {
        return rBuf_->GetRow(y);
    }

    virtual inline uint8_t* PixPtr(int32_t x, int32_t y)
    {
        return rBuf_->GetRowPtr(y) + sizeof(uint8_t) * (x * PIX_STEP);
    }

    virtual inline const uint8_t* PixPtr(int32_t x, int32_t y) const
    {
        return rBuf_->GetRowPtr(y) + sizeof(uint8_t) * (x * PIX_STEP);
    }

    /**
     * @brief Pointer to pixel type pointer.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline PixelType* PixValuePtr(int32_t x, int32_t y)
    {
        return reinterpret_cast<PixelType*>(rBuf_->GetRowPtr(y) + sizeof(uint8_t) * (x * PIX_STEP));
    }

    /**
     * @brief Gets the pixel address of the specified left.
     *
     * @since 1.0
     * @version 1.0.
     */
    virtual inline const PixelType* PixValuePtr(int32_t x, int32_t y) const
    {
        uint8_t* pixelPtr = rBuf_->GetRowPtr(y);
        return pixelPtr ? reinterpret_cast<PixelType*>(pixelPtr + sizeof(uint8_t) * (x * PIX_STEP)) : nullptr;
    }

    /**
     * @brief Pointer to pixel type pointer.
     *
     * @since 1.0
     * @version 1.0
     */
    inline static PixelType* PixValuePtr(void* pixelPtr)
    {
        return static_cast<PixelType*>(pixelPtr);
    }

    /**
     * @brief Pointer to pixel type pointer.
     *
     * @since 1.0
     * @version 1.0
     */
    inline static const PixelType* PixValuePtr(const void* pixelPtr)
    {
        return static_cast<const PixelType*>(pixelPtr);
    }

    /**
     * @brief Gets the color of a pixel.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline ColorType Pixel(int32_t x, int32_t y) const
    {
        const PixelType* pixelPtr = PixValuePtr(x, y);
        if (pixelPtr != nullptr) {
            return pixelPtr->GetPixelColor();
        }
        return ColorType::NoColor();
    }

    /**
     * @brief Copy color to pixel.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline void CopyPixel(int32_t x, int32_t y, const ColorType& color)
    {
        PixValuePtr(x, y)->SetPixelColor(color);
    }

    /**
    * @brief Mix pixels (x, y) with the transparency of cover (coverage = transparency) with color color.
    *
    * @since 1.0
    * @version 1.0
    */
    virtual inline void BlendPixel(int32_t x, int32_t y, const ColorType& color, uint8_t cover)
    {
        CopyOrBlendPix(PixValuePtr(x, y), color, cover);
    }

    /**
     * @brief Set the pixels of len length in horizontal order starting from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void CopyHLine(int32_t x, int32_t y,
                           uint32_t len,
                           const ColorType& color)
    {
        PixelType vPixelValue;
        vPixelValue.SetPixelColor(color);
        PixelType* pixelPtr = PixValuePtr(x, y);
#ifdef NEON_ARM_OPT
        int16_t step = NEON_STEP_8 * PIX_STEP;
        while (len >= NEON_STEP_8) {
            SetPixelColor_ARGB8888(pixelPtr->colors, color->redValue,
                                   colors->greenValue, colors->blueValue,
                                   colors->alphaValue);
            pixelPtr = pixelPtr->colors + step;
            len -= NEON_STEP_8;
        };
#endif
        for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
            *pixelPtr = vPixelValue;
            pixelPtr = pixelPtr->Next();
        }
    }

    /**
     * @brief Pixels of len length are mixed horizontally from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void BlendHLine(int32_t x, int32_t y,
                            uint32_t len,
                            const ColorType& color,
                            uint8_t cover)
    {
        if (!color.IsTransparent()) {
            PixelType* pPixel = PixValuePtr(x, y);
#ifdef NEON_ARM_OPT
            int16_t step = NEON_STEP_8 * PIX_STEP;
            while (len >= NEON_STEP_8) {
                NeonBlendPix(pixelPtr, color, cover);
                pixelPtr = pixelPtr->colors + step;
                len -= NEON_STEP_8;
            };
#endif
            if (color.IsOpaque() && cover == COVER_MASK) {
                for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                    PixelType pixelValue;
                    pixelValue.SetPixelColor(color);
                    *pPixel = pixelValue;
                    pPixel = pPixel->Next();
                }
            } else {
                if (cover == COVER_MASK) {
                    for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                        BlendPix(pPixel, color);
                        pPixel = pPixel->Next();
                    }
                } else {
                    for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                        BlendPix(pPixel, color, cover);
                        pPixel = pPixel->Next();
                    }
                }
            }
        }
    }

    /**
     * @brief Mix a series of colors of len length in horizontal order starting from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void BlendSolidHSpan(int32_t x, int32_t y,
                                 uint32_t len,
                                 const ColorType& color,
                                 const uint8_t* covers)
    {
        if (!color.IsTransparent()) {
            PixelType* pixelPtr = PixValuePtr(x, y);

#ifdef NEON_ARM_OPT
            int16_t step = NEON_STEP_8 * PIX_STEP;
            while (len >= NEON_STEP_8) {
                NeonBlendPix(pixelPtr->colors, color, covers);
                pixelPtr = pixelPtr->colors + step;
                covers += NEON_STEP_8;
                len -= NEON_STEP_8;
            };
#endif

            for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                if (color.IsOpaque() && *covers == COVER_MASK) {
                    pixelPtr->SetPixelColor(color);
                } else {
                    BlendPix(pixelPtr, color, *covers);
                }
                pixelPtr = pixelPtr->Next();
                ++covers;
            }
        }
    }

    /**
     * @brief Mix a series of colors of len length in vertical order starting from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void BlendSolidVSpan(int32_t x, int32_t y,
                                 uint32_t len,
                                 const ColorType& color,
                                 const uint8_t* covers)
    {
        if (!color.IsTransparent()) {
            do {
                PixelType* pixelPtr = PixValuePtr(x, y++);
                if (color.IsOpaque() && *covers == COVER_MASK) {
                    pixelPtr->SetPixelColor(color);
                } else {
                    BlendPix(pixelPtr, color, *covers);
                }
                ++covers;
            } while (--len);
        }
    }

    /**
     * @brief Set the color of len length in horizontal order starting from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void CopyColorHSpan(int32_t x, int32_t y,
                                uint32_t len,
                                const ColorType* colors)
    {
        PixelType* pixelPtr = PixValuePtr(x, y);
#ifdef NEON_ARM_OPT
        int16_t step = NEON_STEP_8 * PIX_STEP;
        const int16_t NEON_STEP_COMPONENTS = NEON_STEP_8 * NUM_COMPONENTS;
        uint8_t mColors[NEON_STEP_COMPONENTS];
        while (len >= NEON_STEP_8) {
            if (memset_s(mColors, size_t(NEON_STEP_COMPONENTS), 0, size_t(NEON_STEP_COMPONENTS)) != EOK) {
                return GRAPHIC_LOGE("CopyColorHSpan faile");
            }
            NeonMemcpy(mColors, NEON_STEP_COMPONENTS, colors, NEON_STEP_COMPONENTS);

            SetPixelColor_ARGB8888(pixelPtr->colors, mColors);
            pixelPtr = pixelPtr->colors + step;
            colors += NEON_STEP_8;
            len -= NEON_STEP_8;
        };
#endif
        for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
            pixelPtr->SetPixelColor(*colors++);
            pixelPtr = pixelPtr->Next();
        }
    }

    /**
     * @brief Set the color of len length in vertical order starting from (x, y).
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void CopyColorVSpan(int32_t x, int32_t y,
                                uint32_t len,
                                const ColorType* colors)
    {
        do {
            PixValuePtr(x, y++)->SetPixelColor(*colors++);
        } while (--len);
    }

    /**
     * @brief Mix a series of colors of len length in horizontal order starting from (x, y).
     * @param x         x coordinate.
     * @param y         x coordinate
     * @param len       length of line
     * @param colors    colors array
     * @param covers    transition value
     * @param cover     cover value
     * @since 1.0
     * @version 1.0
     */
    void BlendColorHSpan(int32_t x, int32_t y,
                         uint32_t len,
                         const ColorType* colors,
                         const uint8_t* covers,
                         uint8_t cover)
    {
        PixelType* pixelPtr = PixValuePtr(x, y, len);
        if (covers) {
#ifdef NEON_ARM_OPT
            int16_t step = NEON_STEP_8 * PIX_STEP;
            const int16_t NEON_STEP_COMPONENTS = NEON_STEP_8 * NUM_COMPONENTS;
            uint8_t mColors[NEON_STEP_COMPONENTS];
            while (len >= NEON_STEP_8) {
                if (memset_s(mColors, size_t(NEON_STEP_COMPONENTS), 0, size_t(NEON_STEP_COMPONENTS)) != EOK) {
                    GRAPHIC_LOGE("BlendColorHSpan fail");
                    return;
                }
                NeonMemcpy(mColors, NEON_STEP_COMPONENTS, colors, NEON_STEP_COMPONENTS);

                NeonBlendPix(pixelPtr->colors, mColors, covers);
                pixelPtr = pixelPtr->colors + step;
                colors += NEON_STEP_8;
                covers += NEON_STEP_8;
                len -= NEON_STEP_8;
            };
#endif
            for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                CopyOrBlendPix(pixelPtr, *colors++, *covers++);
                pixelPtr = pixelPtr->Next();
            }
        } else {
#ifdef NEON_ARM_OPT
            int16_t step = NEON_STEP_8 * PIX_STEP;
            const int16_t NEON_STEP_COMPONENTS = NEON_STEP_8 * NUM_COMPONENTS;
            uint8_t mColors[NEON_STEP_COMPONENTS];
            while (len >= NEON_STEP_8) {
                if (memset_s(mColors, size_t(NEON_STEP_COMPONENTS), 0, size_t(NEON_STEP_COMPONENTS)) != EOK) {
                    GRAPHIC_LOGE("BlendColorHSpan fail");
                    return;
                }
                NeonMemcpy(mColors, NEON_STEP_COMPONENTS, colors, NEON_STEP_COMPONENTS);

                NeonBlendPix(pixelPtr->colors, mColors, cover);
                pixelPtr = pixelPtr->colors + step;
                colors += NEON_STEP_8;
                len -= NEON_STEP_8;
            };
#endif
            if (cover == COVER_MASK) {
                for (int16_t iPixel = 0; iPixel < len; ++iPixel) {
                    cover == COVER_MASK ? CopyOrBlendPix(pixelPtr, *colors++) :
                                          CopyOrBlendPix(pixelPtr, *colors++, cover);
                    pixelPtr = pixelPtr->Next();
                }
            }
        }
    }

    /**
     * @brief Mix source pixels and coverage into rBuf_.
     * @param from Source pixel buffer.
     * @param xdst,ydst Destination buffer start position.
     * @param xsrc,ysrc Source buffer start position.
     * @param len Length to blend.
     * @param cover Coverage.
     * @since 1.0
     * @version 1.0
     */
    template <class SrcPixelFormatRenderer>
    void BlendFrom(const SrcPixelFormatRenderer& from,
                   int32_t xdst, int32_t ydst,
                   int32_t xsrc, int32_t ysrc,
                   uint32_t len,
                   uint8_t cover)
    {
        using SrcPixelType = typename SrcPixelFormatRenderer::PixelType;
        const SrcPixelType* psrc = from.PixValuePtr(xsrc, ysrc);
        if (psrc != nullptr) {
            PixelType* pdst = PixValuePtr(xdst, ydst, len);

            int32_t srcInc = 1;
            int32_t dstInc = 1;

#ifdef NEON_ARM_OPT
            dstInc = NEON_STEP_8;
            srcInc = dstInc;
            if (xdst > xsrc) {
                psrc = psrc->Advance(len - NEON_STEP_8);
                pdst = pdst->Advance(len - NEON_STEP_8);
                srcInc = -NEON_STEP_8;
                dstInc = -NEON_STEP_8;
            }

            while (len >= NEON_STEP_8) {
                NeonBlendPix(pdst->colors, psrc->colors, cover);
                psrc = psrc->Advance(srcInc);
                pdst = pdst->Advance(dstInc);
                len -= NEON_STEP_8;
            };
#endif

            if (xdst > xsrc) {
                psrc = psrc->Advance(len - 1);
                pdst = pdst->Advance(len - 1);
                srcInc = -1;
                dstInc = -1;
            }
            if (cover == COVER_MASK) {
                for (int16_t i = 0; i < static_cast<int32_t>(len); ++i) {
                    CopyOrBlendPix(pdst, psrc->GetPixelColor());
                    psrc = psrc->Advance(srcInc);
                    pdst = pdst->Advance(dstInc);
                }
            } else {
                for (int16_t i = 0; i < static_cast<int32_t>(len); ++i) {
                    CopyOrBlendPix(pdst, psrc->GetPixelColor(), cover);
                    psrc = psrc->Advance(srcInc);
                    pdst = pdst->Advance(dstInc);
                }
            }
        }
    }

protected:
#ifdef ARM_NEON_OPT
    virtual inline void NeonBlendPix(PixelType* pixelColors, const ColorType& color)
    {
        blender_.NeonBlendPix(pixelColors->colors, color.redValue, color.greenValue,
                              color.blueValue, color.alphaValue);
    }

    virtual inline void NeonBlendPix(PixelType* pixelColors, const ColorType& color, uint8_t cover)
    {
        blender_.NeonBlendPix(pixelColors->colors, color.redValue, color.greenValue,
                              color.blueValue, color.alphaValue, cover);
    }

    virtual inline void NeonBlendPix(uint8_t* dstColors, uint8_t* srcColors, uint8_t srcCover)
    {
        blender_.NeonBlendPix(dstColors, srcColors, srcCover);
    }

    virtual inline void NeonBlendPix(uint8_t* dstColors, uint8_t* srcColors, uint8_t* srcCovers)
    {
        blender_.NeonBlendPix(dstColors, srcColors, srcCovers);
    }

    virtual inline void NeonBlendPix(uint8_t* dstColors, const ColorType& srcColors, uint8_t* srcCovers)
    {
        blender_.NeonBlendPix(dstColors, srcColors.redValue, srcColors.greenValue, srcColors.blueValue,
                              srcColors.alphaValue, srcCovers);
    }
#endif

    /**
     * @brief Blend color and coverage to specified pixels.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline void BlendPix(PixelType* pixelPtr, const ColorType& color, uint32_t cover)
    {
        blender_.BlendPix(pixelPtr->colors, color.redValue, color.greenValue,
                          color.blueValue, color.alphaValue, cover);
    }

    /**
     * @brief Blend colors to specified pixels.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline void BlendPix(PixelType* pixelPtr, const ColorType& color)
    {
        blender_.BlendPix(pixelPtr->colors, color.redValue, color.greenValue, color.blueValue, color.alphaValue);
    }

    /**
     * @brief Set or blend to specified pixels with color and coverage.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual inline void CopyOrBlendPix(PixelType* pixelPtr, const ColorType& color, uint32_t cover)
    {
        if (!color.IsTransparent()) {
            if (color.IsOpaque() && cover == COVER_MASK) {
                pixelPtr->SetPixelColor(color.redValue, color.greenValue, color.blueValue, color.alphaValue);
            } else {
                blender_.BlendPix(pixelPtr->colors, color.redValue, color.greenValue,
                                  color.blueValue, color.alphaValue, cover);
            }
        }
    }

    /**
     * @brief Sets or blends the color to the specified pixel.
     *
     * @since 1.0
     * @version 1.0.
     */
    virtual inline void CopyOrBlendPix(PixelType* pixelPtr, const ColorType& color)
    {
        if (!color.IsTransparent()) {
            if (color.IsOpaque()) {
                pixelPtr->SetPixelColor(color);
            } else {
                blender_.BlendPix(pixelPtr->colors, color.redValue, color.greenValue,
                                  color.blueValue, color.alphaValue);
            }
        }
    }

    RbufType* rBuf_;
    Blender blender_;
};
} // namespace OHOS
#endif
