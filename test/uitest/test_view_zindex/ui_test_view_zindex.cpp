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

#include "ui_test_view_zindex.h"

#include "components/ui_label.h"
#include "components/ui_label_button.h"

namespace OHOS {
namespace {
constexpr int16_t BUTTON_OFFSET = 5;
constexpr int16_t BUTTON_GROUP_WIDTH = 150;
constexpr int16_t BUTTON_GROUP_HEIGHT = 600;
constexpr uint8_t ZINDEX_VIEW_NUM = 6;
constexpr uint8_t ZINDEX_BTN_NUM = 8;
constexpr uint8_t ZINDEX_MODIFY_NUM = 7;
constexpr uint8_t CHANGE_ZINDEX_VIEW_Y = 10;
constexpr uint8_t CHANGE_ZINDEX_VIEW_X = 100;
struct ZIndexView {
    const char* text;
    int16_t zIndex;
    ColorType color;
};
struct ZIndexBtn {
    const char* text;
    int16_t zIndex;
};
const ZIndexBtn ZINDEX_BTN_GROUP[ZINDEX_BTN_NUM] = {{"zIndex->-1", -1}, {"zIndex->0", 0}, {"zIndex->1", 1},
                                                    {"zIndex->2", 2},   {"zIndex->3", 3}, {"zIndex->4", 4},
                                                    {"zIndex->5", 5},   {"zIndex->7", 7}};
const ZIndexView ZINDEX_VIEW_GROUP[ZINDEX_VIEW_NUM] = {
    {"zIndex=6", 6, Color::Blue()},      {"zIndex=4", 4, Color::Blue()},      {"zIndex=2", 2, Color::Blue()},
    {"A.zIndex=0", 0, Color::Magenta()}, {"B.zIndex=0", 0, Color::Magenta()}, {"C.zIndex=0", 0, Color::Magenta()}};
const char* ZINDEX_BTN_VIEWID_GROUP[ZINDEX_BTN_NUM] = {"zIndex=-1", "zIndex=0", "zIndex=1", "zIndex=2",
                                                       "zIndex=3", "zIndex=4", "zIndex=5", "zIndex=7"};
const char* MODIFY_INSERT_HEAD = "InsertHead";
const char* MODIFY_INSERT_TAIL = "InsertTail";
const char* MODIFY_AFTER_ZINDEX_4 = "AfterZIndex=4";
const char* MODIFY_AFTER_B_ZINDEX_0 = "AfterB.ZIndex=0";
const char* MODIFY_REMOVE = "Remove";
const char* MODIFY_RESET = "Reset";
const char* MODIFY_ANIMATE_IN = "AnimateIn";
const char* ZINDEX_MODIFY_GROUP[ZINDEX_MODIFY_NUM] = {
    MODIFY_INSERT_HEAD, MODIFY_INSERT_TAIL, MODIFY_AFTER_ZINDEX_4, MODIFY_AFTER_B_ZINDEX_0,
    MODIFY_REMOVE,      MODIFY_RESET,       MODIFY_ANIMATE_IN};
const char* ID_CHANGE_MY_ZINDEX = "Change zIndex";
const char* ID_CLICK_HINT = "clickHint";
const char* ID_ZINDEX_VIEW_VG = "zIndex_view_group1";
const char* ID_ZINDEX_BUTTON_VG = "zIndex_button_group";
const char* ID_CHILD_CHANGE_VG = "child_change_btn_group";
} // namespace
UITestViewZIndex::~UITestViewZIndex()
{
    // todo
}
void UITestViewZIndex::SetUp()
{
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight() - BACK_BUTTON_HEIGHT);
        container_->SetHorizontalScrollState(false);
        container_->SetThrowDrag(true);
    }
}

void UITestViewZIndex::TearDown()
{
    DeleteChildren(container_);
    container_ = nullptr;
    if (animator_ != nullptr) {
        delete animator_;
        animator_ = nullptr;
    }
}

const UIView* UITestViewZIndex::GetTestView()
{
    UIKitViewZIndex001();
    return container_;
}

UILabel* UITestViewZIndex::CreateTitleLabel() const
{
    UILabel* label = new UILabel();
    label->SetHeight(TITLE_LABEL_DEFAULT_HEIGHT);
    label->SetLineBreakMode(UILabel::LINE_BREAK_STRETCH);
    label->SetPosition(TEXT_DISTANCE_TO_LEFT_SIDE, TEXT_DISTANCE_TO_TOP_SIDE);
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    return label;
}

UILabel* UITestViewZIndex::CreateZIndexLabel(const char* text, int16_t zIndex, ColorType color)
{
    UILabel* label = new UILabel();
    label->Resize(300, 70); // 300: width 70:height
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    label->SetZIndex(zIndex);
    label->SetText(text);
    label->SetViewId(text);
    label->SetOnClickListener(this);
    label->SetTouchable(true);
    label->SetStyle(STYLE_BACKGROUND_COLOR, color.full);
    label->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
    label->SetStyle(STYLE_BORDER_COLOR, Color::Red().full);
    label->SetStyle(STYLE_BORDER_OPA, OPA_OPAQUE);
    label->SetStyle(STYLE_BORDER_WIDTH, 2); // 2: border width
    label->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    return label;
}

UILabelButton* UITestViewZIndex::CreateZIndexBtn(const char* text, const char* viewId)
{
    UILabelButton* btn = new UILabelButton();
    btn->Resize(120, 40);                           // 120: width 40:height
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, 15); // 15: font size
    btn->SetText(text);
    btn->SetViewId(viewId);
    btn->SetOnClickListener(this);
    return btn;
}

bool UITestViewZIndex::OnClick(UIView& view, const ClickEvent& event)
{
    if (container_ == nullptr) {
        return true;
    }

    ClickZIndexBtn(view);
    ClickModifyBtn(view);
    UpdateClickHint(view);

    container_->Invalidate();
    return true;
}

void UITestViewZIndex::ClickZIndexBtn(UIView& view)
{
    UIView* zIndexView = container_->GetChildById(ID_CHANGE_MY_ZINDEX);
    if (zIndexView == nullptr) {
        return;
    }
    const char* id = view.GetViewId();
    for (uint8_t i = 0; i < ZINDEX_BTN_NUM; i++) {
        if (strcmp(id, ZINDEX_BTN_VIEWID_GROUP[i]) == 0) {
            zIndexView->SetZIndex(ZINDEX_BTN_GROUP[i].zIndex);
        }
    }
}

void UITestViewZIndex::ClickModifyBtn(UIView& view)
{
    UIView* zIndexView = container_->GetChildById(ID_CHANGE_MY_ZINDEX);
    if (zIndexView == nullptr) {
        SetupChangeView();
        zIndexView = container_->GetChildById(ID_CHANGE_MY_ZINDEX);
    }
    UIView* zIndexViewGroupTmp = container_->GetChildById(ID_ZINDEX_VIEW_VG);
    if (zIndexViewGroupTmp == nullptr) {
        return;
    }

    UIViewGroup* zIndexViewGroup = reinterpret_cast<UIViewGroup*>(zIndexViewGroupTmp);
    const char* id = view.GetViewId();
    if (strcmp(id, MODIFY_INSERT_HEAD) == 0) {
        zIndexViewGroup->Remove(zIndexView);
        zIndexViewGroup->Insert(zIndexViewGroup->GetChildrenHead(), zIndexView);
    } else if (strcmp(id, MODIFY_INSERT_TAIL) == 0) {
        zIndexViewGroup->Remove(zIndexView);
        zIndexViewGroup->Add(zIndexView);
    } else if (strcmp(id, MODIFY_AFTER_ZINDEX_4) == 0) {
        zIndexViewGroup->Remove(zIndexView);
        zIndexViewGroup->Insert(zIndexViewGroup->GetChildrenHead()->GetNextSibling(), zIndexView);
    } else if (strcmp(id, MODIFY_AFTER_B_ZINDEX_0) == 0) {
        zIndexViewGroup->Remove(zIndexView);
        UIView* view5 = container_->GetChildById(ZINDEX_VIEW_GROUP[4].text); // 4 : the fifth view
        if (view5 == nullptr) {
            return;
        }
        zIndexViewGroup->Insert(view5, zIndexView);
    } else if (strcmp(id, MODIFY_REMOVE) == 0) {
        zIndexViewGroup->Remove(zIndexView);
    } else if (strcmp(id, MODIFY_RESET) == 0) {
        zIndexViewGroup->Remove(zIndexView);
        SetupChangeView();
    } else if (strcmp(id, MODIFY_ANIMATE_IN) == 0) {
        if (animator_ != nullptr) {
            animator_->Stop();
            delete animator_;
        }

        zIndexView->SetY(container_->GetHeight());
        animator_ = new Animator(this, zIndexView, 15, true); // 15: time millsec
        animator_->Start();
    }
}

void UITestViewZIndex::Callback(UIView* view)
{
    if ((view == nullptr) || (container_ == nullptr)) {
        return;
    }
    int16_t y = view->GetY();
    int16_t step = 2;
    if (y <= CHANGE_ZINDEX_VIEW_Y) {
        animator_->Stop();
        return;
    }
    if (y - step < CHANGE_ZINDEX_VIEW_Y) {
        y = CHANGE_ZINDEX_VIEW_Y;
    } else {
        y -= step;
    }
    view->Invalidate();
    view->SetY(y);
    view->Invalidate();
}

void UITestViewZIndex::UpdateClickHint(UIView& view)
{
    UIView* tmpView = container_->GetChildById(ID_CLICK_HINT);
    if (tmpView == nullptr) {
        return;
    }
    UILabel* clickHint = reinterpret_cast<UILabel*>(tmpView);
    clickHint->SetText(view.GetViewId());
}

void UITestViewZIndex::UIKitViewZIndex001()
{
    if (container_ == nullptr) {
        return;
    }
    SetupZIndexView();
    SetupZIndexBtn();
    SetupChildModifyBtn();
}

void UITestViewZIndex::SetupZIndexView()
{
    UIViewGroup* group = new UIViewGroup();
    container_->Add(group);
    group->SetOnClickListener(this);
    group->SetTouchable(true);
    group->SetViewId(ID_ZINDEX_VIEW_VG);
    group->SetPosition(48, 5, 500, 500); // 48:position x 5: offset 500: width/height

    int16_t alignBottom = -55;
    int16_t alignLeft = 30;
    for (uint8_t i = 0; i < ZINDEX_VIEW_NUM; i++) {
        UILabel* zIndexView =
            CreateZIndexLabel(ZINDEX_VIEW_GROUP[i].text, ZINDEX_VIEW_GROUP[i].zIndex, ZINDEX_VIEW_GROUP[i].color);
        group->Add(zIndexView);
        if (i == 0) {
            zIndexView->SetPosition(0, 0);
        } else {
            if (i == 3) { // 3: for zindex 0 group
                zIndexView->AlignBottomToSibling(ZINDEX_VIEW_GROUP[i - 1].text, alignBottom - 80); // 80: offset
                zIndexView->AlignLeftToSibling(ZINDEX_VIEW_GROUP[0].text, alignLeft);
            } else {
                zIndexView->AlignBottomToSibling(ZINDEX_VIEW_GROUP[i - 1].text, alignBottom);
                zIndexView->AlignLeftToSibling(ZINDEX_VIEW_GROUP[i - 1].text, alignLeft);
            }
        }
    }

    SetupChangeView();
}

void UITestViewZIndex::SetupChangeView()
{
    UIView* zIndexViewGroupTmp = container_->GetChildById(ID_ZINDEX_VIEW_VG);
    if (zIndexViewGroupTmp == nullptr) {
        return;
    }
    UIViewGroup* group = reinterpret_cast<UIViewGroup*>(zIndexViewGroupTmp);
    UILabel* target = CreateZIndexLabel(ID_CHANGE_MY_ZINDEX, 0, Color::Cyan());
    target->SetTextColor(Color::Black());
    UIView* tmpView = group->GetChildById(ZINDEX_VIEW_GROUP[2].text);
    if (tmpView == nullptr) {
        delete target;
        return;
    }
    group->Insert(tmpView, target);
    target->SetPosition(CHANGE_ZINDEX_VIEW_X, CHANGE_ZINDEX_VIEW_Y);
    target->Resize(200, 400); // 200:width 400:height
}

void UITestViewZIndex::SetupZIndexBtn()
{
    UIViewGroup* group = new UIViewGroup();
    container_->Add(group);
    group->SetOnClickListener(this);
    group->SetViewId(ID_ZINDEX_BUTTON_VG);
    group->Resize(BUTTON_GROUP_WIDTH, BUTTON_GROUP_HEIGHT);
    group->LayoutRightToSibling(ID_ZINDEX_VIEW_VG);

    UILabel* clickHint = new UILabel();
    clickHint->Resize(150, 30);    // 150: width 30: height
    clickHint->SetPosition(0, 10); // 10: offset y
    clickHint->SetFont(DEFAULT_VECTOR_FONT_FILENAME, FONT_DEFAULT_SIZE);
    clickHint->SetViewId(ID_CLICK_HINT);
    clickHint->SetAlign(TEXT_ALIGNMENT_LEFT, TEXT_ALIGNMENT_CENTER);
    group->Add(clickHint);

    for (uint8_t i = 0; i < ZINDEX_BTN_NUM; i++) {
        UILabelButton* zIndexBtn = CreateZIndexBtn(ZINDEX_BTN_GROUP[i].text, ZINDEX_BTN_VIEWID_GROUP[i]);
        group->Add(zIndexBtn);
        if (i == 0) {
            zIndexBtn->SetPosition(0, 50); // 50: offset y
        } else {
            zIndexBtn->LayoutBottomToSibling(ZINDEX_BTN_VIEWID_GROUP[i - 1], BUTTON_OFFSET);
            zIndexBtn->AlignLeftToSibling(ZINDEX_BTN_VIEWID_GROUP[i - 1]);
        }
    }
}

void UITestViewZIndex::SetupChildModifyBtn()
{
    UIViewGroup* group = new UIViewGroup();
    container_->Add(group);
    group->SetOnClickListener(this);
    group->SetViewId(ID_CHILD_CHANGE_VG);
    group->Resize(BUTTON_GROUP_WIDTH, BUTTON_GROUP_HEIGHT);
    group->LayoutRightToSibling(ID_ZINDEX_BUTTON_VG);

    for (uint8_t i = 0; i < ZINDEX_MODIFY_NUM; i++) {
        UILabelButton* zIndexModifyBtn = CreateZIndexBtn(ZINDEX_MODIFY_GROUP[i], ZINDEX_MODIFY_GROUP[i]);
        zIndexModifyBtn->SetWidth(150); // 150: width
        group->Add(zIndexModifyBtn);
        if (i == 0) {
            zIndexModifyBtn->SetPosition(0, 50); // 50: position y
        } else {
            zIndexModifyBtn->LayoutBottomToSibling(ZINDEX_MODIFY_GROUP[i - 1], BUTTON_OFFSET);
            zIndexModifyBtn->AlignLeftToSibling(ZINDEX_MODIFY_GROUP[i - 1]);
        }
    }
}
} // namespace OHOS
