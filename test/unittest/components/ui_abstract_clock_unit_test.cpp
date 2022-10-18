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
#include "components/ui_abstract_clock.h"

#include <climits>
#include <gtest/gtest.h>

using namespace testing::ext;

namespace OHOS {
namespace {
    uint8_t CURRENT_HOUR = 14;
    uint8_t CURRENT_MINUTE = 40;
    uint8_t CURRENT_SECOND = 30;
    const uint8_t INIT_HOUR = 24;
    const uint8_t INIT_MINUTE = 60;
    const uint8_t INIT_SECOND = 60;
    const bool CLOCK_INT = 1;
}

class UIAbstractClockUnitTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static UIAbstractClock* clock_;
};

UIAbstractClock* UIAbstractClockUnitTest::clock_ = nullptr;

void UIAbstractClockUnitTest::SetUpTestCase()
{
    if (clock_ == nullptr) {
        clock_ = new UIAbstractClock();
    }
}

void UIAbstractClockUnitTest::TearDownTestCase()
{
    if (clock_ != nullptr) {
        delete clock_;
        clock_ = nullptr;
    }
}

/**
 * @tc.name: UIAbstractClockIncOneSecond_001
 * @tc.desc: Verify IncOneSecond function.
 */
HWTEST_F(UIAbstractClockUnitTest, UIAbstractClockIncOneSecond_001, TestSize.Level1)
{
    if (clock_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    clock_->SetTime24Hour(CURRENT_HOUR, CURRENT_MINUTE, CURRENT_SECOND);
    clock_->IncOneSecond();
    CURRENT_SECOND++;
    CURRENT_MINUTE += CURRENT_SECOND / INIT_SECOND;
    CURRENT_SECOND = CURRENT_SECOND % INIT_SECOND;

    CURRENT_HOUR += CURRENT_MINUTE / INIT_MINUTE;
    CURRENT_MINUTE = CURRENT_MINUTE % INIT_MINUTE;
    CURRENT_HOUR = CURRENT_HOUR % INIT_HOUR;
    EXPECT_EQ(clock_->GetCurrentHour(), CURRENT_HOUR);
    EXPECT_EQ(clock_->GetCurrentMinute(), CURRENT_MINUTE);
    EXPECT_EQ(clock_->GetCurrentSecond(), CURRENT_SECOND);
}

/**
 * @tc.name: UIAbstractClockSetWorkMode_001
 * @tc.desc: Verify SetWorkMode function.
 */
HWTEST_F(UIAbstractClockUnitTest, UIAbstractClockSetWorkMode_001, TestSize.Level1)
{
    if (clock_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    clock_->SetWorkMode(UIAbstractClock::ALWAYS_ON);
    EXPECT_EQ(clock_->GetWorkMode(), UIAbstractClock::ALWAYS_ON);
}
}