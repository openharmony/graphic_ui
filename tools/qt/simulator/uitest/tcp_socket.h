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

#ifndef GRAPHIC_LITE_TCP_SOCKET_H
#define GRAPHIC_LITE_TCP_SOCKET_H

#include <QtCore/qobject.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include "tcp_socket_manager.h"

const QString IP = "127.0.0.1";
const quint16 port = 23495;

namespace OHOS {
class TcpSocketClientManager;
class TcpScoketClient : public QObject {
    Q_OBJECT

public:
    TcpScoketClient();
    virtual ~TcpScoketClient();
    void CreateTCPScoket();
    void SetScoketManager(TcpSocketClientManager* tcpSocketManager);
    void OnSendMessage(QString& message);
    void ConnectSocket();

private slots:
    void OnConnected();
    void OnDisconnected();
    void OnSocketStateChange(QAbstractSocket::SocketState socketState);
    void OnSocketReadyRead();

public:

private:
    QTcpSocket* tcpSocket_;
    TcpSocketClientManager* tcpSocketManager_;
};
} // namespace OHOS

#endif // GRAPHIC_LITE_TCP_SOCKET_H
