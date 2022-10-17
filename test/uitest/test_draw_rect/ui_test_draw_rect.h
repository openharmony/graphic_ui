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

#ifndef UI_TEST_DRAW_RECT_H
#define UI_TEST_DRAW_RECT_H

#include "components/ui_button.h"
#include "components/ui_label.h"
#include "components/ui_scroll_view.h"
#include "ui_test.h"

namespace OHOS {
class UITestDrawRect : public UITest {
public:
    UITestDrawRect() {}
    ~UITestDrawRect() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;

    void UIKitDrawRectTestRectNoBorder001();
    void UIKitDrawRectTestRectNoBorder002();
    void UIKitDrawRectTestRectNoBorder003();
    void UIKitDrawRectTestRectNoBorder004();
    void UIKitDrawRectTestRectNoBorder005();
    void UIKitDrawRectTestRectNoBorder006();
    void UIKitDrawRectTestRectNoBorder007();
    void UIKitDrawRectTestRectNoBorder008();
    void UIKitDrawRectTestRectNoBorder009();
    void UIKitDrawRectTestRectNoBorder0010();
    void UIKitDrawRectTestRectBorderNoRadius001();
    void UIKitDrawRectTestRectBorderNoRadius002();
    void UIKitDrawRectTestRectBorderRadius001();
    void UIKitDrawRectTestRectBorderRadius002();
    void UIKitDrawRectTestRectBorderRadius003();
    void UIKitDrawRectTestRectBorderRadius004();
    void UIKitDrawRectTestRectBorderRadius005();
    void UIKitDrawRectTestRectBorderRadius006();
    void UIKitDrawRectTestRectBorderRadius007();
    void UIKitDrawRectTestRectBorderRadius008();
    void UIKitDrawRectTestRectBorderRadius009();
    void UIKitDrawRectTestRectBorderRadius010();
    void UIKitDrawRectTestRectBorderRadius011();

    /**
     * @brief Test draw rect function
     */
    void UIKitDrawRectTestRect001();

    /**
     * @brief Test draw rect background color
     */
    void UIKitDrawRectTestRectColor001();

    /**
     * @brief Test draw rect radius is 0
     */
    void UIKitDrawRectTestRectRadius001();

    /**
     * @brief Test draw rect radius
     */
    void UIKitDrawRectTestRectRadius002();

    /**
     * @brief Test draw rect radius equal width
     */
    void UIKitDrawRectTestRectRadius003();

    /**
     * @brief Test draw rect radius equal width and height
     */
    void UIKitDrawRectTestRectRadius004();

    /**
     * @brief Test draw rect opacity is not transparent
     */
    void UIKitDrawRectTestRectOpacity001();

    /**
     * @brief Test draw rect opacity is transparent
     */
    void UIKitDrawRectTestRectOpacity002();

    /**
     * @brief Test draw rect opacity with different value
     */
    void UIKitDrawRectTestRectOpacity003();

    /**
     * @brief Test draw rect border color with different value
     */
    void UIKitDrawRectTestRectBorderColor001();

    /**
     * @brief Test draw rect border width is 0
     */
    void UIKitDrawRectTestRectBorderWidth001();

    /**
     * @brief Test draw rect border with different value
     */
    void UIKitDrawRectTestRectBorderWidth002();

    /**
     * @brief Test draw rect border opacity is not transparent
     */
    void UIKitDrawRectTestRectBorderOpacity001();

    /**
     * @brief Test draw rect border opacity is transparent
     */
    void UIKitDrawRectTestRectBorderOpacity002();

    /**
     * @brief Test draw rect border opacity with different value
     */
    void UIKitDrawRectTestRectBorderOpacity003();

    /**
     * @brief Test draw rect padding is 0
     */
    void UIKitDrawRectTestRectPadding001();

    /**
     * @brief Test draw rect padding with different value
     */
    void UIKitDrawRectTestRectPadding002();

    /**
     * @brief Test draw rect margin is 0
     */
    void UIKitDrawRectTestRectMargin001();

    /**
     * @brief Test draw rect margin is not 0
     */
    void UIKitDrawRectTestRectMargin002();

    /**
     * @brief Test draw rect padding and margin is 0
     */
    void UIKitDrawRectTestRectPaddingMargin001();

    /**
     * @brief Test draw rect padding and margin with different value
     */
    void UIKitDrawRectTestRectPaddingMargin002();

    /**
     * @brief Test rect width is 0
     */
    void UIKitDrawRectTestRectWidthAndHeight001();

    /**
     * @brief Test rect height is 0
     */
    void UIKitDrawRectTestRectWidthAndHeight002();

    /**
     * @brief Test rect width and height is 0
     */
    void UIKitDrawRectTestRectWidthAndHeight003();

private:
    UIViewGroup* CreateTestCaseGroup() const;
    UILabel* CreateTitleLabel() const;
    UIView* CreateUIView() const;
    UIScrollView* container_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_DRAW_RECT_H
