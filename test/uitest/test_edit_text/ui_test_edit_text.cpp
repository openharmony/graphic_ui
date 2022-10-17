/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "ui_test_edit_text.h"

#include "common/input_method_manager.h"
#include "common/screen.h"
#include "components/ui_edit_text.h"
#include "components/ui_label.h"
#include "font/ui_font.h"
#include "securec.h"
#include "test_edit_text/custom_input_method.h"

namespace OHOS {
namespace {
constexpr int16_t EDIT_VIEW_OFFSET = 20;
}

void UITestEditText::SetUp()
{
    CustomInputMethod* inputMethod = new CustomInputMethod();
    InputMethodManager::GetInstance().SetInputMethodListener(inputMethod);

    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->SetThrowDrag(true);
        container_->SetHorizontalScrollState(false);
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
    }

    if (changeHint_ == nullptr) {
        UILabel* title = new UILabel();
        container_->Add(title);
        title->SetText("Value:");
        title->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
        // 0: position x; 40: position y 60: width 48 height
        title->SetPosition(0, 40, 60, 48);

        changeHint_ = new UILabel();
        container_->Add(changeHint_);
        container_->SetViewId("ChanggeHint");
        // 60: position x; 40: position y 288: width 48 height
        changeHint_->SetPosition(60, 40, 288, 48);
        changeHint_->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    }
}

void UITestEditText::TearDown()
{
    DeleteChildren(container_);
    container_ = nullptr;
    changeHint_ = nullptr;
}

const UIView* UITestEditText::GetTestView()
{
    UIKitUIEditTextTestDisplay001();
    return container_;
}

void UITestEditText::UIKitUIEditTextTestDisplay001()
{
    if (container_ == nullptr) {
        return;
    }

    UILabel* label = new UILabel();
    container_->Add(label);
    // 288: width; 48: height
    label->SetPosition(TEXT_DISTANCE_TO_LEFT_SIDE, TEXT_DISTANCE_TO_TOP_SIDE, 288, 48);
    label->SetText("UIEditText 效果:");
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    UIEditText* editText1 = SetupEditText("", "Name:", "editText1");
    editText1->SetPosition(20, 80); // 20:position x; 80: position x;
    editText1->SetPlaceholderColor(Color::Blue());
    editText1->SetCursorColor(Color::Red());
    container_->Add(editText1);

    UIEditText* editText2 = SetupEditText("zhangsan", "Name 2:", "editText2");
    container_->Add(editText2);
    editText2->LayoutBottomToSibling("editText1", EDIT_VIEW_OFFSET);
    editText2->AlignLeftToSibling("editText1");

    UIEditText* editText3 = SetupEditText("", "Password:", "editText3");
    container_->Add(editText3);
    editText3->SetMaxLength(8); // 8: max length
    editText3->SetInputType(InputType::PASSWORD_TYPE);
    editText3->LayoutBottomToSibling("editText2", EDIT_VIEW_OFFSET);
    editText3->AlignLeftToSibling("editText2");

    UIEditText* editText4 = SetupEditText("", "This is a long placeholder", "editText4");
    container_->Add(editText4);
    editText4->LayoutBottomToSibling("editText3", EDIT_VIEW_OFFSET);
    editText4->AlignLeftToSibling("editText3");

    UIEditText* editText5 = SetupEditText("This is a long default value", "This is a long placeholder", "editText5");
    container_->Add(editText5);
    editText5->LayoutBottomToSibling("editText4", EDIT_VIEW_OFFSET);
    editText5->AlignLeftToSibling("editText4");
    editText5->SetTextColor(Color::Red());
}

bool UITestEditText::OnClick(UIView& view, const ClickEvent& event)
{
    return true;
}

UIEditText* UITestEditText::SetupEditText(const char* value, const char* placeholder, const char* viewId)
{
    UIEditText* editText = new UIEditText();
    editText->SetText(value);
    editText->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 26); // 26: font size
    editText->Resize(280, 50);                           // 280: width 50: height
    editText->SetPlaceholder(placeholder);
    editText->SetViewId(viewId);
    editText->SetOnChangeListener(this);
    return editText;
}

void UITestEditText::OnChange(UIView& view, const char* value)
{
    printf("onchange viewId:%s, value:%s\n", view.GetViewId(), value);

    if (changeHint_ != nullptr) {
        changeHint_->SetText(value);
    }
}
} // namespace OHOS
