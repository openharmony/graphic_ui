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

/**
 * @addtogroup UI_Components
 * @{
 *
 * @brief Defines UI components such as buttons, texts, images, lists, and progress bars.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ui_canvas.h
 *
 * @brief Defines the attributes of the canvas component and provides functions for drawing rectangles,
 *        circles, and others.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_CANVAS_H
#define GRAPHIC_LITE_UI_CANVAS_H

#include <stack>
#include <string>
#include "common/image.h"
#include "components/ui_label.h"
#include "gfx_utils/diagram/depiction/depict_curve.h"
#include "gfx_utils/diagram/depiction/depict_dash.h"
#include "gfx_utils/diagram/depiction/depict_stroke.h"
#include "gfx_utils/diagram/imageaccessor/image_accessors.h"
#include "gfx_utils/diagram/imagefilter/filter_blur.h"
#include "gfx_utils/diagram/rasterizer/rasterizer_scanline_antialias.h"
#include "gfx_utils/diagram/scanline/geometry_scanline.h"
#include "gfx_utils/diagram/spancolorfill/fill_base.h"
#include "gfx_utils/diagram/spancolorfill/fill_gradient.h"
#include "gfx_utils/diagram/spancolorfill/fill_gradient_lut.h"
#include "gfx_utils/diagram/spancolorfill/fill_interpolator.h"
#include "gfx_utils/diagram/spancolorfill/fill_pattern_rgba.h"
#include "gfx_utils/diagram/vertexprimitive/geometry_path_storage.h"
#include "gfx_utils/file.h"
#include "gfx_utils/list.h"
namespace OHOS {
const uint16_t DEFAULT_STROKE_WIDTH = 2;
/**
 * @brief Defines the basic styles of graphs drawn on canvases.
 *
 * @since 1.0
 * @version 1.0
 */
class Paint : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Paint</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Paint()
        : style_(PaintStyle::STROKE_FILL_STYLE),
          fillColor_(Color::Black()),
          strokeColor_(Color::White()),
          opacity_(OPA_OPAQUE),
          strokeWidth_(DEFAULT_STROKE_WIDTH),
          changeFlag_(false),
          globalAlpha_(1.0),
          rotateAngle_(0),
          scaleRadioX_(1.0f),
          scaleRadioY_(1.0f),
          translationX_(0),
          translationY_(0) {}

    Paint(const Paint& paint)
    {
        Init(paint);
    }

    /*
     * Initialize data members.
     * style_:        paint style.
     * fillColor_:    Sets the fill color of the pen.
     * strokeColor_:  Sets the line color of the pen.
     * strokeWidth_:  Set lineweight.
     * opacity_:      Set transparency.
     * changeFlag_:   Set changeFlag.
     * scaleRadioX_:  Set scale Radio X
     * scaleRadioY_:  Set scale Radio Y
     * translationX_: Set translation X
     * translationY_: Set translation Y
     * globalAlpha_:  Set element Global alpha.
     * rotateAngle_:  Set rotate Angle.
     * transfrom_:    Set transfrom.
     */
    void Init(const Paint& paint)
    {
        style_ = paint.style_;
        fillColor_ = paint.fillColor_;
        strokeColor_ = paint.strokeColor_;
        strokeWidth_ = paint.strokeWidth_;
        opacity_ = paint.opacity_;
        changeFlag_ = paint.changeFlag_;
        scaleRadioX_= paint.scaleRadioX_;
        scaleRadioY_= paint.scaleRadioY_;
        translationX_= paint.translationX_;
        translationY_= paint.translationY_;
        globalAlpha_ = paint.globalAlpha_;
        rotateAngle_ = paint.rotateAngle_;
        transfrom_ = paint.transfrom_;
    }

    /**
     * @brief A destructor used to delete the <b>Paint</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Paint() {}

    const Paint& operator=(const Paint& paint)
    {
        Init(paint);
        return *this;
    }
    /**
     * @brief Enumerates paint styles of a closed graph. The styles are invalid for non-closed graphs.
     */
    enum PaintStyle {
        /** Stroke only */
        STROKE_STYLE = 1,
        /** Fill only */
        FILL_STYLE,
        /** Stroke and fill */
        STROKE_FILL_STYLE,
        /** Gradual change */
        GRADIENT,
        /** Image mode */
        PATTERN
    };

    struct LinearGradientPoint {
        /**  Start point coordinate x  */
        double x0;
        /**  Start point coordinate y  */
        double y0;
        /**  End point coordinate x  */
        double x1;
        /**  End point coordinate y  */
        double y1;
    };

    /**
     * @brief Sets the paint style of a closed graph.
     *
     * @param style Indicates the paint style. Stroke and fill are set by default.
     * For details, see {@link PaintStyle}.
     * @see GetStyle
     * @since 1.0
     * @version 1.0
     */
    void SetStyle(PaintStyle style)
    {
        style_ = style;
    }

    /**
     * @brief Sets the paint style.
     *
     * @param color value.
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeStyle(ColorType color)
    {
        SetStyle(Paint::STROKE_STYLE);
        SetStrokeColor(color);
    }

    /**
     * @brief Sets fill style.
     *
     * @param color value.
     * @since 1.0
     * @version 1.0
     */
    void SetFillStyle(ColorType color)
    {
        SetStyle(Paint::FILL_STYLE);
        SetFillColor(color);
    }

    /**
     * @brief Sets the paint stroke style of a closed graph.
     *
     * @param style Indicates the paint style. Stroke and fill are set by default.
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeStyle(PaintStyle style)
    {
        SetStyle(style);
    }

    /**
     * @brief Sets the paint fill style of a closed graph.
     *
     * @param style Indicates the paint style. Stroke and fill are set by default.
     * @since 1.0
     * @version 1.0
     */
    void SetFillStyle(PaintStyle style)
    {
        SetStyle(style);
    }

    /**
     * @brief Obtains the paint style of a closed graph.
     *
     * @return Returns the paint style. For details, see {@link PaintStyle}.
     * @see SetStyle
     * @since 1.0
     * @version 1.0
     */
    PaintStyle GetStyle() const
    {
        return style_;
    }

    /**
     * @brief Sets the width of a line or border.
     *
     * @param width Indicates the line width when a line is drawn or the border width when a closed graph is drawn.
     *        The width is extended to both sides.
     * @see GetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeWidth(uint16_t width)
    {
        strokeWidth_ = width;
    }

    /**
     * @brief Obtains the width of a line or border.
     *
     * @return Returns the line width if a line is drawn or the border width if a closed graph is drawn.
     * @see SetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetStrokeWidth() const
    {
        return strokeWidth_;
    }

    /**
     * @brief Sets the color of a line or border.
     *
     * @param color Indicates the line color when a line is drawn or the border color when a closed graph is drawn.
     * @see GetStrokeColor
     * @since 1.0
     * @version 1.0
     */
    void SetStrokeColor(ColorType color)
    {
        strokeColor_ = color;
        changeFlag_ = true;
    }

    /**
     * @brief Obtains the color of a line or border.
     *
     * @return Returns the line color if a line is drawn or the border color if a closed graph is drawn.
     * @see SetStrokeWidth
     * @since 1.0
     * @version 1.0
     */
    ColorType GetStrokeColor() const
    {
        return strokeColor_;
    }

    /**
     * @brief Sets fill color.
     *
     * This function is valid only for closed graphs.
     *
     * @param color Indicates the fill color to set.
     * @see GetFillColor
     * @since 1.0
     * @version 1.0
     */
    void SetFillColor(ColorType color)
    {
        fillColor_ = color;
        changeFlag_ = true;
    }

    /**
     * @brief Obtains the fill color.
     *
     * @return Returns the fill color.
     * @see SetFillColor
     * @since 1.0
     * @version 1.0
     */
    ColorType GetFillColor() const
    {
        return fillColor_;
    }

    /**
     * @brief Sets the opacity.
     *
     * The setting takes effect for the entire graph, including the border, line color, and fill color.
     *
     * @param opacity Indicates the opacity. The value range is [0, 255].
     * @see GetOpacity
     * @since 1.0
     * @version 1.0
     */
    void SetOpacity(uint8_t opacity)
    {
        opacity_ = opacity;
    }

    /**
     * @brief Obtains the opacity.
     *
     * @return Returns the opacity.
     * @see SetOpacity
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetOpacity() const
    {
        return opacity_;
    }

    /**
     * @brief get change flag.
     * @return Returns the changeFlag_ value.
     * @since 1.0
     * @version 1.0
     */
    bool GetChangeFlag() const
    {
        return changeFlag_;
    }

    /**
     * @brief Sets the alpha of the current drawing.
     * @param alphaPercentage alpha Percentage value. The value range is [0.0, 1.0].
     * @since 1.0
     * @version 1.0
     */
    void SetGlobalAlpha(float alphaPercentage)
    {
        if (alphaPercentage > 1) {
            globalAlpha_ = 1.0;
            return;
        }
        if (alphaPercentage < 0) {
            globalAlpha_ = 0.0;
            return;
        }
        globalAlpha_ = alphaPercentage;
        changeFlag_ = true;
    }

    /**
     * @brief get the alpha of the current drawing
     * @return Returns the alpha of the current drawing
     * @since 1.0
     * @version 1.0
     */
    float GetGlobalAlpha() const
    {
        return globalAlpha_;
    }

    /**
     * @brief Zooms the current drawing to a larger or smaller size
     * @param scaleX x coordinate scale value.
     * @param scaleY y coordinate scale value.
     * @since 1.0
     * @version 1.0
     */
    void Scale(float scaleX, float scaleY)
    {
        this->scaleRadioX_ *= scaleX;
        this->scaleRadioY_ *= scaleX;
        if (rotateAngle_ > 0.0 || rotateAngle_ < 0) {
            transfrom_.Rotate(-rotateAngle_ * PI / BOXER);
            transfrom_.Scale(scaleX, scaleY);
            transfrom_.Rotate(rotateAngle_ * PI / BOXER);
        } else {
            transfrom_.Scale(scaleX, scaleY);
        }
        changeFlag_ = true;
    }

    /**
     * @brief get the x coordinate scale value
     * @since 1.0
     * @version 1.0
     */
    double GetScaleX() const
    {
        return this->scaleRadioX_;
    }

    /**
     * @brief get the y coordinate scale value
     * @since 1.0
     * @version 1.0
     */
    double GetScaleY() const
    {
        return this->scaleRadioY_;
    }

    /**
     * @brief Rotate current drawing
     * @param angle rotate angle value.
     * @since 1.0
     * @version 1.0
     */
    void Rotate(float angle)
    {
        changeFlag_ = true;
        transfrom_.Rotate(angle * PI / BOXER);
        rotateAngle_ += angle;
    }

    /**
     * @brief Rotate current drawing
     * @param angle rotate angle value.
     * @param x translate x coordinate.
     * @param y translate y coordinate.
     * @since 1.0
     * @version 1.0
     */
    void Rotate(float angle, int16_t x, int16_t y)
    {
        transfrom_.Translate(-x, -y);
        transfrom_.Rotate(angle * PI / BOXER);
        rotateAngle_ += angle;
        transfrom_.Translate(x, y);
        changeFlag_ = true;
    }

    /**
     * @brief Remap the (x, y) position on the canvas
     * @param x translate x coordinate.
     * @param y translate y coordinate.
     * @since 1.0
     * @version 1.0
     */
    void Translate(int16_t x, int16_t y)
    {
        changeFlag_ = true;
        transfrom_.Translate(x, y);
        this->translationX_ += x;
        this->translationY_ += y;
    }

    /**
     * @brief Gets the x position on the remapping canvas
     * @since 1.0
     * @version 1.0
     */
    int16_t GetTranslateX() const
    {
        return this->translationX_;
    }

    /**
     * @brief Gets the Y position on the remapping canvas
     * @since 1.0
     * @version 1.0
     */
    int16_t GetTranslateY() const
    {
        return this->translationY_;
    }

    /**
     * @brief Resets the current conversion to the identity matrix. Then run transform ()
     * @param scaleX scale x value.
     * @param shearX shear x value.
     * @param shearY shear y value.
     * @param scaleY scale y value
     * @param transLateX translate x coordinate.
     * @param transLateY translate y coordinate.
     * @since 1.0
     * @version 1.0
     */
    void SetTransform(float scaleX, float shearX, float shearY, float scaleY,
                      int16_t transLateX, int16_t transLateY)
    {
        transfrom_.Reset();
        rotateAngle_ = 0;
        Transform(scaleX, shearX, shearY, scaleY, transLateX, transLateY);
        changeFlag_ = true;
    }

    /**
     * @brief Resets the current conversion to the identity matrix. Then run transform ()
     * @param scaleX scale x value.
     * @param shearX shear x value.
     * @param shearY shear y value.
     * @param scaleY scale y value
     * @param transLateX translate x coordinate.
     * @param transLateY translate y coordinate.
     * @since 1.0
     * @version 1.0
     */
    void Transform(float scaleX, float shearX, float shearY, float scaleY, int16_t transLateX, int16_t transLateY)
    {
        changeFlag_ = true;
        this->translationX_ += transLateX;
        this->translationY_ += transLateY;
        transLateX += transfrom_.GetData()[2];
        transLateY += transfrom_.GetData()[5];
        transfrom_.Translate(-transfrom_.GetData()[2], -transfrom_.GetData()[5]);
        Scale(scaleX, scaleY);
        transfrom_.Translate(transLateX, transLateY);
        transfrom_.SetData(1, transfrom_.GetData()[1] + shearX);
        transfrom_.SetData(3, transfrom_.GetData()[3] + shearY);
    }

    /**
     * @brief Gets the Trans Affine
     * @since 1.0
     * @version 1.0
     */
    TransAffine GetTransAffine() const
    {
        return transfrom_;
    }

    /**
     * @brief Gets the Rotate Angle
     * @since 1.0
     * @version 1.0
     */
    float GetRotateAngle() const
    {
        return rotateAngle_;
    }

private:
    PaintStyle style_;
    ColorType fillColor_;
    ColorType strokeColor_;
    uint8_t opacity_;
    uint16_t strokeWidth_;
    bool changeFlag_;
    float globalAlpha_;                                 // The transparency of the current drawing is 0-1 percent
    float rotateAngle_;                                 // Rotation angle in degrees
    float scaleRadioX_;
    float scaleRadioY_;
    int32_t translationX_;
    int32_t translationY_;
    TransAffine transfrom_;                             // matrix.
};

/**
 * @brief Defines a canvas, which is used to draw multiple types of 2D graphs.
 *
 * @since 1.0
 * @version 1.0
 */
class UICanvas : public UIView {
public:
    using Rgba8Color = Rgba8;
    // Color array RGBA, index position of blue:0,green:1,red:2,alpha:3,
    using ComponentOrder = OrderBgra;

    using Scanline = GeometryScanline;
    using SpanAllocator = FillBase<Rgba8Color> ;
    /**
     * @brief A constructor used to create a <b>UICanvas</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UICanvas() : startPoint_({0, 0}), vertices_(nullptr) {}

    /**
     * @brief A destructor used to delete the <b>UICanvas</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UICanvas();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_CANVAS;
    }

    /**
     * @brief Clears the entire canvas.
     *
     * @since 1.0
     * @version 1.0
     */
    void Clear();

    /**
     * @brief Sets the coordinates of the start point for drawing a line. For example, if <b>startPoint</b> is
     *        set to {50, 50}, the line is drawn from this set of coordinates on the canvas.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @see GetStartPosition
     * @since 1.0
     * @version 1.0
     */
    void SetStartPosition(const Point& startPoint)
    {
        startPoint_ = startPoint;
    }

    /**
     * @brief Obtains the coordinates of the start point of a line.
     *
     * @return Returns the coordinates of the start point.
     * @see SetStartPosition
     * @since 1.0
     * @version 1.0
     */
    const Point& GetStartPosition() const
    {
        return startPoint_;
    }

    /**
     * @brief Draws a straight line.
     *
     * If {@link SetStartPosition} is not used to set the coordinates of the start point of the line, the drawing
     * starts from the end point of the last line.
     *
     * @param endPoint Indicates the end point of the straight line.
     * @param paint    Indicates the straight line style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLine(const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a straight line from the coordinates of the start point.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param endPoint   Indicates the coordinates of the end point.
     * @param paint      Indicates the straight line style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLine(const Point& startPoint, const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a cubic Bezier curve.
     *
     * If {@link SetStartPosition} is not used to set the coordinates of the start point of the curve,
     * the drawing starts from the end point of the last line.
     * Currently, the opacity cannot be set, and the maximum line width is <b>3</b>.
     *
     * @param control1 Indicates the coordinates of the first control point of the cubic Bezier curve.
     * @param control2 Indicates the coordinates of the second control point of the cubic Bezier curve.
     * @param endPoint Indicates the coordinates of the end point of the cubic Bezier curve.
     * @param paint    Indicates the curve style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCurve(const Point& control1, const Point& control2, const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a cubic Bezier curve from the start point coordinates.
     *
     * Currently, the opacity cannot be set, and the maximum line width is <b>3</b>.
     *
     * @param startPoint Indicates the coordinates of the start point of the cubic Bezier curve.
     * @param control1   Indicates the coordinates of the first control point of the cubic Bezier curve.
     * @param control2   Indicates the coordinates of the second control point of the cubic Bezier curve.
     * @param endPoint   Indicates the coordinates of the end point of the cubic Bezier curve.
     * @param paint      Indicates the curve style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCurve(const Point& startPoint, const Point& control1, const Point& control2,
                   const Point& endPoint, const Paint& paint);

    /**
     * @brief Draws a rectangle.
     *
     * @param startPoint Indicates the coordinates of the point at the upper left corner of the rectangle.
     * @param height     Indicates the height of the rectangle.
     * @param width      Indicates the width of the rectangle.
     * @param paint      Indicates the rectangle style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawRect(const Point& startPoint, int16_t height, int16_t width, const Paint& paint);

    /**
     * @brief Draws a rectangular path with no fill.
     * @param startPoint starting point
     * @param height
     * @param width
     * @param paint paint brush
     */
    void StrokeRect(const Point& startPoint, int16_t height, int16_t width, const Paint& paint);

    /**
     * @brief Draws a circle.
     *
     * @param center Indicates the coordinates of the circle center.
     * @param radius Indicates the radius of the circle.
     * @param paint  Indicates the circle style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawCircle(const Point& center, uint16_t radius, const Paint& paint);

    /**
     * @brief Draws a sector.
     *
     * When the start angle is smaller than the end angle, the sector is drawn clockwise.
     * Otherwise, the sector is drawn counterclockwise.
     *
     * @param center     Indicates the coordinates of the sector's center.
     * @param radius     Indicates the radius of the sector.
     * @param startAngle Indicates the start angle of the sector. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param endAngle   Indicates the end angle of the sector. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param paint      Indicates the sector style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawSector(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle, const Paint& paint);

    /**
     * @brief Draws an arc.
     *
     * Only stroke is supported. \n
     * When the start angle is smaller than the end angle, the sector is drawn clockwise.
     * Otherwise, the sector is drawn counterclockwise. \n
     *
     * @param center     Indicates the coordinates of the arc's center.
     * @param radius     Indicates the radius of the arc.
     * @param startAngle Indicates the start angle of the arc. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param endAngle   Indicates the end angle of the arc. Value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param paint      Indicates the arc style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawArc(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle, const Paint& paint);

    /**
     * @brief Draws an image.
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param image      Indicates the pointer to the image source.
     * @param paint      Indicates the image style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawImage(const Point& startPoint, const char* image, const Paint& paint);

    /**
     * @brief Defines the font style.
     */
    struct FontStyle {
        /** Text direction. For details, see {@link UITextLanguageDirect}. */
        UITextLanguageDirect direct;
        /** Text alignment mode. For details, see {@link UITextLanguageAlignment}. */
        UITextLanguageAlignment align;
        /** Font size */
        uint8_t fontSize;
        /** Letter-spacing */
        int16_t letterSpace;
        /** Font name */
        const char* fontName;
    };

    struct ImageParam : public HeapBase {
        Point start;
        uint16_t height;
        uint16_t width;
        int16_t newWidth;
        int16_t newHeight;
        Image* image = nullptr;
        std::string path;
    };

    /**
     * @brief Draws text.
     *
     * Only fill is supported. \n
     * If the text length exceeds the value of <b>maxWidth</b>, the text will be truncated. \n
     *
     * @param startPoint Indicates the coordinates of the start point.
     * @param text       Indicates the pointer to the text content.
     * @param maxWidth   Indicates the maximum width of the text that can be displayed. If the maximum width is
     *                   exceeded, the text is truncated.
     * @param fontStyle  Indicates the text layout and font style. For details, see {@link FontStyle}.
     * @param paint      Indicates the text style. For details, see {@link Paint}.
     * @since 1.0
     * @version 1.0
     */
    void DrawLabel(const Point& startPoint, const char* text, uint16_t maxWidth, const FontStyle& fontStyle,
                   const Paint& paint);

    /**
     * @brief Creates a path.
     *
     * A round corner can be used to join two lines. Currently, miter and bevel joints are not supported.
     * To draw this path, you need to call {@link DrawPath}.
     *
     * @since 3.0
     * @version 5.0
     */
    void BeginPath();

    /**
     * @brief Moves the start point of this path to a specified point.
     *
     * @param point Indicates the specified point to move to.
     * @since 3.0
     * @version 5.0
     */
    void MoveTo(const Point& point);

    /**
     * @brief Creates a straight line from the end point of this path to a specified point.
     *
     * @param point Indicates the coordinates of the specified point.
     * @since 3.0
     * @version 5.0
     */
    void LineTo(const Point& point);

    /**
     * @brief Creates an arc path.
     *
     * @param center     Indicates the coordinates of the arc's center point.
     * @param radius     Indicates the radius of the arc.
     * @param startAngle Indicates the start angle of the arc.
     *                   The value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @param endAngle   Indicates the end angle of the arc.
     *                   The value <b>0</b> indicates the 12-o'clock direction,
     *                   and <b>90</b> indicates the 3-o'clock direction.
     * @since 3.0
     * @version 5.0
     */
    void ArcTo(const Point& center, uint16_t radius, int16_t startAngle, int16_t endAngle);

    /**
     * @brief Creates a rectangular path.
     *
     * @param point  Indicates the coordinates of the rectangle's upper left corner.
     * @param height Indicates the height of the rectangle.
     * @param width  Indicates the width of the rectangle.
     * @since 3.0
     * @version 5.0
     */
    void AddRect(const Point& point, int16_t height, int16_t width);

    /**
     * @brief Closes this path.
     *
     * @since 3.0
     * @version 5.0
     */
    void ClosePath();

    /**
     * @brief Draws this path.
     *
     * @param paint Indicates the path style. For details, see {@link Paint}.
     * @since 3.0
     * @version 5.0
     */
    void DrawPath(const Paint& paint);

    /**
     * @brief Fill polygon path
     * @param paint fill paint
     * @since 3.0
     * @version 5.0
     */
    void FillPath(const Paint& paint);

    /**
     * @brief Save history status
     *
     * @param paint  will save paint.
     * @since 3.0
     * @version 5.0
     */
    void Save(Paint& paint)
    {
        paintStack_.push(paint);
    }

    /**
     * @brief Restore to last historical state
     * @return Returns the last paint value.
     * @since 3.0
     * @version 5.0
     */
    Paint Restore()
    {
        Paint paint;
        if (paintStack_.empty()) {
            return paint;
        }
        paint = paintStack_.top();
        paintStack_.pop();
        return paint;
    }

    void OnDraw(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea) override;

    static void RenderBlendSolid(const Paint& paint,
                                 Rgba8Color& color,
                                 const bool& isStroke)
    {
        if (isStroke) {
            if (paint.GetStyle() == Paint::STROKE_STYLE ||
                paint.GetStyle() == Paint::STROKE_FILL_STYLE) {
                ChangeColor(color, paint.GetStrokeColor(), paint.GetStrokeColor().alpha * paint.GetGlobalAlpha());
            }
        } else {
            if (paint.GetStyle() == Paint::FILL_STYLE ||
                paint.GetStyle() == Paint::STROKE_FILL_STYLE) {
                ChangeColor(color, paint.GetFillColor(), paint.GetFillColor().alpha * paint.GetGlobalAlpha());
            }
        }
    }
protected:
    constexpr static uint8_t MAX_CURVE_WIDTH = 3;

    struct LineParam : public HeapBase {
        Point start;
        Point end;
    };

    struct CurveParam : public HeapBase {
        Point start;
        Point control1;
        Point control2;
        Point end;
    };

    struct RectParam : public HeapBase {
        Point start;
        int16_t height;
        int16_t width;
    };

    struct CircleParam : public HeapBase {
        Point center;
        uint16_t radius;
    };

    struct ArcParam : public HeapBase {
        Point center;
        uint16_t radius;
        int16_t startAngle;
        int16_t endAngle;
    };

    struct PathParam : public HeapBase {
        UICanvasVertices* vertices;
        ImageParam* imageParam = nullptr;
        bool isStroke;
    };

    struct DrawCmd : public HeapBase {
        Paint paint;
        void* param;
        void (*DrawGraphics)(BufferInfo&, void*, const Paint&, const Rect&, const Rect&, const Style&);
        void (*DeleteParam)(void*);
    };

    Point startPoint_;
    UICanvasVertices* vertices_;
    List<DrawCmd> drawCmdList_;
    // Save historical modification information of paint
    std::stack<Paint> paintStack_;
    static void DeleteLineParam(void* param)
    {
        LineParam* lineParam = static_cast<LineParam*>(param);
        delete lineParam;
    }

    static void DeleteCurveParam(void* param)
    {
        CurveParam* curveParam = static_cast<CurveParam*>(param);
        delete curveParam;
    }

    static void DeleteRectParam(void* param)
    {
        RectParam* rectParam = static_cast<RectParam*>(param);
        delete rectParam;
    }

    static void DeleteCircleParam(void* param)
    {
        CircleParam* circleParam = static_cast<CircleParam*>(param);
        delete circleParam;
    }

    static void DeleteArcParam(void* param)
    {
        ArcParam* arcParam = static_cast<ArcParam*>(param);
        delete arcParam;
    }

    static void DeleteImageParam(void* param)
    {
        ImageParam* imageParam = static_cast<ImageParam*>(param);
        if (imageParam->image != nullptr) {
            delete imageParam->image;
            imageParam->image = nullptr;
        }
        delete imageParam;
    }

    static void DeleteLabel(void* param)
    {
        UILabel* label = static_cast<UILabel*>(param);
        delete label;
    }

    static void DeletePathParam(void* param)
    {
        PathParam* pathParam = static_cast<PathParam*>(param);
        if (pathParam->vertices != nullptr) {
            pathParam->vertices->FreeAll();
            pathParam->vertices = nullptr;
        }
        if (pathParam->imageParam != nullptr) {
            DeleteImageParam(pathParam->imageParam);
        }
        delete pathParam;
        pathParam = nullptr;
    }

    static void DoDrawLine(BufferInfo& gfxDstBuffer,
                           void* param,
                           const Paint& paint,
                           const Rect& rect,
                           const Rect& invalidatedArea,
                           const Style& style);
    static void DoDrawCurve(BufferInfo& gfxDstBuffer,
                            void* param,
                            const Paint& paint,
                            const Rect& rect,
                            const Rect& invalidatedArea,
                            const Style& style);
    static void DoDrawRect(BufferInfo& gfxDstBuffer,
                           void* param,
                           const Paint& paint,
                           const Rect& rect,
                           const Rect& invalidatedArea,
                           const Style& style);
    static void DoFillRect(BufferInfo& gfxDstBuffer,
                           void* param,
                           const Paint& paint,
                           const Rect& rect,
                           const Rect& invalidatedArea,
                           const Style& style);
    static void DoDrawCircle(BufferInfo& gfxDstBuffer,
                             void* param,
                             const Paint& paint,
                             const Rect& rect,
                             const Rect& invalidatedArea,
                             const Style& style);
    static void DoDrawArc(BufferInfo& gfxDstBuffer,
                          void* param,
                          const Paint& paint,
                          const Rect& rect,
                          const Rect& invalidatedArea,
                          const Style& style);
    static void DoDrawImage(BufferInfo& gfxDstBuffer,
                            void* param,
                            const Paint& paint,
                            const Rect& rect,
                            const Rect& invalidatedArea,
                            const Style& style);
    static void DoDrawLabel(BufferInfo& gfxDstBuffer,
                            void* param,
                            const Paint& paint,
                            const Rect& rect,
                            const Rect& invalidatedArea,
                            const Style& style);
    static void DoDrawPath(BufferInfo& gfxDstBuffer,
                           void* param,
                           const Paint& paint,
                           const Rect& rect,
                           const Rect& invalidatedArea,
                           const Style& style);
    static void GetAbsolutePosition(const Point& prePoint, const Rect& rect, const Style& style, Point& point);
    static void DoDrawLineJoin(BufferInfo& gfxDstBuffer,
                               const Point& center,
                               const Rect& invalidatedArea,
                               const Paint& paint);

    static void DoFillPath(BufferInfo& gfxDstBuffer,
                           void* param,
                           const Paint& paint,
                           const Rect& rect,
                           const Rect& invalidatedArea,
                           const Style& style);

    static void SetRasterizer(UICanvasVertices& vertices,
                              const Paint& paint,
                              RasterizerScanlineAntialias<>& rasterizer,
                              TransAffine& transform,
                              const bool& isStroke);

    static void DoRender(BufferInfo& gfxDstBuffer,
                         void* param,
                         const Paint& paint,
                         const Rect& rect,
                         const Rect& invalidatedArea,
                         const Style& style,
                         const bool& isStroke);
    /**
     * Assembly parameter setting lineweight，LineCap，LineJoin
     */
    template <class LineStyle>
    static void LineStyleCalc(DepictStroke<LineStyle>& strokeLineStyle, const Paint& paint)
    {
        strokeLineStyle.SetWidth(paint.GetStrokeWidth()); // Line style related
    };

    static bool IsSoild(const Paint& paint)
    {
        if (paint.GetStyle() == Paint::STROKE_STYLE ||
           paint.GetStyle() == Paint::FILL_STYLE ||
           paint.GetStyle() == Paint::STROKE_FILL_STYLE) {
            return true;
        }
        return false;
    }

    template <class Color>
    static void ChangeColor(Color& color, ColorType colorType, uint8_t alpha)
    {
        color.redValue = colorType.red;
        color.greenValue = colorType.green;
        color.blueValue = colorType.blue;
        color.alphaValue = alpha;
    }

    void DrawRectSetCmd(const Point& startPoint, int16_t height, int16_t width, const Paint& paint,
                        Paint::PaintStyle paintStyle);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_CANVAS_H
