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

#ifndef UI_TEST_BOX_PROGRESS_H
#define UI_TEST_BOX_PROGRESS_H

#include "components/ui_box_progress.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "ui_test.h"

namespace OHOS {
class UITestBoxProgress : public UITest, public UIView::OnClickListener {
public:
    UITestBoxProgress() {}
    ~UITestBoxProgress() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    void SetUpButton(UILabelButton* btn, const char* title, int16_t x, int16_t y);
    void SetUpLabel(const char* title, int16_t x, int16_t y) const;

    bool OnClick(UIView& view, const ClickEvent& event) override;

    void UIKitBoxProgressTestUIBoxProgress001();
    void UIKitBoxProgressTestSetRange002();
    void UIKitBoxProgressTestSetValue003();
    void UIKitBoxProgressTestSetImage004();
    void UIKitBoxProgressTestSetStyle005();
    void UIKitBoxProgressTestGetStyle006();
    void UIKitBoxProgressTestSetCapType007();
    void UIKitBoxProgressTestSetDirection008();
    void UIKitBoxProgressTestEnableBackground009();
    void UIKitBoxProgressTestSetStep010();
    void UIKitBoxProgressTestSetValidSize011();
    void UIKitBoxProgressTestSetBorderAndPadding012();

private:
    UIScrollView* container_ = nullptr;
    UIScrollView* scroll_ = nullptr;
    UIBoxProgress* boxProgress_ = nullptr;
    UIViewGroup* uiViewGroupFrame_ = nullptr;

    UILabelButton* resetBtn_ = nullptr;
    UILabelButton* incWidthBtn_ = nullptr;
    UILabelButton* incHeightBtn_ = nullptr;
    UILabelButton* decWidthBtn_ = nullptr;
    UILabelButton* decHeightBtn_ = nullptr;
    UILabelButton* incProgressBtn_ = nullptr;
    UILabelButton* decProgressBtn_ = nullptr;
    UILabelButton* incMinProgressBtn_ = nullptr;
    UILabelButton* decMinProgressBtn_ = nullptr;
    UILabelButton* incMaxProgressBtn_ = nullptr;
    UILabelButton* decMaxProgressBtn_ = nullptr;
    UILabelButton* stepBtn_ = nullptr;
    UILabelButton* dirL2RBtn_ = nullptr;
    UILabelButton* dirR2LBtn_ = nullptr;
    UILabelButton* dirT2BBtn_ = nullptr;
    UILabelButton* dirB2TBtn_ = nullptr;
    UILabelButton* imageBtn_ = nullptr;
    UILabelButton* noImageBtn_ = nullptr;
    UILabelButton* setStyleBtn_ = nullptr;
    UILabelButton* getStyleBtn_ = nullptr;
    UILabelButton* roundCapBtn_ = nullptr;
    UILabelButton* noneCapBtn_ = nullptr;
    UILabelButton* enableBgBtn_ = nullptr;
    UILabelButton* disableBgBtn_ = nullptr;
    UILabelButton* borderIncBtn_ = nullptr;
    UILabelButton* borderDecBtn_ = nullptr;
    UILabelButton* paddingLeftIncBtn_ = nullptr;
    UILabelButton* paddingRightIncBtn_ = nullptr;
    UILabelButton* paddingTopIncBtn_ = nullptr;
    UILabelButton* paddingBottomIncBtn_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_BOX_PROGRESS_H
