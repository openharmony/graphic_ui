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

#ifndef GRAPHIC_LITE_FOCUS_MANAGER_H
#define GRAPHIC_LITE_FOCUS_MANAGER_H

#include "components/ui_view.h"

namespace OHOS {
class FocusManager {
public:
    static FocusManager* GetInstance()
    {
        static FocusManager instance;
        return &instance;
    }

    void ClearFocus()
    {
        view_ = nullptr;
    }

    UIView* GetFocusedView()
    {
        return view_;
    }

    void RequestFocus(UIView* view)
    {
        view_ = view;
    }

private:
    FocusManager() : view_(nullptr) {}
    ~FocusManager() {}
    UIView* view_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_FOCUS_MANAGER_H
