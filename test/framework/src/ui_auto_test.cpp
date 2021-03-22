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

#include "ui_auto_test.h"
#include "components/root_view.h"
#include "components/ui_list.h"
#include "components/ui_view_group.h"
#include "dfx/event_injector.h"
#include "compare_tools.h"
#include "ui_test_app.h"
#include "ui_test_group.h"

namespace OHOS {
int16_t UIAutoTest::GetAbsoluteX(UIView* view) const
{
    if (view == nullptr) {
        return 0xffff;
    }
    int16_t x = 0;
    UIView* pareter = view;
    while (pareter != nullptr) {
        x += pareter->GetX();
        pareter = pareter->GetParent();
    }
    return x;
}

int16_t UIAutoTest::GetAbsoluteY(UIView*  view) const
{
    if (view == nullptr) {
        return 0xffff;
    }
    int16_t y = 0;
    UIView* pareter = view;
    while (pareter != nullptr) {
        y += pareter->GetY();
        pareter = pareter->GetParent();
    }
    return y;
}

UIView* UIAutoTest::GetChildViewById(UIView* node, const char* id) const
{
    if (node == nullptr || id == nullptr) {
        return nullptr;
    }
    if (!node->IsViewGroup()) {
        return nullptr;
    }
    UIView* view = node->GetChildById(id);
    if (view != nullptr) {
        return view;
    }
    UIView* child = reinterpret_cast<UIViewGroup*>(node)->GetChildrenHead();
    while (child != nullptr) {
        view = GetChildViewById(child, id);
        if (view != nullptr) {
            return view;
        }
        child = child->GetNextSibling();
    }
    return nullptr;
}

void UIAutoTest::ResetMainMenu()
{
    while (RootView::GetInstance()->GetChildById(UI_TEST_MAIN_LIST_ID) == nullptr) {
        ClickViewById(UI_TEST_BACK_BUTTON_ID);
    }
}

void UIAutoTest::EnterSubMenu(const char* id)
{
    if (id == nullptr) {
        return;
    }
    UIView* view = GetChildViewById(RootView::GetInstance(), id);
    if (view == nullptr) {
        UIView* view = GetChildViewById(RootView::GetInstance(), UI_TEST_MAIN_LIST_ID);
        if (view == nullptr) {
            return;
        }
        ListNode<TestCaseInfo>* node = UITestGroup::GetTestCase().Begin();
        while (node != UITestGroup::GetTestCase().End()) {
            if (node->data_.sliceId != nullptr && strcmp(id, node->data_.sliceId) == 0) {
                UITestGroup::GetTestCase().PushFront(node->data_);
                UITestGroup::GetTestCase().Remove(node);
                break;
            }
            node = node->next_;
        }
        reinterpret_cast<UIList*>(view)->RefreshList();
        CompareTools::WaitSuspend();
    }
    ClickViewById(id);
}

void UIAutoTest::ClickViewById(const char* id)
{
    if (id == nullptr) {
        return;
    }
    UIView* view = GetChildViewById(RootView::GetInstance(), id);
    if (view == nullptr) {
        return;
    }
    Point point;
    point.x = GetAbsoluteX(view);
    point.y = GetAbsoluteY(view);
    EventInjector::GetInstance()->SetClickEvent(point);
    CompareTools::WaitSuspend();
}

void UIAutoTest::DragViewToHead(const char* id)
{
    if (id == nullptr) {
        return;
    }
        UIView* view = GetChildViewById(RootView::GetInstance(), id);
    if (view == nullptr) {
        return;
    }
    Point startPoint;
    startPoint.x = GetAbsoluteX(view);
    startPoint.y = GetAbsoluteY(view);

    Point endPoint;
    endPoint.x = 50;
    endPoint.y = 80;
    EventInjector::GetInstance()->SetDragEvent(startPoint, endPoint, 80); // 80: drag time
    CompareTools::WaitSuspend();
}
} //namespace OHOS
