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

#include "components/ui_edit_text.h"
#include "common/input_method_manager.h"

#include <climits>
#include <gtest/gtest.h>

using namespace testing::ext;
namespace OHOS {
class InputMethodManagerTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
};

class TestInputMethodListener : public InputMethodManager::InputMethodListener {
public:
    void OnShow(InputMethodManager::InputMethodParam& param) override
    {
        showStatus = true;
    }

    void OnHide() override
    {
        showStatus = false;
    }

    bool GetShowStatus()
    {
        return showStatus;
    }

private:
    bool showStatus = false;
};

void InputMethodManagerTest::SetUpTestCase(void)
{
}

void InputMethodManagerTest::TearDownTestCase(void)
{
    InputMethodManager& inputMethodManager =  InputMethodManager::GetInstance();
    inputMethodManager.SetInputMethodListener(nullptr);
}

/**
 * @tc.name: ShowInputMethod_001
 * @tc.desc: Verify ShowInputMethod function, equal.
 * @tc.type: FUNC
 */
HWTEST_F(InputMethodManagerTest, ShowInputMethod_001, TestSize.Level0)
{
    TestInputMethodListener* listener = new TestInputMethodListener();
    InputMethodManager& inputMethodManager =  InputMethodManager::GetInstance();
    inputMethodManager.SetInputMethodListener(listener);
    UIEditText* editView = new UIEditText();

    inputMethodManager.ShowInputMethod(editView);
    EXPECT_EQ(listener->GetShowStatus(), true);

    inputMethodManager.HideInputMethod();
    EXPECT_EQ(listener->GetShowStatus(), false);

    delete listener;
    listener = nullptr;
    delete editView;
    editView = nullptr;
}
} // namespace OHOS