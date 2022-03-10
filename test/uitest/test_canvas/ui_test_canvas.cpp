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

#include "ui_test_canvas.h"

#include "common/screen.h"
#include "components/ui_label.h"
#include "test_resource_config.h"
namespace OHOS {
void UITestCanvas::SetUp()
{
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->Resize(Screen::GetInstance().GetWidth(),
                           Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
        container_->SetHorizontalScrollState(false);
        container_->SetThrowDrag(true);
    }
    positionY_ = 0;
}

void UITestCanvas::TearDown()
{
    DeleteChildren(container_);
    container_ = nullptr;
}

const UIView* UITestCanvas::GetTestView()
{
    RM008UIKitCanvasTest001();
    RM011CanvasScale001();
    RM011CanvasRotate001();
    RM012globalAlpha001();
    RM012SaveOrRestore002();
    UIKitCanvasTestDrawLine001();
    UIKitCanvasTestDrawLine002();
    UIKitCanvasTestDrawCurve001();
    UIKitCanvasTestDrawCurve002();
    UIKitCanvasTestDrawRect001();
    UIKitCanvasTestDrawRect002();
    UIKitCanvasTestDrawRect003();
    UIKitCanvasTestDrawCircle001();
    UIKitCanvasTestDrawCircle002();
    UIKitCanvasTestDrawCircle003();
    UIKitCanvasTestDrawArc001();
    UIKitCanvasTestDrawImage001();
    UIKitCanvasTestDrawLabel001();
    UIKitCanvasTestDrawSector001();
    UIKitCanvasTestClear001();
    UIKitCanvasTestDrawPath001();
    UIKitCanvasTestDrawPath002();
    UIKitCanvasTestDrawPath003();
    UIKitCanvasTestDrawPath004();
    UIKitCanvasTestDrawPath005();
    UIKitCanvasTestDrawPath006();
    UIKitCanvasTestDrawPath007();
    UIKitCanvasTestDrawPath008();
    UIKitCanvasTestDrawPath009();
    UIKitCanvasTestDrawPath010();
    UIKitCanvasTestDrawPath011();
    UIKitCanvasTestDrawPath012();
    UIKitCanvasTestDrawPath013();
    UIKitCanvasTestDrawPath014();
    UIKitCanvasTestDrawPath015();
    UIKitCanvasTestDrawPath016();
    UIKitCanvasTestDrawPath017();
    UIKitCanvasTestDrawPath018();
    UIKitCanvasTestDrawPath019();
    UIKitCanvasTestDrawPath020();
    UIKitCanvasTestDrawPath021();
    UIKitCanvasTestDrawPath022();
    UIKitCanvasTestDrawPath023();
    UIKitCanvasTestDrawPath024();
    UIKitCanvasTestDrawPath025();
    UIKitCanvasTestDrawPath026();
    UIKitCanvasTestDrawPath027();
    UIKitCanvasTestDrawPath028();
    UIKitCanvasTestDrawPath029();
    UIKitCanvasTestDrawPath030();
    UIKitCanvasTestDrawPath031();
    UIKitCanvasTestDrawPath032();
    UIKitCanvasTestDrawPath033();
    UIKitCanvasTestDrawPath034();
    return container_;
}

void UITestCanvas::CreateTitleLabel(const char* title)
{
    UILabel* titleLabel = new UILabel();
    titleLabel->SetPosition(TEXT_DISTANCE_TO_LEFT_SIDE, positionY_, Screen::GetInstance().GetWidth(), TITLE_HEIGHT);
    titleLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    titleLabel->SetText(title);
    container_->Add(titleLabel);
    positionY_ += TITLE_HEIGHT + HEIGHT_GAP; // 8: gap
}

UICanvas* UITestCanvas::CreateCanvas()
{
    UICanvas* canvas = new UICanvas();
    canvas->SetHeight(CANVAS_HEIGHT);
    canvas->SetWidth(CANVAS_WIDTH);
    canvas->SetPosition(VIEW_DISTANCE_TO_LEFT_SIDE, positionY_);
    canvas->SetStyle(STYLE_BACKGROUND_COLOR, Color::Gray().full);
    container_->Add(canvas);
    positionY_ += CANVAS_HEIGHT + GAP;
    return canvas;
}

void UITestCanvas::UIKitCanvasTestDrawLine001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制直线");
    UICanvas* canvas = CreateCanvas();
    Paint paint;
    // {0, 10}: Start point coordinates x, y; {50, 10}: end point coordinates x, y
    canvas->DrawLine({0, START1_X}, {LINE4_X, START1_X}, paint);
}

void UITestCanvas::UIKitCanvasTestDrawLine002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制直线");
    UICanvas* canvas = CreateCanvas();

    Paint paint;

    paint.SetStrokeWidth(LINE_WIDTH5);            // 5: line width
    canvas->SetStartPosition({START_X, START_Y}); // {50, 10}: Start point coordinates x, y;
    canvas->DrawLine({LINE2_X, RECT_Y}, paint);   // {100, 50}: end point coordinates x, y
}

void UITestCanvas::UIKitCanvasTestDrawCurve001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制曲线");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStrokeColor(Color::Red());
    canvas->DrawCurve({LINE2_X, RECT_Y}, {LINE12_X, RECT_Y}, {LINE12_X, RECT_Y},
                      {LINE12_X, LINE1_Y}, paint);
}

void UITestCanvas::UIKitCanvasTestDrawCurve002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制曲线");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStrokeColor(Color::Red());
    canvas->DrawCurve({LINE2_X, LINE_CURVE_Y}, {LINE12_X, LINE_CURVE_Y},
                      {LINE12_X, LINE1_Y}, paint);
}

void UITestCanvas::UIKitCanvasTestDrawRect001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("矩形填充");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::FILL_STYLE);
    paint.SetFillColor(Color::Yellow());
    paint.SetStrokeWidth(LINE_WIDTH30); // 30: line width
    // {100, 10}: left corner coordinates point, 50: width, 50: rectangle style
    canvas->DrawRect({LINE1_Y, START1_Y}, LINE4_X, TRANSLATE_Y, paint);
}

void UITestCanvas::UIKitCanvasTestDrawRect002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("矩形描边");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::STROKE_STYLE);
    paint.SetStrokeColor(Color::Blue());
    // {200, 10}: left corner coordinates point, 50: width, 50: rectangle style
    canvas->DrawRect({LINE28_X, START2_Y}, LINE4_X, LINE_RECT_Y50, paint);
}

void UITestCanvas::UIKitCanvasTestDrawRect003()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("矩形填充 + 描边");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::STROKE_FILL_STYLE);
    paint.SetFillColor(Color::Yellow());
    paint.SetStrokeColor(Color::Blue());
    // {300, 10}: left corner coordinates point, 50: width, 50: rectangle style
    canvas->DrawRect({LINE_RECT_X300, LINE_RECT_Y10}, LINE_RECT_WIDTH50, LINE_RECT_HEIGHT50, paint);
}

void UITestCanvas::UIKitCanvasTestDrawCircle001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("圆形填充");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::FILL_STYLE);
    paint.SetStrokeColor(Color::Yellow());
    paint.SetFillColor(Color::Yellow());
    paint.SetStrokeWidth(LINE_WIDTH10); // 10: line width
    paint.SetOpacity(OPARCITY_127);     // 127: opacity
    // {100, 100}: circle center coordinates, 30: circle radius
    canvas->DrawCircle({LINE_CURVE_X100, LINE_CURVE_Y100}, LINE_CURVE_R30, paint);
}

void UITestCanvas::UIKitCanvasTestDrawCircle002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("圆形描边");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::STROKE_STYLE);
    paint.SetStrokeColor(Color::Blue());
    paint.SetStrokeWidth(LINE_WIDTH10); // 10: line width
    paint.SetOpacity(OPARCITY_127);     // 127: opacity
    // {200, 100}: circle center coordinates, 30: circle radius
    canvas->DrawCircle({LINE_CURVE_X200, LINE_CURVE_Y100}, LINE_CURVE_R30, paint);
}

void UITestCanvas::UIKitCanvasTestDrawCircle003()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("圆形填充 + 描边");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::STROKE_FILL_STYLE);
    paint.SetFillColor(Color::Yellow());
    paint.SetStrokeColor(Color::Blue());
    paint.SetStrokeWidth(LINE_WIDTH10); // 10: line width
    paint.SetOpacity(OPARCITY_127);     // 127: opacity
    // {300, 100}: circle center coordinates, 30: circle radius
    canvas->DrawCircle({LINE_CURVE_X300, LINE_CURVE_Y100}, LINE_CURVE_R30, paint);
}

void UITestCanvas::UIKitCanvasTestDrawArc001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制弧线");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::STROKE_STYLE);
    paint.SetStrokeColor(Color::Red());
    paint.SetStrokeWidth(LINE_WIDTH10); // 10: line width
    canvas->BeginPath();

    canvas->MoveTo({LINE11_X, LINE13_Y});
    // {100, 150}: arc's center coordinates, 50: arc radius, 135: start angle, 270: end angle
    canvas->DrawArc({ARC_X100, ARC_Y150}, ARC_R50, ARC_ANGLE135, ARC_ANGLE270, paint);
}

void UITestCanvas::UIKitCanvasTestDrawImage001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制图片");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetOpacity(127); // 127: opacity
    // {200, 50}: start point coordinates
    canvas->DrawImage({ 200, 50 }, GREEN_IMAGE_PATH, paint);
}

void UITestCanvas::UIKitCanvasTestDrawLabel001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制文字");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetFillColor(Color::Blue());
    UICanvas::FontStyle fontStyle;
    fontStyle.align = TEXT_ALIGNMENT_RIGHT;
    fontStyle.direct = TEXT_DIRECT_LTR;
    fontStyle.fontName = DEFAULT_VECTOR_FONT_FILENAME;
    fontStyle.fontSize = FONT_SIZE30;         // 30: font size
    fontStyle.letterSpace = FONT_LETTERSPACE; // 10 letter space
    // {50, 50}: start point coordinates, 100: max width
    canvas->DrawLabel({LABEL_START50, LABEL_START50}, "canvas绘制字体", LABEL_WIDTH100, fontStyle, paint);
}

void UITestCanvas::UIKitCanvasTestDrawSector001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("扇形填充");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    paint.SetStyle(Paint::PaintStyle::FILL_STYLE);
    paint.SetFillColor(Color::Yellow());
    // {350, 150}: sector's center coordinates, 100: sector radius, 0: start angle, 30: end angle
    canvas->DrawSector({START_X350, START_Y150}, ARC_R100, 0, END_ANGLE30, paint);
}

void UITestCanvas::UIKitCanvasTestClear001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("清空画布，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    // {0, 10}: Start point coordinates x, y; {50, 10}: end point coordinates x, y
    canvas->DrawLine({0, START_Y}, {TRANSLATE_X, START_Y}, paint);
    canvas->Clear();
}

void UITestCanvas::UIKitCanvasTestDrawPath001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("lineTo，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath003()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("arc");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath004()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("rect");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath005()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("closePath，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath006()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath007()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + arc");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath008()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + rect");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->AddRect({RECT_X, RECT_Y}, RECT_WIDTH, RECT_HEIGHT);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath009()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + closePath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath010()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("闭合路径调用closePath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->LineTo({START1_X, START1_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath011()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + moveTo + lineTo");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->MoveTo({START2_X, START2_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath012()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + arc");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath013()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + arc + closePath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath014()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + rect");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath015()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + rect + closePath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath016()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("rect + lineTo");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath017()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("rect + moveTo + lineTo");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath018()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("rect + arc");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath019()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("arc + rect");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath020()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + arc + closePath + lineTo");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->ClosePath();
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath021()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("不调用beginPath，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->ClosePath();
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath022()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("不调用drawPath，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->ClosePath();
    canvas->LineTo({LINE1_X, LINE1_Y});
}

void UITestCanvas::UIKitCanvasTestDrawPath023()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + lineTo + closePath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath024()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("moveTo + closePath，无显示");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath025()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("多次drawPath");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->DrawPath(paint);
    paint.SetStrokeColor(Color::Blue());
    paint.SetStrokeWidth(1);
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath026()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("arc起止角度互换");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, END_ANGLE);

    canvas->MoveTo({START2_X, START2_Y});
    canvas->ArcTo({int16_t(CENTER_X + CENTER_X), CENTER_Y}, RADIUS, END_ANGLE, START_ANGLE);

    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath027()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("arc扫描范围超过360度 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y},
                  RADIUS, START_ANGLE, START_ANGLE + CIRCLE_IN_DEGREE + QUARTER_IN_DEGREE);
    canvas->ArcTo({int16_t(CENTER_X + CENTER_X), CENTER_Y}, RADIUS, END_ANGLE,
                  START_ANGLE + CIRCLE_IN_DEGREE);

    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath028()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("创建两条路径，只绘制后一条 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, START_ANGLE + CIRCLE_IN_DEGREE);

    canvas->BeginPath();
    canvas->MoveTo({START2_X, START2_Y});
    canvas->ArcTo({int16_t(CENTER_X + CENTER_X), CENTER_Y}, RADIUS, END_ANGLE,
                  START_ANGLE + CIRCLE_IN_DEGREE);

    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath029()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制两条不同样式的路径 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, START_ANGLE + CIRCLE_IN_DEGREE);
    canvas->DrawPath(paint);

    canvas->BeginPath();
    canvas->MoveTo({START2_X, START2_Y});
    canvas->ArcTo({int16_t(CENTER_X + CENTER_X), CENTER_Y}, RADIUS, END_ANGLE,
                  START_ANGLE + CIRCLE_IN_DEGREE);
    paint.SetStrokeColor(Color::Blue());
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath030()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("同一条路径绘制100遍 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({LINE1_X, LINE1_Y});
    canvas->ArcTo({CENTER_X, CENTER_Y}, RADIUS, START_ANGLE, START_ANGLE + CIRCLE_IN_DEGREE);
    canvas->AddRect({RECT_X, RECT_Y}, RECT_HEIGHT, RECT_WIDTH);
    for (uint8_t i = 0; i < 100; i++) { // 100: number of times for drawing loops
        canvas->DrawPath(paint);
    }
}

void UITestCanvas::UIKitCanvasTestDrawPath031()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制直线超出canvas范围");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({START1_X, START1_Y});
    canvas->LineTo({int16_t(LINE1_X + HORIZONTAL_RESOLUTION), LINE1_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath032()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("绘制直线传入临界值 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->MoveTo({INT16_MAX, INT16_MAX});
    canvas->LineTo({0, 0});

    canvas->MoveTo({0, 0});
    canvas->LineTo({INT16_MAX, INT16_MAX});

    canvas->MoveTo({INT16_MIN, INT16_MIN});
    canvas->LineTo({0, 0});

    canvas->MoveTo({0, 0});
    canvas->LineTo({INT16_MIN, INT16_MIN});
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath033()
{
    if (container_ == nullptr) {
        return;
    }

    CreateTitleLabel("绘制arc传入临界值 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->ArcTo({INT16_MAX, INT16_MAX}, RADIUS, START_ANGLE, END_ANGLE);
    canvas->DrawPath(paint);

    canvas->BeginPath();
    canvas->ArcTo({INT16_MIN, INT16_MIN}, RADIUS, START_ANGLE, END_ANGLE);
    paint.SetStrokeColor(Color::Red());
    canvas->DrawPath(paint);

    canvas->BeginPath();
    canvas->ArcTo({CENTER_X, CENTER_Y}, UINT16_MAX, START_ANGLE, END_ANGLE);
    paint.SetStrokeColor(Color::Yellow());
    canvas->DrawPath(paint);

    canvas->BeginPath();
    canvas->ArcTo({int16_t(CENTER_X + CENTER_X), CENTER_Y}, RADIUS, INT16_MIN, INT16_MAX);
    paint.SetStrokeColor(Color::Blue());
    canvas->DrawPath(paint);
}

void UITestCanvas::UIKitCanvasTestDrawPath034()
{
    if (container_ == nullptr) {
        return;
    }

    CreateTitleLabel("绘制rect传入临界值 ");
    UICanvas* canvas = CreateCanvas();

    Paint paint;
    canvas->BeginPath();
    canvas->AddRect({INT16_MAX, INT16_MAX}, RECT_HEIGHT, RECT_WIDTH);
    canvas->DrawPath(paint);

    canvas->BeginPath();
    canvas->AddRect({RECT_X, RECT_Y}, INT16_MAX, INT16_MAX);
    paint.SetStrokeColor(Color::Red());
    canvas->DrawPath(paint);
}

void UITestCanvas::RM008UIKitCanvasTest001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("RM008_FillStyle_Solid_单色绘制多边形和填充多边形");
    UICanvas* canvas = CreateCanvas();
    Paint paint;

    paint.SetStyle(Paint::STROKE_FILL_STYLE);
    paint.SetStrokeWidth(STROKEWIDTH2);
    paint.SetStrokeColor(Color::Orange());
    paint.SetFillColor(Color::Blue());
    canvas->BeginPath();

    canvas->MoveTo({LINE11_X, LINE13_Y});
    canvas->LineTo({LINE22_X, LINE11_Y});
    canvas->LineTo({LINE26_X, LINE13_Y});
    canvas->ArcTo({LINE26_X, LINE1_Y}, ARC_RADIUS, START1_ANGLE, END1_ANGLE);
    canvas->LineTo({LINE26_X, LINE26_Y});
    canvas->LineTo({LINE4_X, LINE2_Y});
    canvas->LineTo({LINE11_X, LINE27_Y});
    canvas->LineTo({LINE3_X, LINE11_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);
    canvas->DrawPath(paint);
}

void UITestCanvas::RM011CanvasScale001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("RM011放大和缩小Scale");
    UICanvas* canvas = CreateCanvas();
    Paint paint;
    paint.SetStrokeStyle(Color::Red());
    paint.SetStrokeWidth(STROKEWIDTH3);
    canvas->BeginPath();
    canvas->MoveTo({MOVETO5, MOVETO5});
    canvas->LineTo({LINET050, MOVETO5});
    canvas->LineTo({LINET050, LINET035});
    canvas->LineTo({MOVETO5, LINET035});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.SetStrokeStyle(Color::Green());
    paint.SetGlobalAlpha(GLOBALALPHA5);
    paint.Scale(SCALE2, SCALE4);
    canvas->BeginPath();
    canvas->MoveTo({MOVETO5, MOVETO5});
    canvas->LineTo({LINET050, MOVETO5});
    canvas->LineTo({LINET050, LINET035});
    canvas->LineTo({LINE3_X, LINE3_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.SetStrokeStyle(Color::Blue());
    paint.SetGlobalAlpha(GLOBALALPHA5);
    paint.Scale(SCALE_X, SCALE_Y);
    canvas->BeginPath();
    canvas->MoveTo({LINE3_X, LINE4_Y});
    canvas->LineTo({LINE4_X, LINE4_Y});
    canvas->LineTo({LINE4_X, LINE3_Y});
    canvas->LineTo({LINE3_X, LINE3_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::RM011CanvasRotate001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("RM011原(红)_旋转(绿)_平移(蓝)_单位矩阵(黄)_重置矩阵后再设置矩阵（橘色）");
    UICanvas* canvas = CreateCanvas();
    Paint paint;
    paint.SetStrokeStyle(Color::Red());
    paint.SetStrokeWidth(STROKE3_WIDTH);
    canvas->BeginPath();
    canvas->MoveTo({LINE8_X, LINE8_X});
    canvas->LineTo({LINE6_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE7_Y});
    canvas->LineTo({LINE8_X, LINE8_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.SetStrokeStyle(Color::Green());
    paint.Rotate(ROTATE_ANGLE);
    canvas->BeginPath();
    canvas->MoveTo({LINE8_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE7_Y});
    canvas->LineTo({LINE8_X, LINE7_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.Translate(TRANSLATE_X, TRANSLATE_Y);
    paint.SetStrokeStyle(Color::Blue());
    canvas->BeginPath();
    canvas->MoveTo({LINE8_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE7_Y});
    canvas->LineTo({LINE8_X, LINE8_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.Transform(SCALE1_X, SHEAR_X, SHEAR_Y, SCALE2_Y, TRANSLATE1_X, TRANSLATE1_Y);
    paint.SetStrokeStyle(Color::Yellow());
    canvas->BeginPath();
    canvas->MoveTo({LINE8_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE7_Y});
    canvas->LineTo({LINE8_X, LINE8_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
    paint.SetTransform(SCALE1_X, SHEAR1_X, SHEAR1_Y, SCALE2_Y, TRANSLATE1_X, TRANSLATE1_Y);
    paint.SetStrokeStyle(Color::Orange());
    canvas->BeginPath();
    canvas->MoveTo({LINE8_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE6_Y});
    canvas->LineTo({LINE6_X, LINE7_Y});
    canvas->LineTo({LINE8_X, LINE8_Y});
    canvas->ClosePath();
    canvas->DrawPath(paint);
}

void UITestCanvas::RM012globalAlpha001()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("RM012_设置图像透明度_红不透明_绿蓝_一半透明度");
    UICanvas* canvas = CreateCanvas();
    Paint paint;
    paint.SetFillColor(Color::Red());
    canvas->BeginPath();
    canvas->MoveTo({LINE11_X, LINE13_Y});
    canvas->LineTo({LINE11_X, LINE11_Y});
    canvas->LineTo({LINE12_X, LINE11_Y});
    canvas->LineTo({LINE12_X, LINE13_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);

    paint.SetGlobalAlpha(GLOBALALPHA2);
    paint.SetFillColor(Color::Green());
    canvas->BeginPath();
    canvas->MoveTo({LINE1_Y, LINE10_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->LineTo({LINE9_X, LINE2_Y});
    canvas->LineTo({LINE9_X, LINE10_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);

    paint.SetFillColor(Color::Blue());
    canvas->BeginPath();
    canvas->MoveTo({LINE14_X, LINE1_Y});
    canvas->LineTo({LINE14_X, LINE14_Y});
    canvas->LineTo({LINE15_X, LINE14_Y});
    canvas->LineTo({LINE15_X, LINE1_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);
}

void UITestCanvas::RM012SaveOrRestore002()
{
    if (container_ == nullptr) {
        return;
    }
    CreateTitleLabel("RM012_设置图像透明度_红不透明_绿蓝_一半透明度Save_Restore");
    UICanvas* canvas = CreateCanvas();
    Paint paint;
    paint.SetFillColor(Color::Red());
    canvas->BeginPath();
    canvas->MoveTo({LINE11_X, LINE13_Y});
    canvas->LineTo({LINE11_X, LINE11_Y});
    canvas->LineTo({LINE12_X, LINE11_Y});
    canvas->LineTo({LINE12_X, LINE13_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);

    paint.SetGlobalAlpha(GLOBALALPHA2);
    paint.SetFillColor(Color::Green());
    canvas->BeginPath();
    canvas->MoveTo({LINE1_Y, LINE10_Y});
    canvas->LineTo({LINE2_X, LINE2_Y});
    canvas->LineTo({LINE9_X, LINE2_Y});
    canvas->LineTo({LINE9_X, LINE10_Y});
    canvas->ClosePath();
    canvas->FillPath(paint);

    canvas->Save(paint);
    paint.SetFillColor(Color::Blue());
    canvas->BeginPath();
    canvas->MoveTo({LINE14_X, LINE1_Y});
    canvas->LineTo({LINE14_X, LINE14_Y});
    canvas->LineTo({LINE15_X, LINE14_Y});
    canvas->LineTo({LINE15_X, LINE1_Y});
    canvas->ClosePath();
    paint = canvas->Restore();
    canvas->FillPath(paint);
}
} // namespace OHOS
