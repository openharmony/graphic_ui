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

#ifndef UI_TEST_DRAW_LINE_H
#define UI_TEST_DRAW_LINE_H

#include "components/ui_canvas.h"
#include "components/ui_label.h"
#include "components/ui_scroll_view.h"
#include "components/ui_view_group.h"
#include "ui_test.h"

namespace OHOS {
class UITestDrawLine : public UITest {
public:
    UITestDrawLine() {}
    ~UITestDrawLine() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    /**
     * @brief Test draw line Function
     */
    void UIKitDrawLineTestLine001();
    void UIKitDrawLineTestLine002();
    void UIKitDrawLineTestLine003();
    void UIKitDrawLineTestLine004();
    void UIKitDrawLineTestLine005();
    void UIKitDrawLineTestLine006();
    void UIKitDrawLineTestLine007();
    void UIKitDrawLineTestLine008();
    void UIKitDrawLineTestLine009();
    void UIKitDrawLineTestLine010();
    void UIKitDrawLineTestLine011();
    void UIKitDrawLineTestLine012();

private:
    UIViewGroup* CreateTestCaseGroup() const;
    UILabel* CreateTitleLabel() const;
    UICanvas* CreateCanvas() const;
    UIScrollView* container_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_DRAW_LINE_H
