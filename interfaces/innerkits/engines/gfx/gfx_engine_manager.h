/*
 * Copyright (c) 2020-2022 Huawei Device Co., Ltd.
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

#ifndef GRAPHIC_LITE_GFX_ENGINE_MANAGER_H
#define GRAPHIC_LITE_GFX_ENGINE_MANAGER_H

#include "gfx_utils/geometry2d.h"
#include "gfx_utils/graphic_buffer.h"
#include "gfx_utils/graphic_math.h"
#include "gfx_utils/graphic_types.h"
#include "gfx_utils/heap_base.h"
#include "gfx_utils/style.h"
#include "gfx_utils/transform.h"
namespace OHOS {
class GfxEngineManager;

enum BlendMode {
    /** No mixing */
    BLEND_MODE = -1,
    /** S */
    BLEND_SRC,
    /** D */
    BLEND_DST,
    /** Default. Displays the source image on the target image. */
    /** S + (1 - Sa) * D */
    BLEND_SRC_OVER,
    /** Displays the target image on the source image. */
    /** (1 - Da) * S + D */
    BLEND_DST_OVER,
    /** Displays the source image in the target image. Only the source image part within the target image
     *  will be displayed, and the target image is transparent. */
    /** Da * S */
    BLEND_SRC_IN,
    /** Displays the target image in the source image. Only the target image part within the source image
     *  will be displayed, and the source image is transparent. */
    /** Sa * D */
    BLEND_DST_IN,
    /** Displays the source image outside the target image. Only the source image part other than the target
     *  image will be displayed, and the target image is transparent. */
    /** S * (1 - Da) */
    BLEND_SRC_OUT,
    /** Displays the target image outside the source image. Only the part of the target image other than the
     *  source image will be displayed, and the source image is transparent. */
    /** D * (1 - Sa) */
    BLEND_DST_OUT,
    /** Displays the source image at the top of the target image. The part of the source image outside the
     *  target image is invisible. */
    BLEND_SRC_ATOP,
    /** Displays the target image at the top of the source image. The part of the target image outside the
     *  source image is invisible. */
    BLEND_DST_ATOP,
    /** Use the XOR operation to combine the source image with the target image. */
    BLEND_XOR,
    /** Display source image + target image. */
    BLEND_LIGHTEN,
    /** Blend transparency */
    BLEND_ALPHA,
    /** S + D - S * D */
    BLEND_SCREEN,
    /** S * (1 - Da) + D * (1 - Sa) + S * D */
    BLEND_MULTIPLY,
    /** S + D */
    BLEND_ADDITIVE,
    /** D * (1 - S) */
    BLEND_SUBTRACT,
    /** Displays the source image. Ignore the target image. */
    BLEND_COPY = 1000
};

#ifndef TRANSFORMOPTION
#define TRANSFORMOPTION
struct TransformOption {
    TransformAlgorithm algorithm;
};
#endif

struct BlendOption {
    TransformMap transMap;
    BlendMode mode;
    TransformOption option;
    OpacityType opacity;
};

class Image;
struct ArcInfo {
    Point center;
    Point imgPos;
    uint16_t radius;
    int16_t startAngle;
    int16_t endAngle;
    const Image* imgSrc;
};

struct TransformDataInfo {
    ImageHeader header;
    const uint8_t* data;
    uint8_t pxSize;
    BlurLevel blurLevel;
    TransformAlgorithm algorithm;
};

enum BufferInfoUsage {
    BUFFER_FB_SURFACE,
    BUFFER_MAP_SURFACE,
    BUFFER_SNAPSHOT_SURFACE
};

class GfxEngineManager : public HeapBase {
public:
    virtual void DrawArc(BufferInfo& dst, ArcInfo& arcInfo, const Rect& mask,
                         const Style& style, OpacityType opacity, uint8_t cap);

    virtual void DrawLine(BufferInfo& dst, const Point& start, const Point& end,
                          const Rect& mask, int16_t width, ColorType color, OpacityType opacity);

    virtual void DrawLetter(BufferInfo& gfxDstBuffer,
                            const uint8_t* fontMap,
                            const Rect& fontRect,
                            const Rect& subRect,
                            const uint8_t fontWeight,
                            const ColorType& color,
                            const OpacityType opa);

    virtual void DrawCubicBezier(BufferInfo& dst, const Point& start, const Point& control1,
                                 const Point& control2, const Point& end, const Rect& mask,
                                 int16_t width, ColorType color, OpacityType opacity);

    virtual void DrawRect(BufferInfo& dst,
                          const Rect& rect,
                          const Rect& dirtyRect,
                          const Style& style,
                          OpacityType opacity);

    virtual void DrawTransform(BufferInfo& dst,
                               const Rect& mask,
                               const Point& position,
                               ColorType color,
                               OpacityType opacity,
                               const TransformMap& transMap,
                               const TransformDataInfo& dataInfo);

    // x/y: center of a circle
    virtual void ClipCircle(const ImageInfo* info, float x, float y, float radius);

    virtual void Blit(BufferInfo& dst,
                      const Point& dstPos,
                      const BufferInfo& src,
                      const Rect& subRect,
                      const BlendOption& blendOption);

    virtual void Fill(BufferInfo& dst,
                      const Rect& fillArea,
                      const ColorType color,
                      const OpacityType opacity);

    virtual uint8_t* AllocBuffer(uint32_t size, uint32_t usage);

    virtual void FreeBuffer(uint8_t* buffer);

    virtual void FlushRegion(const Rect& rect, const uint8_t* buffer, ColorMode mode) {}

    virtual BufferInfo* GetFBBufferInfo()
    {
        return nullptr;
    }

    virtual void Flush() {}

    virtual uint16_t GetScreenWidth()
    {
        return width_;
    }

    virtual uint16_t GetScreenHeight()
    {
        return height_;
    }

    virtual void SetScreenShape(ScreenShape screenShape)
    {
        screenShape_ = screenShape;
    }

    virtual ScreenShape GetScreenShape()
    {
        return screenShape_;
    }

    static GfxEngineManager* GetInstance()
    {
        return baseEngine_;
    }

    static void InitGfxEngine(GfxEngineManager* gfxEngine = nullptr)
    {
        if (gfxEngine == nullptr) {
            static GfxEngineManager localGfxEngine;
            baseEngine_ = &localGfxEngine;
            return;
        }
        baseEngine_ = gfxEngine;
    }

protected:
    static GfxEngineManager* baseEngine_;
    uint16_t width_ = HORIZONTAL_RESOLUTION;
    uint16_t height_ = VERTICAL_RESOLUTION;
    ScreenShape screenShape_ = RECTANGLE;
};
using BaseGfxEngine = GfxEngineManager;
} // namespace OHOS

#endif // GRAPHIC_LITE_GFX_ENGINE_MANAGER_H
