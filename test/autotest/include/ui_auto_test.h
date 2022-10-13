/*
 * Copyright (c) 2020-2022 Huawei Device Co., Ltd.
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

#ifndef GRAPHIC_LITE_AUTO_TEST_H
#define GRAPHIC_LITE_AUTO_TEST_H

#include "components/ui_view.h"
#include "compare_tools.h"
#include "ui_test_message.h"

namespace OHOS {
constexpr int WAIT_TIME_MUBLITE = 4;
constexpr uint16_t DRAGE_DEFAULT_WAIT_TIME = 3000;
class UIAutoTest {
public:
    UIAutoTest();
    virtual ~UIAutoTest();

    void ResetMainMenu() const;
    void Reset(std::string testID) const;

    void RunTest(std::vector<std::shared_ptr<TestMsgInfo>> msgInfo);
    void TestComplete() const;

    void EnterSubMenu(const char* id) const;
    void ClickViewById(const char* id) const;
    void DragViewToHead(const char* id) const;
    bool CompareByBinary(const char* fileName) const;
    void DrageToView(const char* id, int16_t x, int16_t y) const;

private:
    void OnTest(std::shared_ptr<TestMsgInfo> info);
    void OnEnterPage(std::vector<std::string> pageNav);
    void OnTestBySteps(std::vector<TestSteps> steps, std::string className);
    void OnTestOneStep(TestSteps step, std::string className, size_t stepIndex);
    void OnSaveFile(std::string className, std::string viewID, size_t stepIndex);
    void OnCompareFile(std::string fileName) const;
    std::string OnGetSystemTime() const;

private:
    std::vector<std::string> fileNames_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_AUTO_TEST_H
