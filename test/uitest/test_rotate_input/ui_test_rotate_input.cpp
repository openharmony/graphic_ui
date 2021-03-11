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

#include "ui_test_rotate_input.h"
#include "common/screen.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "cstdio"
#include "dock/focus_manager.h"

#if ENABLE_ROTATE_INPUT
namespace OHOS {
static int16_t g_blank = 20;
static int16_t g_listW = 200;
static int16_t g_listH = 400;
static int16_t g_scrollH = 200;
static int16_t g_scrollW = 400;
static int16_t g_buttonH = 500;
static int16_t g_buttonW = 500;
static int16_t g_smallButtonH = 80;
static int16_t g_smallButtonW = 200;
static int16_t g_swipeH = 200;
static int16_t g_swipeW = 400;
static int16_t g_sliderW = 40;
static int16_t g_sliderH = 300;
static const char* g_pickerRange[] = { "A0", "B1", "C2", "D3", "E4", "F5", "G6", "H7", "I8", "J9", "K10", "L11" };

#if ENABLE_MOTOR
void Print(MotorType motorType)
{
    switch (motorType) {
        case MotorType::MOTOR_TYPE_ONE:
            printf("MOTOR_TYPE_ONE\n");
            break;
        case MotorType::MOTOR_TYPE_TWO:
            printf("MOTOR_TYPE_TWO\n");
            break;
        default:
            break;
    }
}
#endif

void UITestRotateInput::SetUp()
{
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->SetOnTouchListener(this);
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight());
        container_->SetThrowDrag(true);
        container_->SetRotateFactor(20); // 20 : rotate factor for container
        container_->RequestFocus();
        container_->SetReboundSize(50); // 50 : rebound size
    }
    if (adapterData_ == nullptr) {
        adapterData_ = new List<const char*>();
        adapterData_->PushBack("000");
        adapterData_->PushBack("111");
        adapterData_->PushBack("222");
        adapterData_->PushBack("333");
        adapterData_->PushBack("444");
        adapterData_->PushBack("555");
        adapterData_->PushBack("666");
        adapterData_->PushBack("777");
        adapterData_->PushBack("888");
        adapterData_->PushBack("999");
        adapterData_->PushBack("///");
        adapterData_->PushBack("***");
        adapterData_->PushBack("+++");
        adapterData_->PushBack("---");
        adapterData_->PushBack("...");
        adapterData_->PushBack("@@@");
        adapterData_->PushBack("000");
        adapterData_->PushBack("111");
        adapterData_->PushBack("222");
        adapterData_->PushBack("333");
        adapterData_->PushBack("444");
        adapterData_->PushBack("555");
        adapterData_->PushBack("666");
        adapterData_->PushBack("777");
        adapterData_->PushBack("888");
        adapterData_->PushBack("999");
        adapterData_->PushBack("///");
        adapterData_->PushBack("***");
        adapterData_->PushBack("+++");
        adapterData_->PushBack("---");
        adapterData_->PushBack("...");
        adapterData_->PushBack("@@@");
    }
#if ENABLE_MOTOR
    FocusManager::GetInstance()->RegisterMotorFunc(Print);
#endif
}

void UITestRotateInput::TearDown()
{
    container_->ClearFocus();
    container_->Remove(timePicker_);
    container_->Remove(picker_);
    DeleteChildren(container_);
    container_ = nullptr;
    if (adapterData_ != nullptr) {
        adapterData_->Clear();
        delete adapterData_;
        adapterData_ = nullptr;
    }
    if (adapter_ != nullptr) {
        delete adapter_;
        adapter_ = nullptr;
    }
    lastX_ = 0;
    lastY_ = 0;
    list_ = nullptr;
    scroll_ = nullptr;
    swipe_ = nullptr;
    timePicker_ = nullptr;
    slider_ = nullptr;
    picker_ = nullptr;
}

const UIView* UITestRotateInput::GetTestView()
{
    UIKit_Rotate_Event_List_001();
    UIKit_Rotate_Event_Scroll_View_002();
    UIKit_Rotate_Event_Swipe_View_003();
    UIKit_Rotate_Event_Slider_004();
    UIKit_Rotate_Event_Time_Picker_005();
    UIKit_Rotate_Event_Picker_006();
    return container_;
}

void UITestRotateInput::UIKit_Rotate_Event_List_001()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UIList Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (adapter_ == nullptr) {
        adapter_ = new TextAdapter();
    }
    adapter_->SetData(adapterData_);
    if (list_ == nullptr) {
        list_ = new UIList(UIList::VERTICAL);
    }
    list_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
    list_->SetPosition(0, label->GetY() + g_blank, g_listW, g_listH - 200); // 200: mean list reduce height
    list_->SetStartIndex(6);                                                // 6 : list start index
    list_->SetAdapter(adapter_);
    list_->SetOnTouchListener(this);
    list_->SetThrowDrag(true);
    list_->SetRotateFactor(10); // 10 : rotate factor
    list_->SetReboundSize(50); // 50 : rebound size
    container_->Add(list_);
    SetLastPos(list_);
}

void UITestRotateInput::UIKit_Rotate_Event_Scroll_View_002()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UIScrollView Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (scroll_ == nullptr) {
        scroll_ = new UIScrollView();
    }
    scroll_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
    scroll_->SetPosition(0, label->GetY() + g_blank, g_scrollW, g_scrollH);
    scroll_->SetXScrollBarVisible(true);
    scroll_->SetYScrollBarVisible(true);
    scroll_->SetRotateFactor(10); // 10 : rotateFactor
    UIButton* btn = new UIButton();
    btn->SetPosition(0, 0, g_buttonW, g_buttonH);
    scroll_->Add(btn);
    scroll_->SetThrowDrag(true);
    scroll_->SetOnTouchListener(this);
    scroll_->SetReboundSize(50); // 50 : rebound size
    SetLastPos(scroll_);
    container_->Add(scroll_);
}

void UITestRotateInput::UIKit_Rotate_Event_Swipe_View_003()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UISwipeView Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (swipe_ == nullptr) {
        swipe_ = new UISwipeView(UISwipeView::HORIZONTAL);
    }
    swipe_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
    swipe_->SetPosition(0, label->GetY() + g_blank, g_swipeW, g_swipeH);
    swipe_->SetBlankSize(100); // 100 is blank size
    UILabelButton* btn1 = new UILabelButton();
    UILabelButton* btn2 = new UILabelButton();
    UILabelButton* btn3 = new UILabelButton();
    UILabelButton* btn4 = new UILabelButton();
    UILabelButton* btn5 = new UILabelButton();
    UILabelButton* btn6 = new UILabelButton();
    UILabelButton* btn7 = new UILabelButton();
    btn1->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn2->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn3->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn4->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn5->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn6->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn7->SetPosition(0, 0, g_smallButtonW, g_smallButtonH);
    btn1->SetText("Button 1");
    btn2->SetText("Button 2");
    btn3->SetText("Button 3");
    btn4->SetText("Button 4");
    btn5->SetText("Button 5");
    btn6->SetText("Button 6");
    btn7->SetText("Button 7");
    swipe_->Add(btn1);
    swipe_->Add(btn2);
    swipe_->Add(btn3);
    swipe_->Add(btn4);
    swipe_->Add(btn5);
    swipe_->Add(btn6);
    swipe_->Add(btn7);
    swipe_->SetOnTouchListener(this);
    swipe_->SetRotateFactor(30); // 30 : rotate factor
    container_->Add(swipe_);
    SetLastPos(swipe_);
}

void UITestRotateInput::UIKit_Rotate_Event_Slider_004()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UISlider Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (slider_ == nullptr) {
        slider_ = new UISlider();
    }
    slider_->SetPosition(50, label->GetY() + g_blank, g_sliderW, g_sliderH); // 50: position x
    slider_->SetValidHeight(200);                                            // 200: valid height
    slider_->SetValue(0);                                                    // 0: progress bar current value
    slider_->SetDirection(UISlider::Direction::DIR_BOTTOM_TO_TOP);
    slider_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Gray().full);
    slider_->SetOnTouchListener(this);
    container_->Add(slider_);
    SetLastPos(slider_);
}
void UITestRotateInput::UIKit_Rotate_Event_Time_Picker_005()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UITimePicker Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (timePicker_ == nullptr) {
        timePicker_ = new UITimePicker();
    }
    timePicker_->EnableSecond(true);
    timePicker_->SetPosition(0, label->GetY() + g_blank, g_listW, g_listH);
    timePicker_->SetItemHeight(50); // 50 height

    UIView* hour = timePicker_->GetChildById("hour");
    if (hour == nullptr) {
        return;
    }
    hour->SetOnTouchListener(this);

    UIView* minute = timePicker_->GetChildById("minute");
    if (minute == nullptr) {
        return;
    }
    minute->SetOnTouchListener(this);

    UIView* second = timePicker_->GetChildById("second");
    if (second == nullptr) {
        return;
    }
    second->SetOnTouchListener(this);

    container_->Add(timePicker_);
    SetLastPos(timePicker_);
}

void UITestRotateInput::UIKit_Rotate_Event_Picker_006()
{
    if (container_ == nullptr) {
        return;
    }
    UILabel* label = GetTitleLabel("UIPicker Test");
    container_->Add(label);
    label->SetPosition(0, lastY_ + g_blank);
    if (picker_ == nullptr) {
        picker_ = new UIPicker();
    }
    picker_->SetPosition(0, label->GetY() + g_blank, g_listW, g_listH);
    picker_->SetItemHeight(50); // 50: height
    picker_->SetValues(g_pickerRange, sizeof(g_pickerRange) / sizeof(g_pickerRange[0]));
    picker_->SetOnTouchListener(this);
    container_->Add(picker_);
    SetLastPos(picker_);
}
bool UITestRotateInput::OnPress(UIView& view, const PressEvent& event)
{
    if (&view == container_) {
        container_->RequestFocus();
        return true;
    } else if (&view == list_) {
        list_->RequestFocus();
        return true;
    } else if (&view == scroll_) {
        scroll_->RequestFocus();
        return true;
    } else if (&view == swipe_) {
        swipe_->RequestFocus();
        return true;
    } else if (&view == slider_) {
        slider_->RequestFocus();
        return true;
    } else if (&view == timePicker_->GetChildById(UITimePicker::HOUR_LIST_NAME)) {
        view.RequestFocus();
        return true;
    } else if (&view == timePicker_->GetChildById(UITimePicker::MIN_LIST_NAME)) {
        view.RequestFocus();
        return true;
    } else if (&view == timePicker_->GetChildById(UITimePicker::SEC_LIST_NAME)) {
        view.RequestFocus();
        return true;
    } else if (&view == picker_) {
        picker_->RequestFocus();
        return true;
    }
    return false;
}
void UITestRotateInput::SetLastPos(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    lastX_ = view->GetX();
    lastY_ = view->GetY() + view->GetHeight();
}
} // namespace OHOS
#endif
