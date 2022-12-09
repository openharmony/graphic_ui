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

#include "ui_test_view_bitmap.h"

#include "securec.h"

#include "common/screen.h"
#include "components/ui_label_button.h"
#include "test_resource_config.h"

namespace OHOS {
class ViewBitmapListener : public UIView::OnClickListener {
public:
    ViewBitmapListener(UIViewGroup* container, UIImageView* img) : container_(container), img_(img)
    {
        (void)memset_s(&info_, sizeof(ImageInfo), 0, sizeof(ImageInfo));
        if ((img != nullptr) && (container != nullptr)) {
            container->Add(img);
            img->SetVisible(false);
        }
    }
    virtual ~ViewBitmapListener()
    {
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (img_ == nullptr) {
            return false;
        }
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
        view.GetBitmap(info_, ARGB8888);
        img_->SetVisible(true);
        img_->SetSrc(&info_);
        img_->Invalidate();
        return false;
    }

private:
    UIViewGroup* container_;
    UIImageView* img_;
    ImageInfo info_;
};


class ViewBitmapListener2 : public UIView::OnClickListener {
public:
    ViewBitmapListener2(UIViewGroup* container, UIImageView* img) : container_(container), img_(img)
    {
        (void)memset_s(&info_, sizeof(ImageInfo), 0, sizeof(ImageInfo));
        if ((img != nullptr) && (container != nullptr)) {
            container->Add(img);
            img->SetVisible(false);
        }
    }
    virtual ~ViewBitmapListener2()
    {
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (img_ == nullptr) {
            return false;
        }
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
        view.GetBitmap(info_, XRGB8888);
        img_->SetVisible(true);
        img_->SetSrc(&info_);
        img_->Invalidate();
        return false;
    }

private:
    UIViewGroup* container_;
    UIImageView* img_;
    ImageInfo info_;
};

class ViewBitmapListener3 : public UIView::OnClickListener {
public:
    ViewBitmapListener3(UIViewGroup* container, UIImageView* img) : container_(container), img_(img)
    {
        (void)memset_s(&info_, sizeof(ImageInfo), 0, sizeof(ImageInfo));
        if ((img != nullptr) && (container != nullptr)) {
            container->Add(img);
            img->SetVisible(false);
        }
    }
    virtual ~ViewBitmapListener3()
    {
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (img_ == nullptr) {
            return false;
        }
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
        view.GetBitmap(info_, RGB888);
        img_->SetVisible(true);
        img_->SetSrc(&info_);
        img_->Invalidate();
        return false;
    }

private:
    UIViewGroup* container_;
    UIImageView* img_;
    ImageInfo info_;
};

class ViewBitmapListener4 : public UIView::OnClickListener {
public:
    ViewBitmapListener4(UIViewGroup* container, UIImageView* img) : container_(container), img_(img)
    {
        (void)memset_s(&info_, sizeof(ImageInfo), 0, sizeof(ImageInfo));
        if ((img != nullptr) && (container != nullptr)) {
            container->Add(img);
            img->SetVisible(false);
        }
    }
    virtual ~ViewBitmapListener4()
    {
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (img_ == nullptr) {
            return false;
        }
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
        view.GetBitmap(info_, RGB565);
        img_->SetVisible(true);
        img_->SetSrc(&info_);
        img_->Invalidate();
        return false;
    }

private:
    UIViewGroup* container_;
    UIImageView* img_;
    ImageInfo info_;
};

class ScreenBitmapListener : public UIView::OnClickListener {
public:
    ScreenBitmapListener(UIViewGroup* container, UIImageView* img) : container_(container), img_(img)
    {
        memset_s(&info_, sizeof(ImageInfo), 0, sizeof(ImageInfo));
        if ((img != nullptr) && (container != nullptr)) {
            container->Add(img);
            img->SetVisible(false);
        }
    }
    virtual ~ScreenBitmapListener()
    {
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
    }
    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        if (img_ == nullptr) {
            return false;
        }
        if (info_.data != nullptr) {
            ImageCacheFree(info_);
        }
        if (!Screen::GetInstance().GetCurrentScreenBitmap(info_)) {
            return false;
        }
        img_->SetVisible(true);
        img_->SetSrc(&info_);
        img_->Invalidate();
        return false;
    }

private:
    UIViewGroup* container_;
    UIImageView* img_;
    ImageInfo info_;
};

void UITestViewBitmap::SetUp()
{
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
        container_->SetHorizontalScrollState(false);
        container_->SetStyle(STYLE_BACKGROUND_COLOR, Color::White().full);
    }
    if (viewBitmap_ == nullptr) {
        viewBitmap_ = new UIImageView();
        // 100 : x pos of image; 100: y pos of image; 960 width of image; 480 : height of image.
        viewBitmap_->SetPosition(100, 100, 960, 480);
    }
    if (viewBitmap2_ == nullptr) {
        viewBitmap2_ = new UIImageView();
        // 300 : x pos of image; 100: y pos of image; 960 width of image; 480 : height of image.
        viewBitmap2_->SetPosition(300, 100, 960, 480);
    }
    if (viewBitmap3_ == nullptr) {
        viewBitmap3_ = new UIImageView();
        // 500 : x pos of image; 100: y pos of image; 960 width of image; 480 : height of image.
        viewBitmap3_->SetPosition(500, 100, 960, 480);
    }
    if (viewBitmap4_ == nullptr) {
        viewBitmap4_ = new UIImageView();
        // 700 : x pos of image; 100: y pos of image; 960 width of image; 480 : height of image.
        viewBitmap4_->SetPosition(700, 100, 960, 480);
    }
    if (screenBitmap_ == nullptr) {
        screenBitmap_ = new UIImageView();
        // 0 : x pos of image; 210: y pos of image; 960 width of image; 480 : height of image.
        screenBitmap_->SetPosition(0, 210, 960, 480);
    }
    if (viewBitmapListener_ == nullptr) {
        viewBitmapListener_ = new ViewBitmapListener(container_, viewBitmap_);
    }
    if (viewBitmapListener2_ == nullptr) {
        viewBitmapListener2_ = new ViewBitmapListener2(container_, viewBitmap2_);
    }
    if (viewBitmapListener3_ == nullptr) {
        viewBitmapListener3_ = new ViewBitmapListener3(container_, viewBitmap3_);
    }
    if (viewBitmapListener4_ == nullptr) {
        viewBitmapListener4_ = new ViewBitmapListener4(container_, viewBitmap4_);
    }
    if (screenBitmapListener_ == nullptr) {
        screenBitmapListener_ = new ScreenBitmapListener(container_, screenBitmap_);
    }
}

void UITestViewBitmap::TearDown()
{
    if (viewBitmapListener_ != nullptr) {
        delete viewBitmapListener_;
        viewBitmapListener_ = nullptr;
    }
    if (viewBitmapListener2_ != nullptr) {
        delete viewBitmapListener2_;
        viewBitmapListener2_ = nullptr;
    }
    if (viewBitmapListener3_ != nullptr) {
        delete viewBitmapListener3_;
        viewBitmapListener3_ = nullptr;
    }
    if (viewBitmapListener4_ != nullptr) {
        delete viewBitmapListener4_;
        viewBitmapListener4_ = nullptr;
    }
    if (screenBitmapListener_ != nullptr) {
        delete screenBitmapListener_;
        screenBitmapListener_ = nullptr;
    }
    DeleteChildren(container_);
    container_ = nullptr;
    viewBitmap_ = nullptr;
    viewBitmap2_ = nullptr;
    viewBitmap3_ = nullptr;
    viewBitmap4_ = nullptr;
    screenBitmap_ = nullptr;
}

const UIView* UITestViewBitmap::GetTestView()
{
    UIKitBitmapTestGetViewBitmap001();
    UIKitBitmapTestGetViewBitmap002();
    UIKitBitmapTestGetViewBitmap003();
    UIKitBitmapTestGetViewBitmap004();
#if !(defined ENABLE_WINDOW && ENABLE_WINDOW)
    UIKitBitmapTestGetScreenBitmap001();
#endif
    return container_;
}

void UITestViewBitmap::UIKitBitmapTestGetViewBitmap001()
{
    UILabelButton* btn = new UILabelButton();
    container_->Add(btn);
    // 100 : x pos of button; 50: y pos of  button.
    btn->SetPosition(100, 50, BUTTON_WIDHT3, BUTTON_HEIGHT3);
    btn->SetText("组件ARGB截屏");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(viewBitmapListener_);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
}

void UITestViewBitmap::UIKitBitmapTestGetViewBitmap002()
{
    UILabelButton* btn = new UILabelButton();
    container_->Add(btn);
    // 300 : x pos of button; 50: y pos of  button.
    btn->SetPosition(300, 50, BUTTON_WIDHT3, BUTTON_HEIGHT3);
    btn->SetText("组件XRGB截屏");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(viewBitmapListener2_);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
}

void UITestViewBitmap::UIKitBitmapTestGetViewBitmap003()
{
    UILabelButton* btn = new UILabelButton();
    container_->Add(btn);
    // 500 : x pos of button; 50: y pos of  button.
    btn->SetPosition(500, 50, BUTTON_WIDHT3, BUTTON_HEIGHT3);
    btn->SetText("组件RGB888截屏");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(viewBitmapListener3_);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
}

void UITestViewBitmap::UIKitBitmapTestGetViewBitmap004()
{
    UILabelButton* btn = new UILabelButton();
    container_->Add(btn);
    // 700 : x pos of button; 50: y pos of  button.
    btn->SetPosition(700, 50, BUTTON_WIDHT3, BUTTON_HEIGHT3);
    btn->SetText("组件RGB565截屏");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(viewBitmapListener4_);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
}

#if !(defined ENABLE_WINDOW && ENABLE_WINDOW)
void UITestViewBitmap::UIKitBitmapTestGetScreenBitmap001()
{
    UILabelButton* btn = new UILabelButton();
    container_->Add(btn);
    // 100 : x pos of button; 150: y pos of  button.
    btn->SetPosition(100, 150, BUTTON_WIDHT3, BUTTON_HEIGHT3);
    btn->SetText("测试全屏截屏");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, BUTTON_LABEL_SIZE);
    btn->SetOnClickListener(screenBitmapListener_);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BORDER_RADIUS, BUTTON_STYLE_BORDER_RADIUS_VALUE, UIButton::INACTIVE);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    btn->SetStyleForState(STYLE_BACKGROUND_COLOR, BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
    btn->SetViewId(UI_TEST_FULL_SCREEN_CAPTURE);
}
#endif
} // namespace OHOS
