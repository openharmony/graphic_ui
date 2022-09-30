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

#ifndef GRAPHIC_LITE_TEST_MESSAGE_H
#define GRAPHIC_LITE_TEST_MESSAGE_H

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace OHOS {
enum TestEventID : uint8_t {
    TEST_CLICK_EVENT,
    TEST_MOVE_EVENT,
};

enum TestMode: uint8_t {
    TEST_MODE_BASE = 1,
    TEST_MODE_RUN,
};

struct TestSteps {
    std::string viewID;
    TestEventID eventID;
    std::vector<int> eventValue;
    bool saveCheckPoint;
};

struct TestMsgInfo {
    std::string className;
    std::vector<std::string> pageNav;
    std::vector<TestSteps> steps;
};

struct TestConfigInfo {
    TestConfigInfo()
    {
        testMode = TEST_MODE_BASE;
    }
    TestMode testMode;
    std::string baseDir;
    std::string runDir;
    std::string logDir;
};

const std::string JSON_VALUE_MAIN_ID = "main_id";
const std::string JOSN_VALUE_TEST_MODE = "test_mode";
const std::string JSON_VALUE_BASE_DIR = "base_dir";
const std::string JSON_VALUE_RUN_DIR = "run_dir";
const std::string JSON_VALUE_LOG_DIR = "log_dir";

const std::string JSON_VALUE_TEST_INFO = "testInfo";
const std::string JSON_VALUE_CLASS_NAME = "className";
const std::string JSON_VALUE_PAGE_NAV = "pageNav";
const std::string JSON_VALUE_TEST_STEPS = "testSteps";
const std::string JSON_VALUE_VIEW_ID = "viewID";
const std::string JSON_VALUE_EVENT_ID = "eventID";
const std::string JSON_VALUE_EVENT_VALUE = "eventValue";
const std::string JSON_VALUE_SAVE_CHECK_POINT = "saveCheckPoint";

const size_t EVENT_VALUE_SIZE_TWO = 2;

const size_t S_C_MAIN_ID_SEND_CONFIG_INFO = 1;              // Send config information
const size_t C_S_MAIN_ID_REQUEST_TEST_INFO = 2;             // Request to start test
const size_t S_C_MAIN_ID_SEND_TEST_INFO = 3;                // Distribute test data
const size_t C_S_MAIN_ID_TEST_FINISH_INFO = 4;              // Test a set of data
const size_t S_C_MAIN_ID_All_TESTS_COMPLETE = 5;            // All tests completed
} // namespace OHOS

#endif // GRAPHIC_LITE_TEST_MESSAGE_H
