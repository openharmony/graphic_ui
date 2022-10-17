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

#ifndef UI_TEST_CHART_PILLAR_H
#define UI_TEST_CHART_PILLAR_H

#include "components/ui_chart.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "ui_test.h"

namespace OHOS {
constexpr char* UI_TEST_ADD_DATA = "add_data";
constexpr char* UI_TEST_DELETE_DATA = "delete_data";
constexpr char* UI_TEST_CLEAR_DATA = "clear_data";
constexpr char* UI_TEST_FLIP = "flip";
constexpr char* UI_TEST_AXIS_COLOR = "axis_color";
constexpr char* UI_TEST_AXIS_NOT_VISIBLE = "axis_not_visible";

class UITestChartPillar : public UITest, public UIView::OnClickListener {
public:
    UITestChartPillar() : dataSerial_() {}
    ~UITestChartPillar() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    void SetUpButton(UILabelButton* btn, const char* title, const char* id);

    bool OnClick(UIView& view, const ClickEvent& event) override;

    void UIKitChartPillarTestAddDataSerial001();
    void UIKitChartPillarTestEnableReverse002();
    void UIKitChartPillarTestSetAxisLineColor003();
    void UIKitChartPillarTestSetAxisLineVisible004();

private:
    void SetLastPos(UIView* view);
    void InnerDeleteChildren(UIView* view) const;
    static constexpr uint8_t DATA_NUM = 3;
    UIChartDataSerial *dataSerial_[DATA_NUM];
    uint8_t curDataIndex_ = 0;

    UIScrollView* container_ = nullptr;
    UIChartPillar* chart_ = nullptr;
    UILabelButton* addDataSerialBtn_ = nullptr;
    UILabelButton* deleteDataSerialBtn_ = nullptr;
    UILabelButton* clearDataSerialBtn_ = nullptr;
    UILabelButton* reverseBtn_ = nullptr;
    UILabelButton* setAxisColorBtn_ = nullptr;
    UILabelButton* setAxisVisibleBtn_ = nullptr;

    int16_t lastX_ = 0;
    int16_t lastY_ = 0;
};
} // namespace OHOS
#endif // UI_TEST_CHART_PILLAR_H
