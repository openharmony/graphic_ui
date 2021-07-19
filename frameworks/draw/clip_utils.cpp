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

#include "clip_utils.h"

#include <cmath>
#include "draw_utils.h"
#include "gfx_utils/graphic_log.h"

namespace OHOS {
namespace {
constexpr float EPS = 0.01f;
};

#define I_PART(X) ((int)(X))
#define F_PART(X) (((float)(X)) - (float)I_PART(X))
#define RF_PART(X) (1.0 - F_PART(X))
#define SWAP_FLOAT(a, b) \
do {                     \
    float tmp = a;       \
    a = b;               \
    b = tmp;             \
} while (0)

/*
 * Note that the square of the distance from point B to the straight line AD is dB,
 * and the square of the distance from point C to the straight line AD is dC.
 * When (dB <= EPS && dC <= EPS), the line AD is considered to fit the spline.
 */
bool ClipPath::CheckoutSplineError(const Spline& spline) const
{
    float dx = spline.d.x - spline.a.x;
    float dy = spline.d.y - spline.a.y;
    float c = dx * spline.a.y - dy * spline.a.x;
    float deltB = dy * spline.b.x - dx * spline.b.y + c;
    deltB = deltB * deltB;
    float deltC = dy * spline.c.x - dx * spline.c.y + c;
    deltC = deltC * deltC;
    float delt = EPS * (dx * dx + dy * dy);
    if (deltB <= delt && deltC <= delt) {
        return true;
    }
    return false;
}

void ClipPath::MidPointOfLine(const PointF& a, const PointF& b, PointF& mid) const
{
    mid.x = a.x + (b.x - a.x) / 2; // 2: half
    mid.y = a.y + (b.y - a.y) / 2; // 2: half
}

void ClipPath::SplitSpline(Spline& s1, Spline& s2) const
{
    PointF ab, bc, cd;
    PointF abbc, bccd;
    PointF e;

    MidPointOfLine(s1.a, s1.b, ab);
    MidPointOfLine(s1.b, s1.c, bc);
    MidPointOfLine(s1.c, s1.d, cd);
    MidPointOfLine(ab, bc, abbc);
    MidPointOfLine(bc, cd, bccd);
    MidPointOfLine(abbc, bccd, e);

    s2.a = e;
    s2.b = bccd;
    s2.c = cd;
    s2.d = s1.d;

    s1.b = ab;
    s1.c = abbc;
    s1.d = e;
}

void ClipPath::SplineDecompose(Spline& s, ClipPolygon& polygon) const
{
    List<Spline> list;
    list.PushBack(s);
    while (!list.IsEmpty()) {
        Spline s1 = list.Front();
        list.PopFront();
        if (CheckoutSplineError(s1)) {
            polygon.AddPoint(s1.a);
        } else {
            Spline s2;
            SplitSpline(s1, s2);
            list.PushFront(s2);
            list.PushFront(s1);
        }
    }
    polygon.AddPoint(s.d);
}

void ClipPath::GeneratePolygon(ClipPolygon& polygon) const
{
    ListNode<PointF>* pointIter = points_.Begin();
    ListNode<ClipPathCmd>* iter = cmd_.Begin();
    for (; iter != cmd_.End() && pointIter != points_.End(); iter = iter->next_) {
        switch (iter->data_) {
            case CMD_MOVE_TO: {
                if (!polygon.points_.IsEmpty()) {
                    return;
                }
                polygon.AddPoint(startPos_);
                break;
            }
            case CMD_LINE_TO: {
                PointF end = pointIter->data_;
                pointIter = pointIter->next_;
                polygon.AddPoint(end);
                break;
            }
            case CMD_CURVE_TO: {
                if (polygon.points_.IsEmpty()) {
                    return;
                }
                Spline s;
                s.a =  polygon.points_.Back();
                s.b = pointIter->data_;
                pointIter = pointIter->next_;
                if (pointIter == points_.End()) {
                    return;
                }
                s.c = pointIter->data_;
                pointIter = pointIter->next_;
                if (pointIter == points_.End()) {
                    return;
                }
                s.d = pointIter->data_;
                pointIter = pointIter->next_;
                SplineDecompose(s, polygon);
                break;
            }
            default:
                break;
        }
    }
}

ClipPath& ClipPath::MoveTo(const PointF& point)
{
    startPos_ = point;
    /* If the previous command is also CMD_MOVE_TO, the previous command is overwritten. */
    if ((cmd_.Size() != 0) && (cmd_.Tail()->data_ == CMD_MOVE_TO)) {
        points_.Tail()->data_ = point;
        return *this;
    }
    cmd_.PushBack(CMD_MOVE_TO);
    return *this;
}

ClipPath& ClipPath::LineTo(const PointF& point)
{
    if (cmd_.Size() == 0) {
        MoveTo(point);
    } else {
        points_.PushBack(point);
        cmd_.PushBack(CMD_LINE_TO);
    }
    return *this;
}

ClipPath& ClipPath::CurveTo(const PointF& control1, const PointF& control2, const PointF& end)
{
    if (cmd_.Size() == 0) {
        MoveTo(end);
    } else {
        points_.PushBack(control1);
        points_.PushBack(control2);
        points_.PushBack(end);
        cmd_.PushBack(CMD_CURVE_TO);
    }
    return *this;
}

/* The ArcInner function can be used to fit the arc within 90 degrees by Bezier curve */
void ClipPath::ArcInner(const PointF& center, float radius, int16_t startAngle, int16_t endAngle)
{
    if (radius > 0) {
        float sinA = radius * Sin(startAngle);
        float cosA = radius * Sin(QUARTER_IN_DEGREE - startAngle);
        float sinB = radius * Sin(endAngle);
        float cosB = radius * Sin(QUARTER_IN_DEGREE - endAngle);
        float x0 = center.x + cosA;
        float y0 = center.y + sinA;
        float x3 = center.x + cosB;
        float y3 = center.y + sinB;
        int16_t addAngle = endAngle - startAngle;
        // a = 4.0 * tan(angle / 4) / 3.0;
        float a = 4.0 * Sin(addAngle / 4.0) / Sin(QUARTER_IN_DEGREE - addAngle / 4.0) / 3.0;
        float x1 = x0 - a * (y0 - center.y);
        float y1 = y0 + a * (x0 - center.x);
        float x2 = x3 + a * (y3 - center.y);
        float y2 = y3 - a * (x3 - center.x);

        if (cmd_.Size() != 0) {
            LineTo({x0, y0});
        } else {
            MoveTo({x0, y0});
        }
        CurveTo({x1, y1}, {x2, y2}, {x3, y3});
    }
}

ClipPath& ClipPath::Arc(const PointF& center, float radius, int16_t startAngle, int16_t endAngle)
{
    if (radius > 0) {
        startAngle = (startAngle % CIRCLE_IN_DEGREE + CIRCLE_IN_DEGREE) % CIRCLE_IN_DEGREE;
        endAngle = (endAngle % CIRCLE_IN_DEGREE + CIRCLE_IN_DEGREE) % CIRCLE_IN_DEGREE;
        if (startAngle > endAngle) {
            endAngle += CIRCLE_IN_DEGREE;
        }
        int16_t tmpAngle = QUARTER_IN_DEGREE;
        while (startAngle < endAngle) {
            while (tmpAngle <= startAngle) {
                tmpAngle += QUARTER_IN_DEGREE;
            }
            if (tmpAngle > endAngle) {
                tmpAngle = endAngle;
            }
            ArcInner(center, radius, startAngle, tmpAngle);
            startAngle = tmpAngle;
        }
    }
    return *this;
}

ClipPath& ClipPath::Circle(const PointF& center, float radius)
{
    if (radius > 0) {
        /*
         * h(a) = (4 / 3) * (1 - cos(a / 2)) / sin(a / 2)
         * h(90) = 0.552
         */
        float h = 0.552 * radius;
        float x0 = center.x + radius;
        float y0 = center.y;
        float x3 = center.x;
        float y3 = center.y + radius;
        float x1 = x0;
        float y1 = y0 + h;
        float x2 = x3 + h;
        float y2 = y3;
        MoveTo({x0, y0});
        CurveTo({x1, y1}, {x2, y2}, {x3, y3});
        x0 = x3;
        y0 = y3;
        x3 = center.x - radius;
        y3 = center.y;
        x1 = x0 - h;
        y1 = y0;
        x2 = x3;
        y2 = y3 + h;
        CurveTo({x1, y1}, {x2, y2}, {x3, y3});
        x0 = x3;
        y0 = y3;
        x3 = center.x;
        y3 = center.y - radius;
        x1 = x0;
        y1 = y0 - h;
        x2 = x3 - h;
        y2 = y3;
        CurveTo({x1, y1}, {x2, y2}, {x3, y3});
        x0 = x3;
        y0 = y3;
        x3 = center.x + radius;
        y3 = center.y;
        x1 = x0 + h;
        y1 = y0;
        x2 = x3;
        y2 = y3 - h;
        CurveTo({x1, y1}, {x2, y2}, {x3, y3});
    }
    return *this;
}

void ClipImageBlitter::DrawHorSpan(const List<Span>& span, int16_t yCur)
{
    if (src_ == nullptr) {
        return;
    }

    for (int16_t y = iy_; y < yCur; y++) {
        DrawHorLine(0, y, src_->header.width, OPA_TRANSPARENT);
    }
    int16_t index = 0;
    auto iter = span.Begin();
    while (iter != span.End()) {
        DrawHorLine(index, yCur, iter->data_.left - index, OPA_TRANSPARENT);
        DrawHorLine(iter->data_.left, yCur, iter->data_.right - iter->data_.left + 1, iter->data_.opa);
        index = iter->data_.right + 1;
        iter = iter->next_;
    }
    DrawHorLine(index, yCur, src_->header.width - index, OPA_TRANSPARENT);
    iy_ = yCur + 1;
}

void ClipImageBlitter::Finish()
{
    if (src_ == nullptr) {
        return;
    }

    for (int16_t y = iy_; y < src_->header.height; y++) {
        DrawHorLine(0, y, src_->header.width, OPA_TRANSPARENT);
    }
}

void ClipImageBlitter::DrawPixel(int16_t x, int16_t y, uint8_t opa)
{
    if (x < 0 || x > src_->header.width - 1 || y < 0 || y > src_->header.height - 1) {
        return;
    }

    int32_t offset = src_->header.width * y + x;
    switch (src_->header.colorMode) {
        case ARGB8888: {
            Color32* buffer = reinterpret_cast<Color32*>(const_cast<uint8_t*>(src_->data));
            buffer[offset].alpha = buffer[offset].alpha * opa / OPA_OPAQUE;
            break;
        }
        default: {
            GRAPHIC_LOGE("Only images in ARGB8888 format are supported!");
            break;
        }
    }
}

void ClipImageBlitter::DrawHorLine(int16_t x, int16_t y, int16_t width, uint8_t opa)
{
    if (width < 0 || opa == OPA_OPAQUE) {
        return;
    }

    for (int16_t i = 0; i < width; i++) {
        DrawPixel(x + i, y, opa);
    }
}

void ClipUtils::CreateNewSpan(List<Span>& list, ListNode<Span>* node, int16_t left, int16_t right, uint8_t opa)
{
    Span insert;
    insert.left = left;
    insert.right = right;
    insert.opa = opa;
    list.Insert(node, insert);
}

void ClipUtils::InsertSpan(List<Span>& curList, int16_t left, int16_t right, uint8_t opa)
{
    if (left > right || opa == OPA_TRANSPARENT) {
        return;
    }

    auto iter = curList.Begin();
    auto endIt = curList.End();
    while (iter != endIt) {
        Span& curSpan = iter->data_;
        if (right < curSpan.left) {
            break;
        }
        if (left > curSpan.right) {
            iter = iter->next_;
            continue;
        }

        if (left < curSpan.left) {
            CreateNewSpan(curList, iter, left, curSpan.left - 1, opa);
        } else if (left > curSpan.left) {
            CreateNewSpan(curList, iter, curSpan.left, left - 1, curSpan.opa);
            curSpan.left = left;
        }

        if (right > curSpan.right) {
            curSpan.opa = MATH_MAX(curSpan.opa, opa);
            left = curSpan.right + 1;
            iter = iter->next_;
            continue;
        } else if (right < curSpan.right) {
            CreateNewSpan(curList, iter->next_, right + 1, curSpan.right, curSpan.opa);
            curSpan.right = right;
        }
        curSpan.opa = MATH_MAX(curSpan.opa, opa);
        return;
    }
    CreateNewSpan(curList, iter, left, right, opa);
}

void ClipUtils::MergeSpan(List<Span>& s)
{
    auto iter = s.Begin();
    auto endIt = s.End();
    while (iter != endIt) {
        auto next = iter->next_;
        while (next != endIt) {
            if (next->data_.left - 1 == iter->data_.left && next->data_.opa == iter->data_.opa) {
                iter->data_.right = next->data_.right;
                next = s.Remove(next);
                continue;
            }
            break;
        }
        iter = iter->next_;
    }
}

void ClipUtils::ClearSpanTable()
{
    if (span0_ != nullptr) {
        span0_->Clear();
        delete span0_;
        span0_ = nullptr;
    }

    if (span1_ != nullptr) {
        span1_->Clear();
        delete span1_;
        span1_ = nullptr;
    }
}

void ClipUtils::DrawAntiAliasedPoints(int16_t yCur)
{
    auto iter = aaList_.Begin();
    while (iter != aaList_.End()) {
        if (iter->data_.y >= yCur + 1) {
            break;
        }
        bool remove = false;
        while (iter->data_.y < yCur + 1) {
            uint8_t opa =  MATH_ROUND(RF_PART(iter->data_.y) * OPA_OPAQUE);
            InsertSpan(*span0_, iter->data_.x, iter->data_.x, opa);
            InsertSpan(*span1_, iter->data_.x, iter->data_.x, OPA_OPAQUE - opa);
            iter->data_.y += iter->data_.dy;
            iter->data_.x += iter->data_.sx;
            iter->data_.xIndex--;
            if (iter->data_.xIndex <= 0) {
                iter = aaList_.Remove(iter);
                remove = true;
                break;
            }
        }
        if (!remove) {
            iter = iter->next_;
        }
    }
}

void ClipUtils::CreateEdgeList(const ClipPath& path)
{
    ClipPolygon polygon;
    path.GeneratePolygon(polygon);
    Graphic::Vector<PointF>& points = polygon.points_;
    maxY_ = floor(polygon.bound_.bottom);
    minY_ = ceil(polygon.bound_.top);

    uint16_t size = points.Size();
    for (int16_t i = 0; i < size; i++) {
        float x1 = points[i].x;
        float y1 = points[i].y;
        float x2 = points[(i + 1) % size].x;
        float y2 = points[(i + 1) % size].y;

        if (y1 > y2) {
            SWAP_FLOAT(x1, x2);
            SWAP_FLOAT(y1, y2);
        }

        /* Insert the non steep edges to aaList_ */
        bool steep = MATH_ABS(y1 - y2) > MATH_ABS(x1 - x2);
        if (!steep) {
            AAEdge edge;
            float dy = (y1 - y2) / (x1 - x2);
            edge.dy = MATH_ABS(dy);
            if (x1 > x2) {
                edge.x = floor(x1);
                edge.y = y1 + (x1 - edge.x) * edge.dy;
                edge.sx = -1;
                edge.xIndex = edge.x - ceil(x2) + 1;
            } else {
                edge.x = ceil(x1);
                edge.y = y1 + (edge.x - x1) * edge.dy;
                edge.sx = 1;
                edge.xIndex = floor(x2) - edge.x + 1;
            }
            if (edge.xIndex > 0) {
                auto it = aaList_.Begin();
                while (it != aaList_.End()) {
                    if (edge.y <= it->data_.y) {
                        break;
                    }
                    it = it->next_;
                }
                aaList_.Insert(it, edge);
            }
        }

        /* Insert the edges to edgeList_ */
        int16_t ymax = floor(y2);
        int16_t ymin = floor(y1) + 1;
        if (ymax < ymin) {
            continue;
        }
        float dx = (x1 - x2) / (y1 - y2);
        Edge p;
        p.ymax = ymax;
        p.ymin = ymin;
        p.x = x1 + dx * (ymin - y1);
        p.dx = dx;
        auto iter = edgeList_.Begin();
        while (iter != edgeList_.End()) {
            if (p.ymin <= iter->data_.ymin) {
                break;
            }
            iter = iter->next_;
        }
        edgeList_.Insert(iter, p);
    }
}

void ClipUtils::PerformScan(const ClipPath& path, Blitter& blitter)
{
    CreateEdgeList(path);

    span0_ = new List<Span>();
    span1_ = new List<Span>();
    List<Edge> activeEdgeList;
    for (int16_t i = minY_; i <= maxY_; ++i) {
        /* Calculate the anti aliasing point of non steep line in each row */
        DrawAntiAliasedPoints(i);

        /*
         * When the ymin of the edge is equal to the current line, the edge is inserted into the AET.
         * Sort by x ascending (Sort by dx ascending when x is equal)
         */
        auto iter1 = edgeList_.Begin();
        while (iter1 != edgeList_.End()) {
            if (iter1->data_.ymin == i) {
                auto iter2 = activeEdgeList.Begin();
                while (iter2 != activeEdgeList.End()) {
                    if (iter1->data_.x < iter2->data_.x) {
                        break;
                    }
                    if (iter1->data_.x == iter2->data_.x && iter1->data_.dx < iter2->data_.dx) {
                        break;
                    }
                    iter2 = iter2->next_;
                }
                activeEdgeList.Insert(iter2, iter1->data_);
                iter1 = edgeList_.Remove(iter1);
                continue;
            }
            break;
        }
        /* Traverse the activeEdgeList, pair the edges and insert the spans */
        auto iter = activeEdgeList.Begin();
        auto endIt = activeEdgeList.End();
        while (iter != endIt && iter->next_ != endIt) {
            int16_t xLeft = ceil(iter->data_.x);
            int16_t xRight = floor(iter->next_->data_.x);
            InsertSpan(*span0_, xLeft, xRight, OPA_OPAQUE);

            /* Anti aliasing on both sides */
            uint8_t opa =  MATH_ROUND(RF_PART(iter->data_.x) * OPA_OPAQUE);
            InsertSpan(*span0_, iter->data_.x, iter->data_.x, opa);
            InsertSpan(*span0_, iter->data_.x + 1, iter->data_.x + 1, OPA_OPAQUE - opa);
            opa =  MATH_ROUND(RF_PART(iter->next_->data_.x) * OPA_OPAQUE);
            InsertSpan(*span0_, iter->next_->data_.x, iter->next_->data_.x, opa);
            InsertSpan(*span0_, iter->next_->data_.x + 1, iter->next_->data_.x + 1, OPA_OPAQUE - opa);

            iter = iter->next_->next_;
        }

        /* Remove the edge with (ymax == i) in active edge list */
        iter = activeEdgeList.Begin();
        while (iter != endIt) {
            if (iter->data_.ymax == i) {
                iter = activeEdgeList.Remove(iter);
            } else {
                iter->data_.x += iter->data_.dx;
                iter = iter->next_;
            }
        }

        /* Merge the span of current row and do blit */
        MergeSpan(*span0_);
        blitter.DrawHorSpan(*span0_, i);

        /* Clear the span of current row, then swap span0_ and span1_ */
        span0_->Clear();
        List<Span>* tmp;
        tmp = span0_;
        span0_ = span1_;
        span1_ = tmp;
    }
    blitter.Finish();

    ClearSpanTable();
}
};