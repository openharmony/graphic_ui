/*
 * Copyright (c) 2021-2021 Huawei Device Co., Ltd.
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

#ifndef GRAPHIC_LITE_CLIP_UTILS_H
#define GRAPHIC_LITE_CLIP_UTILS_H

#include "gfx_utils/geometry2d.h"
#include "gfx_utils/image_info.h"
#include "gfx_utils/list.h"
#include "gfx_utils/vector.h"

namespace OHOS {
/* Indicates an interval with the same transparency */
struct Span : public HeapBase {
    int16_t left;
    int16_t right;
    uint8_t opa;
};

/* Indicates a point in float */
struct PointF {
    float x;
    float y;
};

/* Indicates a rectangle in flaot */
struct RectF {
    float left;
    float top;
    float right;
    float bottom;
};

/* Indicates an edge */
struct Edge : public HeapBase {
    /* The maximum y coordinate of the edge */
    int16_t ymax;
    /* The minimum y coordinate of the edge */
    int16_t ymin;
    /* The x-coordinate of the intersection with the current row */
    float x;
    /* Increment of x-coordinate when y-coordinate increases by 1 */
    float dx;
};

/* Indicates an edge that to be antialiased */
struct AAEdge : public HeapBase {
    /* The y-coordinate of current integer x-coordinate */
    float y;
    /* Increment of y-coordinate when x-coordinate step by sx */
    float dy;
    /* Current integer x-coordinate */
    int16_t x;
    /* Step of x, 1 or -1 */
    int16_t sx;
    /* Upper limit of steps */
    int16_t xIndex;
};

/* Indicates a cubic Bezier curve */
struct Spline : public HeapBase {
    /* Start point */
    PointF a;
    /* First control point */
    PointF b;
    /* Second control point */
    PointF c;
    /* End point */
    PointF d;
};

enum ClipPathCmd {
    CMD_MOVE_TO,
    CMD_LINE_TO,
    CMD_CURVE_TO,
};

class ClipPolygon : public HeapBase {
public:
    ClipPolygon() {}
    ~ClipPolygon()
    {
        Clear();
    }

    void Clear()
    {
        points_.Clear();
        bound_ = {0, 0, 0, 0};
    }

    void AddPoint(const PointF& p)
    {
        if (points_.IsEmpty()) {
            bound_.left = p.x;
            bound_.right = p.x;
            bound_.top = p.y;
            bound_.bottom = p.y;
            points_.PushBack(p);
        } else if (!MATH_FLT_EQUAL(points_.Back().x, p.x) || !MATH_FLT_EQUAL(points_.Back().y, p.y)) {
            bound_.left = (p.x < bound_.left) ? p.x : bound_.left;
            bound_.top = (p.y < bound_.top) ? p.y : bound_.top;
            bound_.right = (p.x > bound_.right) ? p.x : bound_.right;
            bound_.bottom = (p.y > bound_.bottom) ? p.y : bound_.bottom;
            points_.PushBack(p);
        }
    }

    Graphic::Vector<PointF> points_;
    RectF bound_ = {0, 0, 0, 0};
};

/*
 * Indicates a path to be cliped.
 * Note: The path will be automatically closed. Only non-self-intersecting path are supported.
 */
class ClipPath : public HeapBase {
public:
    ClipPath() {}
    ~ClipPath()
    {
        points_.Clear();
        cmd_.Clear();
    }
    void GeneratePolygon(ClipPolygon& polygon) const;

    ClipPath& MoveTo(const PointF& point);
    ClipPath& LineTo(const PointF& point);
    ClipPath& CurveTo(const PointF& control1, const PointF& control2, const PointF& end);
    ClipPath& Arc(const PointF& center, float radius, int16_t startAngle, int16_t endAngle);
    ClipPath& Circle(const PointF& center, float radius);

private:
    bool CheckoutSplineError(const Spline& spline) const;
    void MidPointOfLine(const PointF& a, const PointF& b, PointF& mid) const;
    void SplitSpline(Spline& s1, Spline& s2) const;
    void SplineDecompose(Spline& s, ClipPolygon& polygon) const;

    void ArcInner(const PointF& center, float radius, int16_t startAngle, int16_t endAngle);

    List<PointF> points_;
    List<ClipPathCmd> cmd_;
    PointF startPos_ = {0, 0};
};

/*
 * Blitter and its subclasses are responible for handling the span list and actually draws the pixels
 */
class Blitter : public HeapBase {
public:
    Blitter() {}
    virtual ~Blitter() {}

    virtual void DrawHorSpan(const List<Span>& span, int16_t yCur) {}
    virtual void Finish() {}
};

/* Clipimageblitter will clip the image on its original memory */
class ClipImageBlitter : public Blitter {
public:
    explicit ClipImageBlitter(const ImageInfo* src) : src_(src) {}
    virtual ~ClipImageBlitter() {}

    void DrawHorSpan(const List<Span>& span, int16_t yCur) override;
    void Finish() override;
private:
    void DrawPixel(int16_t x, int16_t y, uint8_t opa);
    void DrawHorLine(int16_t x, int16_t y, int16_t width, uint8_t opa);

    const ImageInfo* src_ = nullptr;
    int16_t iy_ = 0;
};

class ClipUtils : public HeapBase {
public:
    ClipUtils() {}
    ~ClipUtils() {}

    void PerformScan(const ClipPath& path, Blitter& blitter);
private:
    void ClearSpanTable();

    void CreateNewSpan(List<Span>& list, ListNode<Span>* node, int16_t left, int16_t right, uint8_t opa);
    void InsertSpan(List<Span>& curList, int16_t left, int16_t right, uint8_t opa);
    void MergeSpan(List<Span>& s);

    void CreateEdgeList(const ClipPath& path);
    void DrawAntiAliasedPoints(int16_t yCur);

    /* Save the lines that needs to be scanned vertically */
    List<Edge> edgeList_;
    /* Save the non steep lines that need to be antialiased */
    List<AAEdge> aaList_;
    /* Pointer to the span of the current row */
    List<Span>* span0_ = nullptr;
    /* Pointer to the span of the next row */
    List<Span>* span1_ = nullptr;

    int16_t minY_ = INT16_MAX;
    int16_t maxY_ = INT16_MIN;
};
};
#endif