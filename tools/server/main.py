#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2022 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import time
import schedule
from tcp_server import TestServer


def main():
    tcp_servr = TestServer()
    tcp_servr.start()
    print(tcp_servr.config)
    start_test_time = tcp_servr.config['start_test_time']
    schedule.every().day.at(start_test_time).do(tcp_servr.start_client_process)

    while True:
        schedule.run_pending()
        time.sleep(1)


if __name__ == "__main__":
    main()
