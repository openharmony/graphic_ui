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
 * @tc.require: issueI5AD4A
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

/**
 * @tc.name: InsertText_001
 * @tc.desc: Verify InsertText function, equal.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(InputMethodManagerTest, InsertText_001, TestSize.Level0)
{
    TestInputMethodListener* listener = new TestInputMethodListener();
    InputMethodManager& inputMethodManager =  InputMethodManager::GetInstance();
    inputMethodManager.SetInputMethodListener(listener);
    UIEditText* editView = new UIEditText();
    inputMethodManager.ShowInputMethod(editView);
    std::string text = "hello";
    inputMethodManager.InsertText(text);
    int16_t ret = text.compare(editView->GetText());
    EXPECT_EQ(ret, 0);

    delete listener;
    listener = nullptr;
    delete editView;
    editView = nullptr;
}

/**
 * @tc.name: DeleteBackward_001
 * @tc.desc: Verify DeleteBackward function, equal.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(InputMethodManagerTest, DeleteBackward_001, TestSize.Level0)
{
    TestInputMethodListener* listener = new TestInputMethodListener();
    InputMethodManager& inputMethodManager =  InputMethodManager::GetInstance();
    inputMethodManager.SetInputMethodListener(listener);
    UIEditText* editView = new UIEditText();
    inputMethodManager.ShowInputMethod(editView);
    std::string text = "hello world";
    inputMethodManager.InsertText(text);
    int16_t ret = text.compare(editView->GetText());
    EXPECT_EQ(ret, 0);

    uint16_t length = 0;
    inputMethodManager.DeleteBackward(length);
    EXPECT_EQ(editView->GetText(), text);

    uint16_t length1 = 1;
    inputMethodManager.DeleteBackward(length1);
    std::string tmp = text.substr(0, text.length() - length1);
    ret = tmp.compare(editView->GetText());
    EXPECT_EQ(ret, 0);

    uint16_t length2 = 2; // 2: length
    inputMethodManager.DeleteBackward(length2);
    tmp = text.substr(0, text.length() - length1 - length2);
    ret = tmp.compare(editView->GetText());
    EXPECT_EQ(ret, 0);

    uint16_t length3 = 200; // 200: length
    inputMethodManager.DeleteBackward(length3);
    tmp = "";
    ret = tmp.compare(editView->GetText());
    EXPECT_EQ(ret, 0);

    delete listener;
    listener = nullptr;
    delete editView;
    editView = nullptr;
}

/**
 * @tc.name: SetInputType_001
 * @tc.desc: Verify SetInputType function, equal.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(InputMethodManagerTest, SetInputType_001, TestSize.Level0)
{
    TestInputMethodListener* listener = new TestInputMethodListener();
    InputMethodManager& inputMethodManager =  InputMethodManager::GetInstance();
    inputMethodManager.SetInputMethodListener(listener);
    UIEditText* editView = new UIEditText();
    inputMethodManager.ShowInputMethod(editView);
    inputMethodManager.SetInputType(InputType::TEXT_TYPE);
    EXPECT_EQ(editView->GetInputType(), InputType::TEXT_TYPE);

    inputMethodManager.SetInputType(InputType::PASSWORD_TYPE);
    EXPECT_EQ(editView->GetInputType(), InputType::PASSWORD_TYPE);

    delete listener;
    listener = nullptr;
    delete editView;
    editView = nullptr;
}
} // namespace OHOS