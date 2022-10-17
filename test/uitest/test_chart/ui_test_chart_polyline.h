/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
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

#ifndef UI_TEST_CHART_POLYLINE_H
#define UI_TEST_CHART_POLYLINE_H

#include "components/ui_chart.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "ui_test.h"

namespace OHOS {
constexpr char* UI_TEST_POLYLINE_ADD_DATA = "add_data";
constexpr char* UI_TEST_POLYLINE_DELETE_DATA = "delete_data";
constexpr char* UI_TEST_POLYLINE_CLEAR_DATA = "clear_data";
constexpr char* UI_TEST_POLYLINE_HIGHESET_POINT = "highest_point";
constexpr char* UI_TEST_POLYLINE_LOWEST_POINT = "lowest_point";
constexpr char* UI_TEST_POLYLINE_NEW_POINT = "new_point";
constexpr char* UI_TEST_POLYLINE_FLIP = "flip";
constexpr char* UI_TEST_POLYLINE_FILL_BOTTOM = "fill_bottom";

constexpr char* UI_TEST_POLYLINE_ADD_POINT = "add_point";
constexpr char* UI_TEST_POLYLINE_SMOOTHING = "smoothing";
constexpr char* UI_TEST_POLYLINE_HIDE_POINT = "hide_point";

class UITestChartPolyline : public UITest, public UIView::OnClickListener {
public:
    UITestChartPolyline() {}
    ~UITestChartPolyline() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    void SetUpButton(UILabelButton* btn, const char* title, const char* id);

    bool OnClick(UIView& view, const ClickEvent& event) override;
    bool ClickExpand(UIView& view, UIChartDataSerial::PointStyle pointStyle);

    void UIKitChartPolylineTestAddDataSerial001();
    void UIKitChartPolylineTestEnableReverse002();
    void UIKitChartPolylineTestSetGradientBottom003();
    void UIKitChartPolylineTestAddPoints004();

private:
    void SetLastPos(UIView* view);
    void InnerDeleteChildren(UIView* view) const;
    static constexpr uint8_t DATA_NUM = 3;
    UIScrollView* container_ = nullptr;
    UIChartPolyline* chart_ = nullptr;
    UIChartDataSerial *dataSerial_[DATA_NUM] = {0};
    uint8_t curDataIndex_ = 0;

    UIChartPolyline* ECGChart_ = nullptr;
    UIChartDataSerial* ECGDataSerial_ = nullptr;
    Animator* ECGAnimator_ = nullptr;

    UILabelButton* addDataSerialBtn_ = nullptr;
    UILabelButton* deleteDataSerialBtn_ = nullptr;
    UILabelButton* clearDataSerialBtn_ = nullptr;
    UILabelButton* reverseBtn_ = nullptr;
    UILabelButton* topPointBtn_ = nullptr;
    UILabelButton* bottomPointBtn_ = nullptr;
    UILabelButton* headPointBtn_ = nullptr;
    UILabelButton* gradientBottomBtn_ = nullptr;

    UILabelButton* addPointsBtn_ = nullptr;
    UILabelButton* smoothBtn_ = nullptr;
    UILabelButton* hidePointsBtn_ = nullptr;

    int16_t lastX_ = 0;
    int16_t lastY_ = 0;
};
} // namespace OHOS
#endif // UI_TEST_CHART_POLYLINE_H
