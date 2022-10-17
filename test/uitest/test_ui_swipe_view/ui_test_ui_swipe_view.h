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

#ifndef UI_TEST_UI_SWIPE_VIEW_H
#define UI_TEST_UI_SWIPE_VIEW_H

#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "components/ui_swipe_view.h"
#include "ui_test.h"

namespace OHOS {
constexpr char* UI_TEST_HOR_001_BUTTON1 = "hor_001_button1";
constexpr char* UI_TEST_HOR_001_BUTTON2 = "hor_001_button2";

constexpr char* UI_TEST_HOR_002_BUTTON1 = "hor_002_button1";
constexpr char* UI_TEST_HOR_002_BUTTON2 = "hor_002_button2";
constexpr char* UI_TEST_HOR_002_BUTTON3 = "hor_002_button3";

constexpr char* UI_TEST_HOR_003_BUTTON1 = "hor_003_button1";
constexpr char* UI_TEST_HOR_003_BUTTON2 = "hor_003_button2";
constexpr char* UI_TEST_HOR_003_BUTTON3 = "hor_003_button3";

constexpr char* UI_TEST_VER_001_BUTTON1 = "ver_001_button1";
constexpr char* UI_TEST_VER_001_BUTTON2 = "ver_001_button2";

constexpr char* UI_TEST_VER_002_BUTTON1 = "ver_002_button1";
constexpr char* UI_TEST_VER_002_BUTTON2 = "ver_002_button2";
constexpr char* UI_TEST_VER_003_BUTTON3 = "ver_002_button3";

constexpr char* UI_TEST_ADD_TO_HEAD = "add_to_head";
constexpr char* UI_TEST_ADD_TO_TAIL = "add_to_tail";
constexpr char* UI_TEST_ADD_TO_BACK_OF_HEAD = "add_to_back_of_head";
constexpr char* UI_TEST_DELETE_HEAD = "delete_head";
constexpr char* UI_TEST_DELETE_MIDDLE = "delete_middle";
constexpr char* UI_TEST_DELETE_ALL = "delete_all";
constexpr char* UI_TEST_SET_CYCLE = "set_cycle";
constexpr char* UI_TEST_SWITCH_PAGES = "switch_pages";


class UITestUISwipeView : public UITest, UIView::OnClickListener {
public:
    UITestUISwipeView() {}
    ~UITestUISwipeView() {}
    void SetUp() override;
    void TearDown() override;
    const UIView* GetTestView() override;
    bool OnClick(UIView& view, const ClickEvent& event) override;

    void UIKitSwipeViewTestHorizontal001();
    void UIKitSwipeViewTestHorizontal002();
    void UIKitSwipeViewTestHorizontal003();
    void UIKitSwipeViewTestVer001();
    void UIKitSwipeViewTestVer002();
    void UIKitSwipeViewTestRemove001();
    void UIKitSwipeViewTestAlign001(UISwipeView::AlignMode alignMode);
    void UIKitSwipeViewTestSetCurrentPage();

private:
    void SetUpButton(UILabelButton* btn, const char* title, const char* id);
    void SetLastPos(UIView* view);
    UIScrollView* container_ = nullptr;
    UISwipeView* currentSwipe_ = nullptr;
    UILabelButton* addBtnInHead_ = nullptr;
    UILabelButton* addBtnInTail_ = nullptr;
    UILabelButton* addBtnInMid_ = nullptr;
    UILabelButton* removeHeadBtn_ = nullptr;
    UILabelButton* removeMidBtn_ = nullptr;
    UILabelButton* removeAllBtn_ = nullptr;
    UILabelButton* loopBtn_ = nullptr;
    UILabelButton* changePageBtn_ = nullptr;
    bool loop_ = false;
    int16_t lastX_ = 0;
    int16_t lastY_ = 0;
    int16_t btnNum_ = 0;
};
} // namespace OHOS
#endif // UI_TEST_UI_SWIPE_VIEW_H
