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

#ifndef GRAPHIC_LITE_UI_ARC_SCROLL_BAR_H
#define GRAPHIC_LITE_UI_ARC_SCROLL_BAR_H

#include "components/ui_abstract_scroll_bar.h"

namespace OHOS {
class UIArcScrollBar : public UIAbstractScrollBar {
public:
    UIArcScrollBar() = default;

    virtual ~UIArcScrollBar() = default;

    void SetPosition(int16_t x, int16_t y, int16_t width, int16_t radius) override;

    void OnDraw(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea, uint8_t backgroundOpa) override;

    void DrawForeground(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea, uint8_t backgroundOpa);

    void DrawBackground(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea, uint8_t backgroundOpa);

protected:
    static constexpr uint16_t START_ANGLE_IN_DEGREE = 60;
    static constexpr uint16_t END_ANGLE_IN_DEGREE = 120;
    static constexpr uint16_t SCROLL_BAR_WIDTH = 5;
    int16_t radius_ = 0;
    int16_t width_ = SCROLL_BAR_WIDTH;
    uint16_t startAngle_ = START_ANGLE_IN_DEGREE;
    uint16_t endAngle_ = END_ANGLE_IN_DEGREE;
    Point center_ = {0, 0};
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_ARC_SCROLL_BAR_H
