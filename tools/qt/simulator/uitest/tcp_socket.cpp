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

#include "tcp_socket.h"

namespace OHOS {
TcpScoketClient::TcpScoketClient() : tcpSocket_(nullptr), tcpSocketManager_(nullptr)
{
}

TcpScoketClient::~TcpScoketClient()
{
    if (tcpSocket_) {
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }
}

void TcpScoketClient::CreateTCPScoket()
{
    if (tcpSocket_ == nullptr) {
        tcpSocket_ =  new QTcpSocket(this);
    }

    if (tcpSocket_ == nullptr) {
        return;
    }

    connect(tcpSocket_, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(tcpSocket_, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
    connect(tcpSocket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(OnSocketStateChange(QAbstractSocket::SocketState)));
    connect(tcpSocket_, SIGNAL(readyRead()), this, SLOT(OnSocketReadyRead()));
}

void TcpScoketClient::ConnectSocket()
{
    if (tcpSocket_ == nullptr) {
        return;
    }

    tcpSocket_->connectToHost(IP, port);
}

void TcpScoketClient::SetScoketManager(TcpSocketClientManager* tcpSocketManager)
{
    tcpSocketManager_ = tcpSocketManager;
}

void TcpScoketClient::OnConnected()
{
    printf("TcpScoketClient::connected\n");
    fflush(stdout);
}

void TcpScoketClient::OnDisconnected()
{
    printf("TcpScoketClient::onDisconnected\n");
}

void TcpScoketClient::OnSocketStateChange(QAbstractSocket::SocketState socketState)
{
    printf("TcpScoketClient::onSocketStateChange---socketState=[%d]\n", socketState);
    switch (socketState) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ClosingState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        default:
            break;
    }
}

void TcpScoketClient::OnSocketReadyRead()
{
    QByteArray recv = tcpSocket_->readAll();
    tcpSocketManager_->RecvMsg(recv);
}

void TcpScoketClient::OnSendMessage(QString& message)
{
    QByteArray str = message.toUtf8();
    str.append('\n');
    tcpSocket_->write(str);
}
}
