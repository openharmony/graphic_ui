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

#ifndef UI_TEST_BORDER_MARGIN_PADDING_H
#define UI_TEST_BORDER_MARGIN_PADDING_H

#include "components/text_adapter.h"
#include "components/ui_chart.h"
#include "components/ui_label.h"
#include "components/ui_picker.h"
#include "components/ui_scroll_view.h"
#include "components/ui_toggle_button.h"
#include "layout/grid_layout.h"
#include "layout/list_layout.h"
#include "ui_test.h"

namespace OHOS {
class BorderListener;
class MarginListener;
class PaddingListener;

class UITestBorderMarginPadding : public UITest {
public:
    UITestBorderMarginPadding()
    {
        style_ = StyleDefault::GetDefaultStyle();
        style_.bgOpa_ = OPA_OPAQUE;
        style_.bgColor_ = Color::Gray();
    }
    virtual ~UITestBorderMarginPadding() {}
    void SetUp() override;
    void TearDown() override;
    UIView* GetTestView() override;
    void ReloadTest();

    void UIKit_UITestBorderMarginPadding_Test_001();
    void UIKit_UITestBorderMarginPadding_Test_002();
    void UIKit_UITestBorderMarginPadding_Test_003();
    void UIKit_UITestBorderMarginPadding_Test_004();
    void UIKit_UITestBorderMarginPadding_Test_005();
    void UIKit_UITestBorderMarginPadding_Test_006();
    void UIKit_UITestBorderMarginPadding_Test_007();
    void UIKit_UITestBorderMarginPadding_Test_008();
    void UIKit_UITestBorderMarginPadding_Test_009();
    void UIKit_UITestBorderMarginPadding_Test_010();
    void UIKit_UITestBorderMarginPadding_Test_011();
    void UIKit_UITestBorderMarginPadding_Test_012();
    void UIKit_UITestBorderMarginPadding_Test_013();
    void UIKit_UITestBorderMarginPadding_Test_014();
    void UIKit_UITestBorderMarginPadding_Test_015();
    void UIKit_UITestBorderMarginPadding_Test_016();
    void UIKit_UITestBorderMarginPadding_Test_017();
    void UIKit_UITestBorderMarginPadding_Test_018();
    Style style_;

private:
    const int16_t TITLE_HEIGHT = 29;
    const int16_t BUTTON_GROUP_WIDTH = 250;
    UIScrollView scroll_;
    GridLayout layoutButton_;
    ListLayout* listScroll_ = nullptr;
    UIViewGroup container_;
    UILabel labelMargin_;
    UIToggleButton margin_;
    UILabel labelBorder_;
    UIToggleButton border_;
    UILabel labelPadding_;
    UIToggleButton padding_;
    MarginListener* marginListener_ = nullptr;
    BorderListener* borderListener_ = nullptr;
    PaddingListener* paddingListener_ = nullptr;
    UIChartPolyline* chart_ = nullptr;
    UIChartDataSerial* dataSerial_ = nullptr;
    TextAdapter* adapter_ = nullptr;
    List<const char*>* adapterData_ = nullptr;
    UIPicker* picker_ = nullptr;

    void AddTitle(const char* text);
};

class MarginListener : public UIToggleButton::OnChangeListener {
public:
    explicit MarginListener(UITestBorderMarginPadding* view)
    {
        view_ = view;
    }

    virtual ~MarginListener() {}

    virtual bool OnChange(UICheckBox::UICheckBoxState state)
    {
        if (state == UICheckBox::SELECTED) {
            view_->style_.SetStyle(STYLE_MARGIN_LEFT, MARGIN_SIZE);
            view_->style_.SetStyle(STYLE_MARGIN_TOP, MARGIN_SIZE);
            view_->style_.SetStyle(STYLE_MARGIN_RIGHT, MARGIN_SIZE);
            view_->style_.SetStyle(STYLE_MARGIN_BOTTOM, MARGIN_SIZE);
        } else {
            view_->style_.SetStyle(STYLE_MARGIN_LEFT, 0);
            view_->style_.SetStyle(STYLE_MARGIN_TOP, 0);
            view_->style_.SetStyle(STYLE_MARGIN_RIGHT, 0);
            view_->style_.SetStyle(STYLE_MARGIN_BOTTOM, 0);
        }
        view_->ReloadTest();
    }

private:
    static constexpr int16_t MARGIN_SIZE = 30;
    UITestBorderMarginPadding* view_ = nullptr;
};

class BorderListener : public UIToggleButton::OnChangeListener {
public:
    explicit BorderListener(UITestBorderMarginPadding* view)
    {
        view_ = view;
    }

    virtual ~BorderListener() {}

    virtual bool OnChange(UICheckBox::UICheckBoxState state)
    {
        if (state == UICheckBox::SELECTED) {
            view_->style_.SetStyle(STYLE_BORDER_WIDTH, 20); // 20: border width
            view_->style_.SetStyle(STYLE_BORDER_OPA, OPA_OPAQUE);
            view_->style_.SetStyle(STYLE_BORDER_COLOR, Color::Blue().full);
        } else {
            view_->style_.SetStyle(STYLE_BORDER_WIDTH, 0);
        }
        view_->ReloadTest();
    }

private:
    UITestBorderMarginPadding* view_ = nullptr;
};

class PaddingListener : public UIToggleButton::OnChangeListener {
public:
    explicit PaddingListener(UITestBorderMarginPadding* view)
    {
        view_ = view;
    }

    virtual ~PaddingListener() {}

    virtual bool OnChange(UICheckBox::UICheckBoxState state)
    {
        if (state == UICheckBox::SELECTED) {
            view_->style_.SetStyle(STYLE_PADDING_LEFT, PADDING_SIZE);
            view_->style_.SetStyle(STYLE_PADDING_TOP, PADDING_SIZE);
            view_->style_.SetStyle(STYLE_PADDING_RIGHT, PADDING_SIZE);
            view_->style_.SetStyle(STYLE_PADDING_BOTTOM, PADDING_SIZE);
        } else {
            view_->style_.SetStyle(STYLE_PADDING_LEFT, 0);
            view_->style_.SetStyle(STYLE_PADDING_TOP, 0);
            view_->style_.SetStyle(STYLE_PADDING_RIGHT, 0);
            view_->style_.SetStyle(STYLE_PADDING_BOTTOM, 0);
        }
        view_->ReloadTest();
    }

private:
    static constexpr int16_t PADDING_SIZE = 30;
    UITestBorderMarginPadding* view_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_BORDER_MARGIN_PADDING_H
