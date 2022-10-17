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

#ifndef UI_TEST_EVENT_INJECTOR_H
#define UI_TEST_EVENT_INJECTOR_H

#include "graphic_config.h"

#if ENABLE_DEBUG
#include "components/root_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "dock/input_device.h"
#include "ui_test.h"
#include "layout/grid_layout.h"

namespace OHOS {
class TestEventInjectorView;

constexpr char* UI_TEST_UP_TO_DOWN = "up_to_down";
constexpr char* UI_TEST_DOWN_TO_UP = "down_to_up";
constexpr char* UI_TEST_LEFT_TO_RIGHT = "left_to_right";
constexpr char* UI_TEST_RIGHT_TO_LEFT = "right_to_left";
constexpr char* UI_TEST_ULEFT_TO_LRIGHT = "uleft_to_lright";
constexpr char* UI_TEST_LRIGHT_TO_ULEFT = "lright_to_uleft";
constexpr char* UI_TEST_INCREASE_DRAG_TIME = "increase_drag_time";
constexpr char* UI_TEST_DECREASE_DRAG_TIME = "decrease_drag_time";
constexpr char* UI_TEST_SET_DRAGE_TIME = "set_drage_time";

class UITestEventInjector : public UITest, public UIView::OnClickListener {
public:
    UITestEventInjector() {}
    ~UITestEventInjector() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;
    bool OnClick(UIView& view, const ClickEvent& event) override;

    void UIKitEventInjectorClickEvent001();
    void UIKitEventInjectorDragEvent002();
    void UIKitEventInjectorLongPressEvent003();
    void UIKitEventInjectorKeyEvent004();
    void UIKitEventInjectorUptoDown005();
    void UIKitEventInjectorDowntoUp006();
    void UIKitEventInjectorLefttoRight007();
    void UIKitEventInjectorRighttoLeft008();
    void UIKitEventInjectorULefttoLRight009();
    void UIKitEventInjectorLRighttoULeft010();

private:
    UIScrollView* container_ = nullptr;
    GridLayout* layout_ = nullptr;
    UILabelButton* clickBtn_ = nullptr;
    UILabelButton* dragBtn_ = nullptr;
    UILabelButton* longPressBtn_ = nullptr;
    UILabelButton* keyBtn_ = nullptr;
    UILabelButton* upToDownBtn_ = nullptr;
    UILabelButton* downToUpBtn_ = nullptr;
    UILabelButton* leftToRightBtn_ = nullptr;
    UILabelButton* rightToLeftBtn_ = nullptr;
    UILabelButton* uLeftTolRightBtn_ = nullptr;
    UILabelButton* lRightTouLeftBtn_ = nullptr;
    UILabelButton* increaseDragTimeBtn_ = nullptr;
    UILabelButton* decreaseDragTimeBtn_ = nullptr;
    UILabelButton* DragTimeDisplayBtn_ = nullptr;
    TestEventInjectorView* clickTestView_ = nullptr;
    TestEventInjectorView* dragTestView_ = nullptr;
    TestEventInjectorView* longPressTestView_ = nullptr;
    TestEventInjectorView* KeyEventTestView_ = nullptr;
    UIScrollView* scrollTestView_ = nullptr;

    int16_t lastX_ = 0;
    int16_t lastY_ = 0;
    uint16_t dragTime_ = 100; // 100: 100ms

    void InnerTest(const char* title, bool touchable, bool draggable, bool dragParent,
        const char* btnTitle, UILabelButton* btn, TestEventInjectorView*& testView);
    void SetLastPos(UIView* view);
    void SetUpButton(UILabelButton* btn, const char* title, const char* id);
    void SetUpScrollView();
    void IncreaseDragTime();
    void DecreaseDragTime();
    void DragTimeDisplay();
    void SetDragTimeDisplay(uint16_t dragTime);
};
} // namespace OHOS
#endif // UI_TEST_EVENT_INJECTOR_H
#endif // ENABLE_DEBUG
