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

#ifndef GRAPHIC_LITE_AUTO_TEST_MANAGER_H
#define GRAPHIC_LITE_AUTO_TEST_MANAGER_H

#include "components/ui_view.h"
#include "graphic_config.h"
#include "ui_test_message.h"
#include "ui_auto_test.h"

namespace OHOS {
using SendMsgFunc = std::function<void(size_t)>;
class AutoTestManager {
public:
    AutoTestManager();
    virtual ~AutoTestManager();
    static AutoTestManager* GetInstance();

    void SetUpTestCase();
    void TearDownTestCase();
    void SendMsg(size_t mainID);
    void StartTest(std::vector<std::shared_ptr<TestMsgInfo>> msgInfo);
    void SetSendMsgFuncCallBack(SendMsgFunc sendMsgFunc);
    void SetConfigInfo(const std::shared_ptr<TestConfigInfo> configInfo);
    std::shared_ptr<TestConfigInfo> GetConfigInfo();
    void TestComplete();

private:
    std::shared_ptr<UIAutoTest> autoTest_;
    SendMsgFunc sendMsgFunc_;
    std::shared_ptr<TestConfigInfo> configInfo_;
};
} // namespace OHOS

#endif  // GRAPHIC_LITE_AUTO_TEST_MANAGER_H
