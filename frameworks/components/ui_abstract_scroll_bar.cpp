/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "components/ui_abstract_scroll_bar.h"
#include "gfx_utils/graphic_log.h"
#include "themes/theme_manager.h"

namespace OHOS {
UIAbstractScrollBar::UIAbstractScrollBar() : backgroundStyleAllocFlag_(false), foregroundStyleAllocFlag_(false)
{
    Theme* theme = ThemeManager::GetInstance().GetCurrent();
    if (theme != nullptr) {
        backgroundStyle_ = &(theme->GetProgressBackgroundStyle());
        foregroundStyle_ = &(theme->GetProgressForegroundStyle());
    } else {
        backgroundStyle_ = &(StyleDefault::GetProgressBackgroundStyle());
        foregroundStyle_ = &(StyleDefault::GetProgressForegroundStyle());
    }
}

UIAbstractScrollBar::~UIAbstractScrollBar()
{
    if (backgroundStyleAllocFlag_) {
        delete backgroundStyle_;
        backgroundStyle_ = nullptr;
        backgroundStyleAllocFlag_ = false;
    }

    if (foregroundStyleAllocFlag_) {
        delete foregroundStyle_;
        foregroundStyle_ = nullptr;
        foregroundStyleAllocFlag_ = false;
    }
}

void UIAbstractScrollBar::SetBackgroundStyle(const Style& backroundStyle)
{
    if (!backgroundStyleAllocFlag_) {
        backgroundStyle_ = new Style();
        if (backgroundStyle_ == nullptr) {
            GRAPHIC_LOGE("new Style fail");
            return;
        }
        backgroundStyleAllocFlag_ = true;
    }
    *backgroundStyle_ = backroundStyle;
}

void UIAbstractScrollBar::SetForegroundStyle(const Style& foregroundStyle)
{
    if (!foregroundStyleAllocFlag_) {
        foregroundStyle_ = new Style();
        if (foregroundStyle_ == nullptr) {
            GRAPHIC_LOGE("new Style fail");
            return;
        }
        foregroundStyleAllocFlag_ = true;
    }
    *foregroundStyle_ = foregroundStyle;
}
} // namespace OHOS