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

#ifndef UI_TEST_VIEW_SCALE_ROTATE_H
#define UI_TEST_VIEW_SCALE_ROTATE_H

#include <cstdio>
#include "components/ui_arc_label.h"
#include "components/ui_box_progress.h"
#include "components/ui_button.h"
#include "components/ui_canvas.h"
#include "components/ui_circle_progress.h"
#include "components/ui_digital_clock.h"
#include "components/ui_image_view.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "components/ui_slider.h"
#include "components/ui_swipe_view.h"
#include "gfx_utils/sys_info.h"
#include "layout/list_layout.h"
#include "ui_test.h"

namespace OHOS {
class UITestViewScaleRotate : public UITest, public AnimatorCallback {
public:
    UITestViewScaleRotate() : animator_(this, nullptr, 1000, true) // 1000: the animator duration time is 1000ms
    {
    }
    virtual ~UITestViewScaleRotate() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;
    void Callback(UIView* view) override;

    void UIKitViewScaleRotateTestLabel001();
    void UIKitViewScaleRotateTestLabelButton002();
    void UIKitViewScaleRotateTestCanvas003();
    void UIKitViewScaleRotateTestUIBoxProgress004();
    void UIKitViewScaleRotateTestUICircleProgress005();
    void UIKitViewScaleRotateTestUIDigitalClock006();
    void UIKitViewScaleRotateTestGroup007();

private:
    const int16_t GROUP_WIDHT = 454;
    const int16_t GROUP_HEIGHT = 300;
    const Vector2<float> VIEW_CENTER = {75, 75};
    const Vector2<float> GROUP_CENTER = {200, 200};

    void SetUpLabel(const char* title) const;

    UIScrollView* container_ = nullptr;
    ListLayout* list_ = nullptr;
    int16_t angleValue_ = 0;
    Vector2<float> scaleValue_ = {1.0f, 1.0f};
    float scaleStep_ = 0.01f;

    Animator animator_;
    UILabel* label_ = nullptr;
    UICanvas* canvas_ = nullptr;
    UILabelButton* button1_ = nullptr;
    UIBoxProgress* boxProgress_ = nullptr;
    UICircleProgress* circleProgress_ = nullptr;
    UIDigitalClock* dClock_ = nullptr;
    UIViewGroup* group1_ = nullptr;
};
} // namespace OHOS
#endif // UI_TEST_BOX_PROGRESS_H
