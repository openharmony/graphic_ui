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

#ifndef GRAPHIC_LITE_TCP_SOCKET_CLIENT_MANGER_H
#define GRAPHIC_LITE_TCP_SOCKET_CLIENT_MANGER_H

#include <queue>
#include <QMutex>

#include "common/task.h"
#include "gfx_utils/list.h"
#include "tcp_socket.h"
#include "ui_test_message.h"

namespace OHOS {
class TcpScoketClient;
using DispatchFunc = std::function<void(std::vector<std::shared_ptr<TestMsgInfo>>)>;
using DispatchConfigFunc = std::function<void(std::shared_ptr<TestConfigInfo>)>;
using DispatchCompleteFunc = std::function<void()>;
class TcpSocketClientManager : public QObject {
    Q_OBJECT
public:
    TcpSocketClientManager() = default;
    ~TcpSocketClientManager();
    static TcpSocketClientManager* GetInstance();

    void InitSocket();
    void ConnectSocket();
    void DispatchMsg();
    void RecvMsg(QByteArray recv);
    void SetDispatchFuncCallBack(DispatchFunc dispatchFunc);
    void SetDispatchConfigFuncCallBack(DispatchConfigFunc dispatchConfigFunc);
    void SetDispatchCompleteFuncCallBack(DispatchCompleteFunc dispatchCompleteFunc);

    inline TcpScoketClient *GetTcpSocket()
    {
        return tcpSocket_;
    }

signals:
    void SendMsgSignal(size_t mainID);
public:
    void SendMsg(size_t mainID)
    {
        emit SendMsgSignal(mainID);
    }

private:
    void OnRunRecvMsg();
    void OnGetMsgInfo(const std::shared_ptr<QByteArray> recv);
    void OnGetConfigInfo(const QJsonObject object);
    void OnGetTestInfo(QJsonObject object);
    void OnGetTestInfo(QJsonObject arrobj, std::shared_ptr<TestMsgInfo>& msgInfo);

    void OnGetPageNav(QJsonArray array, std::vector<std::string>& pageNav);
    void OnGetTestSetps(QJsonArray array, std::vector<TestSteps>& steps);
    void OnGetEventValue(QJsonArray array, std::vector<int>& values);
    void OnPrintTestInfo(const std::vector<std::shared_ptr<TestMsgInfo>> testMsgInfo) const;
private:
    TcpScoketClient *tcpSocket_;
    DispatchFunc dispatchFunc_;
    DispatchConfigFunc dispatchConfigFunc_;
    DispatchCompleteFunc dispatchCompleteFunc_;
    std::deque<std::shared_ptr<QByteArray>> recv_;
    QMutex mutex_;
};
} // namespace OHOS

#endif  // GRAPHIC_LITE_TCP_SOCKET_CLIENT_MANGER_H
