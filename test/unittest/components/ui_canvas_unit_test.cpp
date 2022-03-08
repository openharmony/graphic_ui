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

#include "components/root_view.h"
#include "components/ui_canvas.h"
#include "components/ui_view_group.h"
#include "components/ui_view_group.h"

#include <climits>
#include <gtest/gtest.h>
#include "test_resource_config.h"
using namespace testing::ext;
namespace OHOS {
namespace {
    const int16_t POS_X = 50;
    const int16_t POS_Y = 100;
    const uint16_t WIDTH = 100;
    const uint16_t HEIGHT = 100;
    const int16_t START1_X = 10;
    const int16_t START1_Y = 20;
    const int16_t LINE1_X = 40;
    const int16_t LINE1_Y = 100;
    const int16_t LINE2_X = 50;
    const int16_t LINE2_Y = 120;
    const int16_t CENTER_X = 150;
    const int16_t CENTER_Y = 150;
    const int16_t RADIUS = 50;
    const int16_t START_ANGLE = 30;
    const int16_t END_ANGLE = 250;
    const int16_t RECT_X = 250;
    const int16_t RECT_Y = 50;
    const int16_t RECT_WIDTH = 100;
    const int16_t RECT_HEIGHT = 50;
    const float LINE_OFFSET1 = 10.0;
    const float LINE_OFFSET2 = 50.0;
    const float LINE_OFFSET3 = 150.0;
    const int16_t LINE_WIDTH1 = 1;
    const int16_t LINE_WIDTH2 = 5;
    const int16_t LINE_WIDTH3 = 9;
    const double MITERLIMIT1 = 11.05;
    const double MITERLIMIT2 = 4.6;
    const double MITERLIMIT3 = -5.6;
    const int16_t IMAGE_X = 20;
    const int16_t IMAGE_Y = 10;
    const int16_t IMAGE_WIDTH = 20;
    const int16_t IMAGE_HEIGHT = 10;
    const uint8_t FONT_SIZE = 15;
    const int16_t LETTER_SPACE = 2;
    const float SCALE_X = 0.5;
    const float SCALE_Y = 0.5;
    const float SHEAR_X = -0.5;
    const float SHEAR_Y = 0.5;
    const float TRANSLATE_X = 30;
    const float TRANSLATE_Y = 10;
    const float GLOBALALPHA = 0.5;
    const int16_t DOUBLENUMBER = 2;
    const double START_X = 180.0;
    const double START_Y = 140.0;
    const double START_R = 10.0;
    const double END_X = 150.0;
    const double END_Y = 100.0;
    const double END_R = 80.0;
    const double COLOR_STOP_0 = 0.0;
    const double COLOR_STOP_1 = 0.3;
    const double COLOR_STOP_2 = 0.6;
    const double COLOR_STOP_3 = 1.0;
    const float ROTATE = 10;
    const int16_t LINE_X = 30;
    const int16_t LINE_Y = 70;
}

class TestUICanvas : public UICanvas {
public:
    TestUICanvas() {}
    virtual ~TestUICanvas() {}

    const UICanvasVertices* GetPath() const
    {
        return vertices_;
    }

    Point GetStartPos() const
    {
        float x;
        float y;
        if (GetPath() != nullptr) {
            vertices_->Rewind(0);
            vertices_->GenerateVertex(&x, &y);
            return { (int16_t)x, (int16_t)y };
        } else {
            return { COORD_MIN, COORD_MIN };
        }
    }

    Point GetEndPos() const
    {
        float x;
        float y;
        if (GetPath() != nullptr) {
            vertices_->LastVertex(&x, &y);
            return { (int16_t)x, (int16_t)y };
        } else {
            return { COORD_MIN, COORD_MIN };
        }
    }
};

class UICanvasTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp();
    void TearDown();
    static Paint* paint_;
    static TestUICanvas* canvas_;
};

Paint* UICanvasTest::paint_ = nullptr;
TestUICanvas* UICanvasTest::canvas_ = nullptr;
void UICanvasTest::SetUp()
{
    if (paint_ == nullptr) {
        paint_ = new Paint();
    }
    if (canvas_ == nullptr) {
        canvas_ = new TestUICanvas();
    }
}

void UICanvasTest::TearDown()
{
    if (paint_ != nullptr) {
        delete paint_;
        paint_ = nullptr;
    }
    if (canvas_ != nullptr) {
        delete canvas_;
        canvas_ = nullptr;
    }
}
/**
 * @tc.name: UICanvasSetPaintStyle_001
 * @tc.desc: Verify SetStyle function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetPaintStyle_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    Paint::PaintStyle paintStyle = Paint::PaintStyle::FILL_STYLE;

    paint_->SetStyle(Paint::PaintStyle::FILL_STYLE);
    EXPECT_EQ(paint_->GetStyle(), paintStyle);
}

/**
 * @tc.name: UICanvasSetStrokeWidth_001
 * @tc.desc: Verify SetStrokeWidth function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetStrokeWidth_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    paint_->SetStrokeWidth(WIDTH);
    EXPECT_EQ(paint_->GetStrokeWidth(), WIDTH);
}

/**
 * @tc.name: UICanvasSetStrokeColor_001
 * @tc.desc: Verify SetStrokeColor function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetStrokeColor_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::Red();

    paint_->SetStrokeColor(color);
    EXPECT_EQ(paint_->GetStrokeColor().full, color.full);
}

/**
 * @tc.name: UICanvasSetFillColor_001
 * @tc.desc: Verify SetFillColor function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetFillColor_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::Red();

    paint_->SetFillColor(color);
    EXPECT_EQ(paint_->GetFillColor().full, color.full);
}

/**
 * @tc.name: UICanvasSetOpacity_001
 * @tc.desc: Verify SetOpacity function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetOpacity_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    paint_->SetOpacity(OPA_OPAQUE);
    EXPECT_EQ(paint_->GetOpacity(), OPA_OPAQUE);
}

/**
 * @tc.name: UICanvasSetStartPosition_001
 * @tc.desc: Verify SetStartPosition function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasSetStartPosition_001, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->SetStartPosition({POS_X, POS_Y});
    EXPECT_EQ(canvas_->GetStartPosition().x, POS_X);
    EXPECT_EQ(canvas_->GetStartPosition().y, POS_Y);
}

/**
 * @tc.name: UICanvasDrawLine_001
 * @tc.desc: Verify DrawLine function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasDrawLine_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    Paint paint;
    Point startPoint = { 0, 50 };
    Point endPoint = { 50, 100 };

    viewGroup->SetPosition(0, 0);
    viewGroup->SetWidth(WIDTH);
    viewGroup->SetHeight(HEIGHT);
    canvas_->DrawLine(startPoint, endPoint, paint);
    viewGroup->Add(canvas_);
    EXPECT_EQ(canvas_->GetStartPosition().x, endPoint.x);
    EXPECT_EQ(canvas_->GetStartPosition().y, endPoint.y);
    viewGroup->Remove(canvas_);
}

/**
 * @tc.name: UICanvasDrawCurve_001
 * @tc.desc: Verify DrawCurve function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000DSMPV
 */
HWTEST_F(UICanvasTest, UICanvasDrawCurve_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    Paint paint;
    Point startPoint = { 100, 100 };
    Point endPoint = { 150, 200 };
    Point control1Point = { 150, 100 };
    Point control2Point = { 150, 100 };

    viewGroup->SetPosition(0, 0);
    viewGroup->SetWidth(WIDTH);
    viewGroup->SetHeight(HEIGHT);
    canvas_->DrawCurve(startPoint, control1Point, control2Point, endPoint, paint);
    viewGroup->Add(canvas_);
    EXPECT_EQ(canvas_->GetStartPosition().x, endPoint.x);
    EXPECT_EQ(canvas_->GetStartPosition().y, endPoint.y);
    viewGroup->Remove(canvas_);
}

/**
 * @tc.name: UICanvasBeginPath_001
 * @tc.desc: Verify BeginPath function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasBeginPath_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    EXPECT_EQ(canvas_->GetPath(), nullptr);
    canvas_->BeginPath();
    EXPECT_NE(canvas_->GetPath(), nullptr);
}

/**
 * @tc.name: UICanvasMoveTo_001
 * @tc.desc: Verify MoveTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasMoveTo_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, START1_X);
    EXPECT_EQ(end.y, START1_Y);
}

/**
 * @tc.name: UICanvasLineTo_001
 * @tc.desc: Verify LineTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasLineTo_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->LineTo({LINE1_X, LINE1_Y});
    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, LINE1_X);
    EXPECT_EQ(start.y, LINE1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, LINE1_X);
    EXPECT_EQ(end.y, LINE1_Y);
}

/**
 * @tc.name: UICanvasLineTo_002
 * @tc.desc: Verify LineTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasLineTo_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    canvas_->LineTo({LINE1_X, LINE1_Y});
    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, LINE1_X);
    EXPECT_EQ(end.y, LINE1_Y);

    canvas_->LineTo({LINE2_X, LINE2_Y});
    end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, LINE2_X);
    EXPECT_EQ(end.y, LINE2_Y);
}

#if GRAPHIC_ENABLE_ARC_FLAG
/**
 * @tc.name: UICanvasArcTo_001
 * @tc.desc: Verify ArcTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasArcTo_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);

    float sinma = RADIUS * Sin(START_ANGLE);
    float cosma = RADIUS * Sin(QUARTER_IN_DEGREE - START_ANGLE);
    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, int16_t(CENTER_X + sinma));
    EXPECT_EQ(start.y, int16_t(CENTER_Y - cosma));

    sinma = RADIUS * Sin(END_ANGLE);
    cosma = RADIUS * Sin(QUARTER_IN_DEGREE - END_ANGLE);
    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, int16_t(CENTER_X + sinma));
    EXPECT_EQ(end.y, int16_t(CENTER_Y - cosma));
}

/**
 * @tc.name: UICanvasArcTo_002
 * @tc.desc: Verify ArcTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasArcTo_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE,
                   START_ANGLE + CIRCLE_IN_DEGREE + QUARTER_IN_DEGREE);

    float sinma = RADIUS * Sin(START_ANGLE);
    float cosma = RADIUS * Sin(QUARTER_IN_DEGREE - START_ANGLE);
    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, int16_t(CENTER_X + sinma));
    EXPECT_EQ(start.y, int16_t(CENTER_Y - cosma));

    sinma = RADIUS * Sin(END_ANGLE);
    cosma = RADIUS * Sin(QUARTER_IN_DEGREE - END_ANGLE);
    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, start.x);
    EXPECT_EQ(end.y, start.y);
}

/**
 * @tc.name: UICanvasArcTo_003
 * @tc.desc: Verify ArcTo function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasArcTo_003, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    canvas_->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);

    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    float sinma = RADIUS * Sin(END_ANGLE);
    float cosma = RADIUS * Sin(QUARTER_IN_DEGREE - END_ANGLE);
    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, int16_t(CENTER_X + sinma));
    EXPECT_EQ(end.y, int16_t(CENTER_Y - cosma));
}
#endif

/**
 * @tc.name: UICanvasAddRect_001
 * @tc.desc: Verify AddRect function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasAddRect_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);

    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, RECT_X);
    EXPECT_EQ(start.y, RECT_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, 0);
    EXPECT_EQ(end.y, 0);
}

/**
 * @tc.name: UICanvasAddRect_002
 * @tc.desc: Verify AddRect function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasAddRect_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    canvas_->LineTo({LINE1_X, LINE1_Y});
    canvas_->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);

    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, 0);
    EXPECT_EQ(end.y, 0);
}

/**
 * @tc.name: UICanvasClosePath_001
 * @tc.desc: Verify ClosePath function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EVN8V
 */
HWTEST_F(UICanvasTest, UICanvasClosePath_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    canvas_->LineTo({LINE1_X, LINE1_Y});
    canvas_->ClosePath();

    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, 0);
    EXPECT_EQ(end.y, 0);
}

/**
 * @tc.name: UICanvasClosePath_002
 * @tc.desc: Verify ClosePath function, equal.
 * @tc.type: FUNC
 * @tc.require: SR000EVN8R
 */
HWTEST_F(UICanvasTest, UICanvasClosePath_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    canvas_->BeginPath();
    canvas_->MoveTo({START1_X, START1_Y});
    canvas_->LineTo({LINE1_X, LINE1_Y});
    canvas_->ClosePath();
    canvas_->DrawPath(*paint_);

    Point start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, START1_X);
    EXPECT_EQ(start.y, START1_Y);

    Point end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, 0);
    EXPECT_EQ(end.y, 0);

    canvas_->BeginPath();
    canvas_->LineTo({LINE2_X, LINE2_Y});
    canvas_->ClosePath();

    start = canvas_->GetStartPos();
    EXPECT_EQ(start.x, LINE2_X);
    EXPECT_EQ(start.y, LINE2_Y);

    end = canvas_->GetEndPos();
    EXPECT_EQ(end.x, 0);
    EXPECT_EQ(end.y, 0);
}

#if GRAPHIC_ENABLE_LINECAP_FLAG
#endif

#if GRAPHIC_ENABLE_LINEJOIN_FLAG
#endif

#if GRAPHIC_ENABLE_DASH_GENERATE_FLAG
#endif

#if GRAPHIC_ENABLE_LINEJOIN_FLAG
#endif

#if GRAPHIC_ENABLE_DASH_GENERATE_FLAG
#endif
/**
 * @tc.name: UICanvasStrokeRect_001
 * @tc.desc: Verify StrokeRect function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasStrokeRect_001, TestSize.Level1)
{
    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    Paint paint;

    viewGroup->SetPosition(0, 0);
    viewGroup->SetWidth(WIDTH);
    viewGroup->SetHeight(HEIGHT);
    canvas_->StrokeRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH, paint);
    viewGroup->Add(canvas_);
    EXPECT_EQ(canvas_->GetStartPosition().x, RECT_X);
    EXPECT_EQ(canvas_->GetStartPosition().y, RECT_Y);
    viewGroup->Remove(canvas_);

    viewGroup->SetPosition(10, 20);
    viewGroup->SetWidth(WIDTH);
    viewGroup->SetHeight(HEIGHT);
    canvas_->StrokeRect({0, 0}, RECT_HEIGHT, RECT_WIDTH, paint);
    viewGroup->Add(canvas_);
    EXPECT_EQ(canvas_->GetStartPosition().x, 0);
    EXPECT_EQ(canvas_->GetStartPosition().y, 0);
    viewGroup->Remove(canvas_);
}

/**
 * @tc.name: UICanvasSetScale_001
 * @tc.desc: Verify SetScale function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSetScale_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_CENTER;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE;
    fontStyle.letterSpace = LETTER_SPACE;

    paint_->Scale(SCALE_X, SCALE_Y);

    EXPECT_EQ(fontStyle.align, TEXT_ALIGNMENT_CENTER);
    EXPECT_EQ(fontStyle.direct, TEXT_DIRECT_LTR);
    EXPECT_EQ(fontStyle.fontName, DEFAULT_VECTOR_FONT_FILENAME);
    EXPECT_EQ(fontStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(fontStyle.letterSpace, LETTER_SPACE);
    EXPECT_EQ(paint_->GetScaleX(), SCALE_X);
    EXPECT_EQ(paint_->GetScaleY(), SCALE_Y);
}

/**
 * @tc.name: UICanvasSetTranslate_001
 * @tc.desc: Verify SetTranslate function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSetTranslate_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_CENTER;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE;
    fontStyle.letterSpace = LETTER_SPACE;

    paint_->Translate(TRANSLATE_X, TRANSLATE_Y);

    EXPECT_EQ(fontStyle.align, TEXT_ALIGNMENT_CENTER);
    EXPECT_EQ(fontStyle.direct, TEXT_DIRECT_LTR);
    EXPECT_EQ(fontStyle.fontName, DEFAULT_VECTOR_FONT_FILENAME);
    EXPECT_EQ(fontStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(fontStyle.letterSpace, LETTER_SPACE);
    EXPECT_EQ(paint_->GetTranslateX(), TRANSLATE_X);
    EXPECT_EQ(paint_->GetTranslateY(), TRANSLATE_Y);
}

/**
 * @tc.name: UICanvasTransform_001
 * @tc.desc: Verify Transform function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasTransform_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_CENTER;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE;
    fontStyle.letterSpace = LETTER_SPACE;

    paint_->Transform(SCALE_X, SHEAR_X, SHEAR_Y, SCALE_Y, TRANSLATE_X, TRANSLATE_Y);

    EXPECT_EQ(fontStyle.align, TEXT_ALIGNMENT_CENTER);
    EXPECT_EQ(fontStyle.direct, TEXT_DIRECT_LTR);
    EXPECT_EQ(fontStyle.fontName, DEFAULT_VECTOR_FONT_FILENAME);
    EXPECT_EQ(fontStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(fontStyle.letterSpace, LETTER_SPACE);
    EXPECT_EQ(paint_->GetScaleX(), SCALE_X);
    EXPECT_EQ(paint_->GetScaleY(), SCALE_Y);
    EXPECT_EQ(paint_->GetTranslateX(), TRANSLATE_X);
    EXPECT_EQ(paint_->GetTranslateY(), TRANSLATE_Y);
}

/**
 * @tc.name: UICanvasSetTransform_001
 * @tc.desc: Verify SetTransform function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSetTransform_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_CENTER;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE;
    fontStyle.letterSpace = LETTER_SPACE;

    paint_->SetTransform(SCALE_X, SHEAR_X, SHEAR_Y, SCALE_Y, TRANSLATE_X, TRANSLATE_Y);

    EXPECT_EQ(fontStyle.align, TEXT_ALIGNMENT_CENTER);
    EXPECT_EQ(fontStyle.direct, TEXT_DIRECT_LTR);
    EXPECT_EQ(fontStyle.fontName, DEFAULT_VECTOR_FONT_FILENAME);
    EXPECT_EQ(fontStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(fontStyle.letterSpace, LETTER_SPACE);
    EXPECT_EQ(paint_->GetScaleX(), SCALE_X);
    EXPECT_EQ(paint_->GetScaleY(), SCALE_Y);
    EXPECT_EQ(paint_->GetTranslateX(), TRANSLATE_X);
    EXPECT_EQ(paint_->GetTranslateY(), TRANSLATE_Y);
}

/**
 * @tc.name: UICanvasGlobalAlpha_001
 * @tc.desc: Verify GlobalAlpha function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasGlobalAlpha_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    paint_->SetGlobalAlpha(GLOBALALPHA);
    EXPECT_EQ(paint_->GetGlobalAlpha(), GLOBALALPHA);
}

/**
 * @tc.name: UICanvasGlobalAlpha_002
 * @tc.desc: Verify GlobalAlpha function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasGlobalAlpha_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    ColorType color = Color::Red();
    paint_->SetStyle(Paint::PaintStyle::STROKE_FILL_STYLE);
    paint_->SetFillColor(color);
    canvas_->DrawRect({RECT_X, RECT_Y}, RECT_WIDTH, RECT_HEIGHT, *paint_);
    paint_->SetStyle(Paint::PaintStyle::FILL_STYLE);
    color = Color::Green();
    paint_->SetFillColor(color);
    paint_->SetGlobalAlpha(GLOBALALPHA);
    canvas_->DrawRect({POS_X, POS_Y}, WIDTH, HEIGHT, *paint_);

    EXPECT_EQ(paint_->GetGlobalAlpha(), GLOBALALPHA);
}

/**
 * @tc.name: UICanvasGetGlobalAlpha_001
 * @tc.desc: Verify GetGlobalAlpha function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasGetGlobalAlpha_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    paint_->SetGlobalAlpha(GLOBALALPHA);
    EXPECT_EQ(paint_->GetGlobalAlpha(), GLOBALALPHA);
}

/**
 * @tc.name: UICanvasGetGlobalAlpha_002
 * @tc.desc: Verify GetGlobalAlpha function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasGetGlobalAlpha_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::Green();
    paint_->SetStyle(Paint::PaintStyle::FILL_STYLE);
    paint_->SetFillColor(color);
    paint_->SetGlobalAlpha(GLOBALALPHA);
    canvas_->DrawRect({POS_X, POS_Y}, WIDTH, HEIGHT, *paint_);

    EXPECT_EQ(paint_->GetGlobalAlpha(), GLOBALALPHA);
}

/**
 * @tc.name: UICanvasSave_001
 * @tc.desc: Verify Save function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSave_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    ColorType color = Color::Red();
    paint_->SetFillColor(color);
    canvas_->Save(*paint_);
    EXPECT_EQ(paint_->GetFillColor().full, color.full);
}

/**
 * @tc.name: UICanvasSave_002
 * @tc.desc: Verify Save function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSave_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    ColorType color = Color::Red();
    paint_->SetFillColor(color);
    canvas_->Save(*paint_);
    canvas_->DrawRect({RECT_X, RECT_Y}, RECT_WIDTH, RECT_HEIGHT, *paint_);
    *paint_ = canvas_->Restore();
    canvas_->DrawRect({POS_X, POS_Y}, WIDTH, HEIGHT, *paint_);

    EXPECT_EQ(paint_->GetFillColor().full, color.full);
}

/**
 * @tc.name: UICanvasRestore_001
 * @tc.desc: Verify Restore function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasRestore_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    ColorType color = Color::Red();
    paint_->SetFillColor(color);
    canvas_->Save(*paint_);
    *paint_ = canvas_->Restore();

    EXPECT_EQ(paint_->GetFillColor().full, color.full);
}

/**
 * @tc.name: UICanvasRestore_002
 * @tc.desc: Verify Restore function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasRestore_002, TestSize.Level1)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    ColorType color = Color::Red();
    paint_->SetFillColor(color);
    canvas_->Save(*paint_);
    canvas_->DrawRect({POS_X, POS_Y}, RECT_WIDTH, RECT_HEIGHT, *paint_);
    *paint_ = canvas_->Restore();
    canvas_->DrawRect({RECT_X, RECT_Y}, WIDTH, HEIGHT, *paint_);

    EXPECT_EQ(paint_->GetFillColor().full, color.full);
}

/**
 * @tc.name: UICanvasSetRotate_001
 * @tc.desc: Verify SetRotate function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(UICanvasTest, UICanvasSetRotate_001, TestSize.Level0)
{
    if (canvas_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    if (paint_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }

    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_CENTER;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE;
    fontStyle.letterSpace = LETTER_SPACE;

    paint_->Rotate(ROTATE);

    EXPECT_EQ(fontStyle.align, TEXT_ALIGNMENT_CENTER);
    EXPECT_EQ(fontStyle.direct, TEXT_DIRECT_LTR);
    EXPECT_EQ(fontStyle.fontName, DEFAULT_VECTOR_FONT_FILENAME);
    EXPECT_EQ(fontStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(fontStyle.letterSpace, LETTER_SPACE);
    EXPECT_EQ(paint_->GetRotateAngle(), ROTATE);
}
} // namespace OHOS
