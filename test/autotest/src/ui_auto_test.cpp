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

#include "ui_auto_test.h"

#include <sys/time.h>
#include "auto_test_manager.h"
#include "components/root_view.h"
#include "components/ui_view_group.h"
#include "dfx/event_injector.h"
#include "ui_test_app.h"
#include "ui_test_group.h"

namespace OHOS {
UIAutoTest::UIAutoTest()
{
}

UIAutoTest::~UIAutoTest()
{
}

void UIAutoTest::Reset(std::string testID) const
{
    ResetMainMenu();
    ClickViewById(testID.c_str());
}

void UIAutoTest::ResetMainMenu() const
{
    while (RootView::GetInstance()->GetChildById(UI_TEST_MAIN_LIST_ID) == nullptr) {
        ClickViewById(UI_TEST_BACK_BUTTON_ID);
    }
}

void UIAutoTest::EnterSubMenu(const char* id) const
{
    if (id == nullptr) {
        return;
    }

    UIView* view = RootView::GetInstance()->GetChildById(id);
    if (view == nullptr) {
        UIView* listView = RootView::GetInstance()->GetChildById(UI_TEST_MAIN_LIST_ID);
        if (listView == nullptr) {
            return;
        }
        ListNode<TestCaseInfo>* node = UITestGroup::GetTestCase().Begin();
        while (node != UITestGroup::GetTestCase().End()) {
            if ((node->data_.sliceId != nullptr) && (strcmp(id, node->data_.sliceId) == 0)) {
                UITestGroup::GetTestCase().PushFront(node->data_);
                UITestGroup::GetTestCase().Remove(node);
                break;
            }
            node = node->next_;
        }
        reinterpret_cast<UIList*>(listView)->RefreshList();
        CompareTools::WaitSuspend();
    }

    ClickViewById(id);
}

void UIAutoTest::ClickViewById(const char* id) const
{
    if (id == nullptr) {
        return;
    }
    UIView* view = RootView::GetInstance()->GetChildById(id);
    if (view == nullptr) {
        return;
    }
    Point point;
    point.x = view->GetOrigRect().GetX();
    point.y = view->GetOrigRect().GetY();
    EventInjector::GetInstance()->SetClickEvent(point);
    CompareTools::WaitSuspend();
}

void UIAutoTest::DragViewToHead(const char* id) const
{
    if (id == nullptr) {
        return;
    }
    UIView* view = RootView::GetInstance()->GetChildById(id);
    if (view == nullptr) {
        return;
    }
    Point startPoint;
    startPoint.x = view->GetOrigRect().GetX();
    startPoint.y = view->GetOrigRect().GetY();

    Point endPoint;
    endPoint.x = 100; // 100 :end point x position;
    endPoint.y = 100; // 100 :end point y position;
    EventInjector::GetInstance()->SetDragEvent(startPoint, endPoint, 100); // 100: drag time
    CompareTools::WaitSuspend();
}

void UIAutoTest::DrageToView(const char* id, int16_t x, int16_t y) const
{
    if (id == nullptr) {
        return;
    }
    UIView* view = RootView::GetInstance()->GetChildById(id);
    if (view == nullptr) {
        return;
    }
    Point startPoint;
    startPoint.x = view->GetOrigRect().GetX();
    startPoint.y = view->GetOrigRect().GetY();

    Point endPoint;
    endPoint.x = x;
    endPoint.y = y;
    EventInjector::GetInstance()->SetDragEvent(startPoint, endPoint, 100); // 100: drag time

    uint16_t waitTime = std::abs((std::abs(x) > std::abs(y) ? x : y) * WAIT_TIME_MUBLITE) + DRAGE_DEFAULT_WAIT_TIME;
    CompareTools::WaitSuspend(waitTime);
}

bool UIAutoTest::CompareByBinary(const char* fileName) const
{
    if (fileName == nullptr) {
        return false;
    }
    char filePath[DEFAULT_FILE_NAME_MAX_LENGTH] = {0};
    CompareTools::StrnCatPath(filePath, DEFAULT_FILE_NAME_MAX_LENGTH, fileName, strlen(fileName));
    if (CompareTools::CheckFileExist(filePath, sizeof(filePath))) {
        return CompareTools::CompareFile(filePath, sizeof(filePath));
    } else {
        return CompareTools::SaveFile(filePath, sizeof(filePath));
    }
}

void UIAutoTest::RunTest(std::vector<std::shared_ptr<TestMsgInfo>> msgInfo)
{
    printf("UIAutoTest::RunTest----testInfo.size=[%d]\n", msgInfo.size());
    fflush(stdout);
    for (auto it: msgInfo) {
        OnTest(it);
    }

    AutoTestManager::GetInstance()->SendMsg(C_S_MAIN_ID_TEST_FINISH_INFO);
}

void UIAutoTest::OnTest(std::shared_ptr<TestMsgInfo> info)
{
    ResetMainMenu();
    OnEnterPage(info->pageNav);
    OnTestBySteps(info->steps, info->className);
}

void UIAutoTest::OnTestBySteps(std::vector<TestSteps> steps, std::string className)
{
    if (steps.empty()) {
        return;
    }

    int stepIndex = 0;
    for (auto it: steps) {
        OnTestOneStep(it, className, stepIndex++);
    }
}

void UIAutoTest::OnTestOneStep(TestSteps step, std::string className, size_t stepIndex)
{
    if (step.eventID == TestEventID::TEST_CLICK_EVENT) {
        ClickViewById(step.viewID.c_str());
    } else if (step.eventID == TestEventID::TEST_MOVE_EVENT) {
        if (step.eventValue.size() < EVENT_VALUE_SIZE_TWO) {
            return;
        }

        int16_t x = static_cast<int16_t>(step.eventValue[0]);
        int16_t y = static_cast<int16_t>(step.eventValue[1]);
        DrageToView(step.viewID.c_str(), x, y);
    }

    if (step.saveCheckPoint) {
        OnSaveFile(className, step.viewID, stepIndex);
    }
}

void UIAutoTest::OnEnterPage(std::vector<std::string> pageNav)
{
    if (pageNav.empty()) {
        return;
    }

    for (auto it: pageNav) {
        EnterSubMenu(it.c_str());
    }
}

void UIAutoTest::OnSaveFile(std::string className, std::string viewID, size_t stepIndex)
{
    std::string fileName = className + "@" + viewID + "@" + std::to_string(stepIndex) + ".bmp";
    fileNames_.push_back(fileName);

    std::string filePath;
    std::shared_ptr<TestConfigInfo> config = AutoTestManager::GetInstance()->GetConfigInfo();
    if (config->testMode == TestMode::TEST_MODE_BASE) {
        filePath =  config->baseDir + fileName;
    } else if (config->testMode == TestMode::TEST_MODE_RUN) {
        filePath =  config->runDir + fileName;
    }

    printf("OnSaveFile, filePath = %s\n", filePath.c_str());
    fflush(stdout);
    CompareTools::SaveFile(filePath.c_str(), strlen(filePath.c_str()));
}

void UIAutoTest::TestComplete() const
{
    printf("UIAutoTest::TestComplete");
    fflush(stdout);
    std::shared_ptr<TestConfigInfo> config = AutoTestManager::GetInstance()->GetConfigInfo();
    if (!config) {
        return;
    }
    if (config->testMode != TestMode::TEST_MODE_RUN) {
        return;
    }

    config->logDir += OnGetSystemTime();
    config->logDir += ".txt";
    printf("UIAutoTest::OnCompareFile--logDir=[%s]\n", config->logDir.c_str());
    fflush(stdout);
    for (auto it: fileNames_) {
        OnCompareFile(it);
    }
}

void UIAutoTest::OnCompareFile(std::string fileName) const
{
    std::shared_ptr<TestConfigInfo> config = AutoTestManager::GetInstance()->GetConfigInfo();
    if (!config) {
        return;
    }

    std::string fileBasePath = config->baseDir + fileName;
    std::string fileRunPath = config->runDir + fileName;

    std::string log;
    if (!CompareTools::CompareFile(fileBasePath.c_str(), fileRunPath.c_str())) {
        printf("UIAutoTest::OnCompareFile----different\n");
        fflush(stdout);
        log = "[FAIL]:[" + fileName + "]\n";
    } else {
        log = "[SUCESS]:[" + fileName + "]\n";
    }

    CompareTools::SaveResultLog(config->logDir.c_str(), log.c_str(), strlen(log.c_str()));
}

std::string UIAutoTest::OnGetSystemTime() const
{
    time_t t = time(0);
    char tmp[32] = { 0 };
    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S", localtime(&t));

    std::string loctime = tmp;

    return loctime;
}
} // namespace OHOS
