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

#ifndef UI_TEST_VIEW_ZINDEX_H
#define UI_TEST_VIEW_ZINDEX_H

#include "components/ui_scroll_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "ui_test.h"

namespace OHOS {
class UITestViewZIndex : public UITest, public UIView::OnClickListener, public AnimatorCallback {
public:
    UITestViewZIndex() {}
    ~UITestViewZIndex();
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    void UIKitViewZIndex001();

    bool OnClick(UIView& view, const ClickEvent& event) override;
    void Callback(UIView* view) override;

private:
    UILabel* CreateTitleLabel() const;
    UILabel* CreateZIndexLabel(const char* text, int16_t zIndex, ColorType color);
    UILabelButton* CreateZIndexBtn(const char* text, const char* viewId);
    void SetupZIndexView();
    void SetupZIndexBtn();
    void SetupChildModifyBtn();
    void SetupChangeView();
    void ClickZIndexBtn(UIView& view);
    void ClickModifyBtn(UIView& view);
    void UpdateClickHint(UIView& view);
    UIScrollView* container_ = nullptr;
    Animator* animator_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_VIEW_ZINDEX_H
