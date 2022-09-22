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
 
#include "components/ui_tree_manager.h"

namespace OHOS {
UITreeManager& UITreeManager::GetInstance()
{
    static UITreeManager manager;
    return manager;
}

void UITreeManager::RegistViewLifeEvent(ViewFunc* func)
{
    auto p = lifeEvents_.Begin();
    if (func == nullptr) {
        return;
    }
    while (p != lifeEvents_.End()) {
        if (p->data_ == func) {
            return;
        }
        p = p->next_;
    }
    lifeEvents_.PushBack(func);
}

void UITreeManager::UnregistViewLifeEvent(ViewFunc* func)
{
    auto p = lifeEvents_.Begin();
    while (p != lifeEvents_.End()) {
        if (p->data_ == func) {
            lifeEvents_.Remove(p);
            return;
        }
        p = p->next_;
    }
}

void UITreeManager::GetLastEvent(UIView*& view, ViewLifeEvent& event)
{
    view = lastEventView_;
    event = lastEvent_;
}

void UITreeManager::OnLifeEvent(UIView* view, ViewLifeEvent event)
{
    lastEventView_ = view;
    lastEvent_ = event;
    auto p = lifeEvents_.Begin();
    while (p != lifeEvents_.End()) {
        p->data_();
        p = p->next_;
    }
}

} // namespace OHOS
