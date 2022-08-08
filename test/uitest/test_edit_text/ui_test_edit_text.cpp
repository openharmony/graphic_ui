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
#include "test_edit_text/custom_input_method.h"

namespace OHOS {
void UITestEditText::SetUp()
{
    CustomInputMethod* inputMethod = new CustomInputMethod();
    InputMethodManager::GetInstance().SetInputMethodListener(inputMethod);

    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->SetThrowDrag(true);
        container_->SetHorizontalScrollState(false);
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
        positionX_ = 0;
        positionY_ = 0;
    }
}

void UITestEditText::TearDown()
{
    DeleteChildren(container_);
    container_ = nullptr;
    editText_ = nullptr;
}

const UIView* UITestEditText::GetTestView()
{
    UIKit_UIEditText_Test_Display_001();
    return container_;
}

void UITestEditText::UIKit_UIEditText_Test_Display_001()
{
    if (container_ == nullptr) {
        return;
    }

    UIViewGroup* viewgroup = new UIViewGroup();
    // 320: width; 390: height
    viewgroup->SetPosition(positionX_, positionY_, 320, 390);
    container_->Add(viewgroup);
    UILabel* label = new UILabel();
    viewgroup->Add(label);
    // 288: width; 48: height
    label->SetPosition(TEXT_DISTANCE_TO_LEFT_SIDE, TEXT_DISTANCE_TO_TOP_SIDE, 288, 48);
    label->SetText("UIEditText 效果:");
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    editText_ = new UIEditText();
    editText_->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 26); // 26: font size
    editText_->SetPosition(20, 80, 280, 50); // 20:position x; 80: position x; 280: width; 50: height
    editText_->SetViewId("editText1");
    editText_->SetPlaceholder("Name:");
    editText_->SetPlaceholderColor(Color::Blue());
    editText_->SetCursorColor(Color::Red());
    editText_->SetOnChangeListener(this);
    viewgroup->Add(editText_);

    UIEditText* editText2 = new UIEditText();
    viewgroup->Add(editText2);
    editText2->SetText("zhangsan");
    editText2->SetPlaceholder("Name 2:");
    editText2->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 26); // 26: font size
    editText2->Resize(280, 50);                           // 280: width 50: height
    editText2->SetViewId("editText2");
    editText2->LayoutBottomToSibling("editText1", 20); // 20: offset
    editText2->AlignLeftToSibling("editText1");

    UIEditText* editText3 = new UIEditText();
    viewgroup->Add(editText3);
    editText3->SetText("");
    editText3->SetPlaceholder("Password:");
    editText3->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 26); // 26: font size
    editText3->Resize(280, 50);                           // 280: width 50: height
    editText3->SetMaxLength(8);                           // 8: max length
    editText3->SetViewId("editText3");
    editText3->SetInputType(InputType::PASSWORD_TYPE);
    editText3->LayoutBottomToSibling("editText2", 20); // 20: offset
    editText3->AlignLeftToSibling("editText2");

    UIEditText* editText4 = new UIEditText();
    viewgroup->Add(editText4);
    editText4->SetText("");
    editText4->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 26); // 26: font size
    editText4->Resize(280, 50);                           // 280: width 50: height
    editText4->SetPlaceholder("This is a long placeholder");
    editText4->SetViewId("editText4");
    editText4->LayoutBottomToSibling("editText3", 20); // 20: offset
    editText4->AlignLeftToSibling("editText3");
}

void UITestEditText::UIKit_UIEditText_Test_Display_002() {}

void UITestEditText::UIKit_UIEditText_Test_Display_003() {}

bool UITestEditText::OnClick(UIView& view, const ClickEvent& event)
{
    return true;
}

void UITestEditText::OnChange(UIView& view, const char* value)
{
    printf("onchange value:%s\n", value);
}
} // namespace OHOS
