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

#include "components/ui_axis.h"

#include <climits>
#include <gtest/gtest.h>

using namespace testing::ext;

namespace OHOS {
namespace {
    const int16_t LARGER_VALUE = 10;
    const int16_t SMALLER_VALUE = 2;
    const bool ENABLE = true;
}
class UIAxisTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    static UIXAxis* axisX_;
    static UIYAxis* axisY_;
};
UIXAxis* UIAxisTest::axisX_ = nullptr;
UIYAxis* UIAxisTest::axisY_ = nullptr;

void UIAxisTest::SetUpTestCase(void)
{
    if (axisX_ == nullptr) {
        axisX_ = new UIXAxis();
    }
    if (axisY_ == nullptr) {
        axisY_ = new UIYAxis();
    }
}

void UIAxisTest::TearDownTestCase(void)
{
    if (axisX_ != nullptr) {
        delete axisX_;
        axisX_ = nullptr;
    }
    if (axisY_ != nullptr) {
        delete axisY_;
        axisY_ = nullptr;
    }
}
/**
 * @tc.name: UIAxisGetViewType_001
 * @tc.desc: Verify GetViewType function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIAxisGetViewType_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(axisX_->GetViewType(), UI_AXIS);
}

/**
 * @tc.name: UIAxisSetLineColor_001
 * @tc.desc: Verify SetLineColor function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIAxisSetLineColor_001, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    axisY_->SetLineColor(Color::Gray());
    EXPECT_EQ(axisY_->GetStyle(STYLE_LINE_COLOR), Color::Gray().full);
}

/**
 * @tc.name: UIXAxisSetDataRange_001
 * @tc.desc: Verify SetDataRange function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIXAxisSetDataRange_001, TestSize.Level0)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(axisX_->SetDataRange(SMALLER_VALUE, LARGER_VALUE), true);
}

/**
 * @tc.name: UIXAxisSetDataRange_002
 * @tc.desc: Verify SetDataRange function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIXAxisSetDataRange_002, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(axisX_->SetDataRange(LARGER_VALUE, SMALLER_VALUE), false);
}

/**
 * @tc.name: UIYAxisSetDataRange_001
 * @tc.desc: Verify SetDataRange function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIYAxisSetDataRange_001, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(axisY_->SetDataRange(SMALLER_VALUE, LARGER_VALUE), true);
}

/**
 * @tc.name: UIYAxisSetDataRange_002
 * @tc.desc: Verify SetDataRange function, equal.
 * @tc.type: FUNC
 * @tc.require: AR000EEMQ8
 */
HWTEST_F(UIAxisTest, UIYAxisSetDataRange_002, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(axisY_->SetDataRange(LARGER_VALUE, SMALLER_VALUE), false);
}

/**
 * @tc.name: UIYAxisSetMarkNum_001
 * @tc.desc: Verify SetMarkNum function, equal.
 */
HWTEST_F(UIAxisTest, UIXAxisSetMarkNum_001, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    int16_t COUNT = 1;
    axisX_->SetMarkNum(COUNT);
    EXPECT_EQ(axisX_->GetMarkNum(), COUNT);
}

/**
 * @tc.name: UIYAxisSetMarkNum_001
 * @tc.desc: Verify SetMarkNum function, equal.
 */
HWTEST_F(UIAxisTest, UIYAxisSetMarkNum_001, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    int16_t COUNT = 1;
    axisY_->SetMarkNum(COUNT);
    EXPECT_EQ(axisY_->GetMarkNum(), COUNT);
    COUNT = 2;
    axisY_->SetMarkNum(COUNT);
    axisY_->UpdateAxis();
    EXPECT_EQ(axisY_->GetMarkNum(), COUNT);
}

/**
 * @tc.name: UIAxisEnableReverse_001
 * @tc.desc: Verify EnableReverse function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisEnableReverse_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    axisX_->EnableReverse(ENABLE);
    EXPECT_EQ(axisX_->GetEnableReverse(), ENABLE);
}

/**
 * @tc.name: UIAxisGetStartPoint_001
 * @tc.desc: Verify GetStartPoint function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisGetStartPoint_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    Point start_ = {0, 0};
    EXPECT_EQ(axisX_->GetStartPoint().x, start_.x);
    EXPECT_EQ(axisX_->GetStartPoint().y, start_.y);
}

/**
 * @tc.name: UIAxisGetEndPoint_001
 * @tc.desc: Verify GetEndPoint function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisGetEndPoint_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    Point end_ = {0, 0};
    EXPECT_EQ(axisX_->GetEndPoint().x, end_.x);
    EXPECT_EQ(axisX_->GetEndPoint().y, end_.y);
}

/**
 * @tc.name: UIAxisGetMarkInterval_001
 * @tc.desc: Verify GetMarkInterval function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisGetMarkInterval_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    float markInterval = 0;
    axisX_->SetMarkInterval(markInterval);
    EXPECT_EQ(axisX_->GetMarkInterval(), markInterval);
}

/**
 * @tc.name: UIAxisOnPreDraw_001
 * @tc.desc: Verify OnPreDraw function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisOnPreDraw_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    Rect* invalidatedArea = new Rect();
    EXPECT_EQ(axisX_->OnPreDraw(*invalidatedArea), false);
    delete invalidatedArea;
    invalidatedArea = nullptr;
}

/**
 * @tc.name: UIAxisUpdateAxisPoints_001
 * @tc.desc: Verify UpdateAxisPoints function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisUpdateAxisPoints_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    axisX_->UpdateAxisPoints();
    Point endx = axisX_->GetEndPoint();
    Point startx = axisX_->GetStartPoint();
    EXPECT_EQ(endx.y, startx.y);
}

/**
 * @tc.name: UIAxisUpdateAxisPoints_002
 * @tc.desc: Verify UpdateAxisPoints function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisUpdateAxisPoints_002, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    axisY_->UpdateAxisPoints();
    Point endx = axisY_->GetEndPoint();
    Point startx = axisY_->GetStartPoint();
    EXPECT_EQ(endx.x, startx.x);
}

/**
 * @tc.name: UIAxisTranslateToPixel_001
 * @tc.desc: Verify TranslateToPixel function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisTranslateToPixel_001, TestSize.Level1)
{
    if (axisX_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    int16_t value = 2;
    float minXStep = 0;
    Point startx = axisX_->GetStartPoint();
    axisX_->TranslateToPixel(value);
    int16_t value2 = startx.x + static_cast<int16_t>((value - 0) * minXStep);
    EXPECT_EQ(value, value2);
}

/**
 * @tc.name: UIAxisTranslateToPixel_002
 * @tc.desc: Verify TranslateToPixel function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisTranslateToPixel_002, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    int16_t value = 2;
    float minYStep = 0;
    Point starty = axisY_->GetStartPoint();
    axisX_->TranslateToPixel(value);
    int16_t value2 = starty.y + static_cast<int16_t>((0 - value + 0) * minYStep);
    EXPECT_EQ(value, value2);
}

/**
 * @tc.name: UIAxisTranslateToPixel_003
 * @tc.desc: Verify TranslateToPixel function, equal.
 */
HWTEST_F(UIAxisTest, UIAxisTranslateToPixel_003, TestSize.Level1)
{
    if (axisY_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    int16_t value = 2;
    float minYStep = 0;
    Point starty = axisY_->GetStartPoint();
    axisY_->TranslateToPixel(value);
    int16_t value2 = starty.y - static_cast<int16_t>((value - 0) * minYStep);
    EXPECT_EQ(value, value2);
}
} // namespace OHOS
