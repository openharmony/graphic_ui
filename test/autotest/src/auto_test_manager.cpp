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

#include "auto_test_manager.h"

#include <iostream>
#include <memory>

#include "dfx/event_injector.h"

namespace OHOS {
AutoTestManager::AutoTestManager()
{
    SetUpTestCase();
}

AutoTestManager::~AutoTestManager()
{
    TearDownTestCase();
}

AutoTestManager* AutoTestManager::GetInstance()
{
    static AutoTestManager instance;
    return &instance;
}

void AutoTestManager::SetUpTestCase()
{
    autoTest_ = std::make_shared<UIAutoTest>();

#ifdef _WIN32
    const char logPath[] = ".\\auto_test_log.txt";
    CompareTools::SetLogPath(logPath, sizeof(logPath));
#else
    const char logPath[] = "./auto_test_log.txt";
    CompareTools::SetLogPath(logPath, sizeof(logPath));
#endif
    EventInjector::GetInstance()->RegisterEventInjector(EventDataType::POINT_TYPE);
    EventInjector::GetInstance()->RegisterEventInjector(EventDataType::KEY_TYPE);
#if defined(ENABLE_WINDOW) && ENABLE_WINDOW
    Window* window = RootView::GetInstance()->GetBoundWindow();
    if (window != nullptr) {
        EventInjector::GetInstance()->SetWindowId(window->GetWindowId());
    }
#endif
}

void AutoTestManager::TearDownTestCase()
{
    if (EventInjector::GetInstance()->IsEventInjectorRegistered(EventDataType::POINT_TYPE)) {
        EventInjector::GetInstance()->UnregisterEventInjector(EventDataType::POINT_TYPE);
    }
    if (EventInjector::GetInstance()->IsEventInjectorRegistered(EventDataType::KEY_TYPE)) {
        EventInjector::GetInstance()->UnregisterEventInjector(EventDataType::KEY_TYPE);
    }
}

void AutoTestManager::SendMsg(size_t mainID)
{
    sendMsgFunc_(mainID);
}

void AutoTestManager::SetSendMsgFuncCallBack(SendMsgFunc sendMsgFunc)
{
    sendMsgFunc_ = sendMsgFunc;
}

void AutoTestManager::StartTest(std::vector<std::shared_ptr<TestMsgInfo>> msgInfo)
{
    printf("AutoTestManager::StartTest----msgInfo.size=[%d]\n", msgInfo.size());
    fflush(stdout);
    if (!autoTest_) {
        return;
    }

    autoTest_->RunTest(msgInfo);
}

void AutoTestManager::TestComplete()
{
    if (!autoTest_) {
        return;
    }

    autoTest_->TestComplete();
}

void AutoTestManager::SetConfigInfo(const std::shared_ptr<TestConfigInfo> configInfo)
{
    configInfo_ = configInfo;
    printf("AutoTestManager::SetConfigInfo--testMode=[%zu], baseDir=[%s], runDir=[%s], logDir=[%s]\n",
        configInfo_->testMode, configInfo_->baseDir.c_str(), configInfo_->runDir.c_str(),
        configInfo_->logDir.c_str());
    fflush(stdout);
    SendMsg(C_S_MAIN_ID_REQUEST_TEST_INFO);
}

std::shared_ptr<TestConfigInfo> AutoTestManager::GetConfigInfo()
{
    return configInfo_;
}
}
