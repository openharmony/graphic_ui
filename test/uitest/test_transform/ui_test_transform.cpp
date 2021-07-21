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

#include "ui_test_transform.h"
#include "common/screen.h"
#include "test_resource_config.h"

namespace OHOS {
void UITestTransform::SetUp()
{
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
        UIViewGroup* uiViewGroup = new UIViewGroup();
        uiViewGroup->SetPosition(0, 0, 320, 390); // 320: width; 390: height
        container_->Add(uiViewGroup);
        UILabel* label = new UILabel();
        uiViewGroup->Add(label);
        // 288: width; 48: height
        label->SetPosition(TEXT_DISTANCE_TO_LEFT_SIDE, TEXT_DISTANCE_TO_TOP_SIDE, 288, 48);
        label->SetText("UITransform效果");
        label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
        uiViewGroupFrame_ = new UIViewGroup();
        uiViewGroup->Add(uiViewGroupFrame_);
        // 288: width; 336: height
        uiViewGroupFrame_->SetPosition(VIEW_DISTANCE_TO_LEFT_SIDE2, VIEW_DISTANCE_TO_TOP_SIDE, 288, 336);
        uiViewGroupFrame_->SetStyle(STYLE_BORDER_COLOR, Color::White().full);
        uiViewGroupFrame_->SetStyle(STYLE_BORDER_OPA, HALF_OPA_OPAQUE);
        uiViewGroupFrame_->SetStyle(STYLE_BORDER_WIDTH, VIEW_STYLE_BORDER_WIDTH);
        uiViewGroupFrame_->SetStyle(STYLE_BORDER_RADIUS, VIEW_STYLE_BORDER_RADIUS);
        uiViewGroupFrame_->SetStyle(STYLE_BACKGROUND_OPA, 0);

        imageView_ = new UIImageView();
        imageView_->SetPosition(150, 50, 200, 200); // 150:poistion x 50:position y 200:width 200:height
        imageView_->SetSrc(BLUE_IMAGE_PATH);
        uiViewGroupFrame_->Add(imageView_);
        imageView_->LayoutCenterOfParent();
    }

    if (layout_ == nullptr) {
        layout_ = new GridLayout();
        // 34: increase x-coordinate; 48: y-coordinate; 100: width; 150: height
        layout_->SetPosition(uiViewGroupFrame_->GetWidth() + 34, 48, 100, 150);
        container_->Add(layout_);
        layout_->SetLayoutDirection(LAYOUT_VER);
        layout_->SetRows(3); // 3:two rows
        layout_->SetCols(1); // 1:three cols
    }
    AddLable(layout_->GetOrigRect().GetRight() + 34, 50, "Auto"); // 34 : increase x-coordinate; 50: position y
    AddLable(layout_->GetOrigRect().GetRight() + 34, 100, "Fill"); // 34 : increase x-coordinate; 100: position y
    AddLable(layout_->GetOrigRect().GetRight() + 34, 150, "Contain"); // 34 : increase x-coordinate; 150: position y
    AddLable(layout_->GetOrigRect().GetRight() + 34, 200, "Tiling"); // 34 : increase x-coordinate; 200: position y
    AddRadioButton(GetRect(560, 40, 50, 50), // 560:position x 40:position y 50:width and height
        "RB", new StateChangeListener(ImageScaleMode::AUTO, this))->SetState(
        UICheckBox::UICheckBoxState::SELECTED);
    AddRadioButton(GetRect(560, 90, 50, 50), // 560:position x 90:position y 50:width and height
        "RB", new StateChangeListener(ImageScaleMode::FILL, this));
    AddRadioButton(GetRect(560, 140, 50, 50), // 560:position x 90:position y 50:width and height
        "RB", new StateChangeListener(ImageScaleMode::CONTAIN, this));
    AddRadioButton(GetRect(560, 190, 50, 50), // 560:position x 90:position y 50:width and height
        "RB", new StateChangeListener(ImageScaleMode::TILING, this));
}

void UITestTransform::TearDown()
{
    DeleteChildren(container_);
    container_ = nullptr;
    layout_ = nullptr;
    uiViewGroupFrame_ = nullptr;
    imageView_ = nullptr;
}

const UIView* UITestTransform::GetTestView()
{
    UIKit_Transform_Test_Rotate_001();
    UIKit_Transform_Test_Scale_002();
    UIKit_Transform_Test_Translate_003();

    layout_->LayoutChildren();
    return container_;
}

void UITestTransform::SetUpButton(UILabelButton* btn, const char* title)
{
    if (btn == nullptr) {
        return;
    }
    layout_->Add(btn);
    btn->Resize(BUTTON_WIDHT1, BUTTON_HEIGHT1);
    btn->SetText(title);
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(this);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
}

void UITestTransform::UIKit_Transform_Test_Rotate_001()
{
    rotateBtn_ = new UILabelButton();
    SetUpButton(rotateBtn_, "旋转");
}

void UITestTransform::UIKit_Transform_Test_Scale_002()
{
    scaleBtn_ = new UILabelButton();
    SetUpButton(scaleBtn_, "缩放");
}

void UITestTransform::UIKit_Transform_Test_Translate_003()
{
    translateBtn_ = new UILabelButton();
    SetUpButton(translateBtn_, "平移");
}

bool UITestTransform::OnClick(UIView& view, const ClickEvent& event)
{
    Rect viewRect = imageView_->GetOrigRect();
    TransformMap transMap(viewRect);
    Vector2<float> pivot(58, 58); // 58:x value 58:y value
    if (&view == rotateBtn_) {
        angle_ = (angle_ + 90) % 360; // 90: increase angle; 360: wrapping value
    } else if (&view == scaleBtn_) {
        scale_ += 0.1f; // 0.1: increase scale
    } else if (&view == translateBtn_) {
        trans_ += 10; // 10: increase translate
    }
    SetTransMap(angle_, scale_, trans_, pivot);
    return true;
}

void UITestTransform::SetScaleMode(ImageScaleMode mode)
{
    // must the position fisrt
    switch (mode) {
        case ImageScaleMode::AUTO:
            imageView_->SetAutoEnable(true);
            imageView_->SetResizeMode(UIImageView::ImageResizeMode::NONE);
            break;
        case ImageScaleMode::CONTAIN:
            imageView_->SetAutoEnable(false);
            imageView_->SetResizeMode(UIImageView::ImageResizeMode::CONTAIN);
            break;
        case ImageScaleMode::FILL:
            imageView_->SetAutoEnable(false);
            imageView_->SetResizeMode(UIImageView::ImageResizeMode::FILL);
            break;
        case ImageScaleMode::TILING:
            imageView_->SetAutoEnable(false);
            imageView_->SetResizeMode(UIImageView::ImageResizeMode::NONE);
            break;
        default:
            break;
    }
    if (mode != ImageScaleMode::AUTO) {
        imageView_->SetWidth(200); // 200: width
        imageView_->SetHeight(200); // 200: height
    }
    // reset the transmap
    SetTransMap(0, 1.0f, 0, {0.0f,  0.0f});
    uiViewGroupFrame_->Invalidate();
}

void UITestTransform::SetTransMap(int16_t angle, float scale, int16_t trans, Vector2<float> pivot)
{
    angle_ = angle;
    scale_ = scale;
    trans_ = trans;
    Rect viewRect = imageView_->GetOrigRect();
    TransformMap transMap(viewRect);
    transMap.Rotate(angle_, pivot);
    transMap.Scale(Vector2<float>(scale_, scale_), pivot);
    transMap.Translate(Vector2<int16_t>(trans, 0));
    imageView_->SetTransformMap(transMap);
}

UILabel* UITestTransform::AddLable(int16_t x, int16_t y, const char* data)
{
    UILabel* label = new UILabel();
    container_->Add(label);
    label->SetPosition(x, y, Screen::GetInstance().GetWidth(),
        TITLE_LABEL_DEFAULT_HEIGHT);
    label->SetText(data);
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    return label;
}

UIRadioButton* UITestTransform::AddRadioButton(Rect rect, const char* name, UICheckBox::OnChangeListener* listener)
{
    if (listener == nullptr || name == nullptr) {
        return nullptr;
    }
    auto radioButton = new UITestRadioButton("dddd");
    container_->Add(radioButton);
    radioButton->SetOnChangeListener(listener);
    radioButton->SetPosition(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    if (radioButton->GetState() == UICheckBox::SELECTED) {
        listener->OnChange(UICheckBox::SELECTED);
    }
    return radioButton;
}

StateChangeListener::StateChangeListener(ImageScaleMode mode, UITestTransform* testInstance)
    : mode_(mode),
      testInstance_(testInstance)
{

}

bool StateChangeListener::OnChange(UICheckBox::UICheckBoxState state)
{
    if (state == UICheckBox::UICheckBoxState::SELECTED) {
        testInstance_->SetScaleMode(mode_);
    }
}

UITestRadioButton::UITestRadioButton(const char*  name)
    : UIRadioButton(name)
{

}

UITestRadioButton::~UITestRadioButton()
{
    if (listener_ != nullptr) {
        delete listener_;
        listener_ = nullptr;
    }
}

void UITestRadioButton::SetOnChangeListener(UICheckBox::OnChangeListener* listener)
{
    UIRadioButton::SetOnChangeListener(listener);
    if (listener_ != nullptr) {
        delete listener_;
    }
    listener_ = listener;
}
} // namespace OHOS