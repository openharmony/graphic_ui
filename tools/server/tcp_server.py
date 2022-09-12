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

import threading
import socket
import json
import time
import subprocess
import os
import shutil


class TestServer(threading.Thread):

    IP = '127.0.0.1'

    PORT = 23495

    config_file_name = "config.json"

    # Run base_ Dir directory
    TestModeBase = 1

    # Run run_dir directory                 
    TestModeRun = 2

    # Send config information                  
    S_C_MAIN_ID_SEND_CONFIG_INFO = 1

    # Request to start test
    C_S_MAIN_ID_REQUEST_TEST_INFO = 2

    # Distribute test data
    S_C_MAIN_ID_SEND_TEST_INFO = 3

    # Test a set of data
    C_S_MAIN_ID_TEST_FINISH_INFO = 4

    # All tests completed
    S_C_MAIN_ID_All_TESTS_COMPLETE = 5


    def __init__(self):
        threading.Thread.__init__(self)
        print("tcp_server_init__")
        self.tcp_server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.tcp_server_socket.bind((self.IP, self.PORT))
        self.tcp_server_socket.listen(128)

        self.config = self.read_data_from_json(self.config_file_name)
        self.test_group_index = 0


    def send_message(self, conn, info):
        clientdata = json.dumps(info).encode("utf-8")
        print('send msg:  ', clientdata)
        conn.send(clientdata)


    def init_data(self):
        self.test_case_index = 0
        self.test_case = self.config['testGroup'][self.test_group_index]['test_case']
        self.test_case_dir = self.config['testGroup'][self.test_group_index]['test_case_dir']

        if len(self.config['testGroup'][self.test_group_index]['test_case']) <= 0:
            self.test_case = self.traverasl_files(self.config['testGroup'][self.test_group_index]['test_case_dir'])
            print(self.test_case)


    def tcp_connect(self, conn, addr):
        print(' Connected by: ', addr)
        time.sleep(3)

        self.init_data()
        self.start_test(conn)
        while True:
            data = conn.recv(1024)
            data = (int)(data.decode("utf-8"))
            print("recv msg: ", data)
            if data == self.C_S_MAIN_ID_REQUEST_TEST_INFO:
                print("begin test: ", data)
                self.test_case_index = 0
                self.send_test_info(conn)
            elif data == self.C_S_MAIN_ID_TEST_FINISH_INFO:
                self.test_case_index += 1
                self.send_test_info(conn)


    def send_all_test_finish(self, conn):
        send_config =  {'main_id':self.S_C_MAIN_ID_All_TESTS_COMPLETE}
        self.send_message(conn, send_config)

        self.test_group_index += 1
        if self.test_group_index >= len(self.config['testGroup']):
            self.test_group_index = 0
            return

        print("send_all_test_finish------test_group_index=", self.test_group_index,\
                "------len=", len(self.config['testGroup']))
        self.start_client_process()


    def send_test_info(self, conn):
        if len(self.test_case):
            if self.test_case_index < len(self.test_case):
                json_data = self.read_data_from_json(self.test_case_dir + '/' + self.test_case[self.test_case_index])
                json_data['main_id'] = self.S_C_MAIN_ID_SEND_TEST_INFO
                print(json_data)
                self.send_message(conn, json_data)
            else:
                self.send_all_test_finish(conn)


    def start_test(self, conn):
        send_config = self.config['testGroup'][self.test_group_index]
        test_mode = send_config['test_mode']
        base_dir = send_config['base_dir']
        run_dir = send_config['run_dir']
        log_dir = send_config['log_dir']

        if test_mode == self.TestModeBase:
            self.clear_directory(base_dir)
        elif test_mode == self.TestModeRun:
            self.clear_directory(run_dir)

        send_config =  {'main_id': self.S_C_MAIN_ID_SEND_CONFIG_INFO,\
            'test_mode': test_mode,\
            'base_dir': base_dir,\
            'run_dir': run_dir,\
            'log_dir': log_dir}

        self.send_message(conn, send_config)


    def read_data_from_json(self, filename):
        with open(filename, 'r') as json_file:
            json_data = json.load(json_file)

        return json_data


    def start_client_process(self):
        print(time.time(), '----time is up')
        process_dir = self.config['testGroup'][self.test_group_index]['process_dir']
        process_name = self.config['testGroup'][self.test_group_index]['process_name']

        process = process_dir + process_name + ' -f'
        subprocess.Popen(process, cwd=process_dir)
        result = subprocess.getstatusoutput(process_dir)
        print(result)


    def traverasl_files(self, path):
        self.filelist = []
        obj = os.scandir(path)
        for entry in obj:
            if entry.is_file():
                self.filelist.append(entry.name)

        return self.filelist


    def clear_directory(self, filepath):
        if not os.path.exists(filepath):
            os.mkdir(filepath)
        else:
            shutil.rmtree(filepath)
            os.mkdir(filepath)


    def run(self):
        print("TcpServer_run__")
        while True:
            conn, addr = self.tcp_server_socket.accept()
            print("TcpServer_run__, conn, addr", conn, addr)
            thread_recv = threading.Thread(target=self.tcp_connect, args=(conn, addr))
            thread_recv.start()

        self.tcp_server_socket.close()