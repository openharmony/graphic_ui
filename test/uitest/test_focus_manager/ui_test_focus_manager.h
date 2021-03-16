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

#ifndef UI_TEST_FOCUS_MANAGER_H
#define UI_TEST_FOCUS_MANAGER_H

#include "graphic_config.h"
#if ENABLE_FOCUS_MANAGER
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "dock/focus_manager.h"
#include "ui_test.h"

namespace OHOS {
class UITestFocusManager : public UITest {
public:
    UITestFocusManager() {}
    ~UITestFocusManager() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView();

    void UIKit_Focus_Manager_Test_001();

private:
    UIView* CreateTestUILabel(UIViewGroup* parent, int16_t x, int16_t y,
        const char* text, bool focusable);
    UIViewGroup* CreateTestUIViewGroup(UIViewGroup* parent, bool focusable, bool interceptFocus);
    UILabelButton* SetUpButton(const char* title, int16_t x, int16_t y, UIViewGroup* viewGroup,
        UIView::OnClickListener* listener);
    UIScrollView* container_ = nullptr;
};
} // namespace OHOS
#endif
#endif // UI_TEST_FOCUS_MANAGER_H