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

#ifndef UI_TEST_UI_PICKER_H
#define UI_TEST_UI_PICKER_H

#include "components/text_adapter.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_picker.h"
#include "components/ui_scroll_view.h"
#include "components/ui_time_picker.h"
#include "ui_test.h"

namespace OHOS {
constexpr char* UI_TEST_START_LOOP = "start_loop";
constexpr char* UI_TEST_STOP_LOOP = "stop_loop";
constexpr char* UI_TEST_GO_TO_THE_FIFTH = "go_to_the_fifth";
constexpr char* UI_TEST_FROM_LEFT_TO_RIGHT = "from_left_to_right";
constexpr char* UI_TEST_FROM_RIGHT_TO_LEFT = "from_right_to_left";
constexpr char* UI_TEST_PICKER_ADD_MARGIN = "add_margin";

class UITestUIPicker : public UITest, UIView::OnClickListener, UIPicker::SelectedListener,
    UITimePicker::SelectedListener {
public:
    UITestUIPicker() {}
    ~UITestUIPicker() {}
    void SetUp() override;
    void TearDown() override;
    bool OnClick(UIView& view, const ClickEvent& event) override;
    const UIView* GetTestView() override;
    void OnPickerStoped(UIPicker& picker) override;
    void OnTimePickerStoped(UITimePicker& picker) override;
    void CreatButtons();
    void UIKitPickerTestBase001();
    void UIKitPickerTestBase002();
    void UIKitPickerTestTimePicker001();

private:
    void SetLastPos(UIView* view);
    void SetUpButton(UILabelButton* btn, const char* title, const char* id);
    UILabelButton* setLoopBtn_ = nullptr;
    UILabelButton* setLoopOffBtn_ = nullptr;
    UILabelButton* setSelectBtn_ = nullptr;
    UILabelButton* setLeftToRightBtn_ = nullptr;
    UILabelButton* setRightToLeftBtn_ = nullptr;
    UILabelButton* setMarginBtn_ = nullptr;
    UILabel* selectIndex_ = nullptr;
    UILabel* selectTime_ = nullptr;
    UIScrollView* container_ = nullptr;
    UIPicker* picker1_ = nullptr;
    UIPicker* picker3_ = nullptr;
    UITimePicker* picker2_ = nullptr;
    int16_t lastX_ = 0;
    int16_t lastY_ = 0;
    int16_t margin_ = 0;
};
} // namespace OHOS
#endif // UI_TEST_UI_PICKER_H
