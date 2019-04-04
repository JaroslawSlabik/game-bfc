#include "server_logic_communicator_worker.h"

#include <QDataStream>
#include <QtNetwork>

ServerLogicCommunicatorWorker::ServerLogicCommunicatorWorker()
{
    m_connected = false;
}

void ServerLogicCommunicatorWorker::communicationProcessStart(const QString& args)
{
    if(!m_connected)
        return;

    bool was_ok = false;
    if(m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        m_tcpSocket->write(prepareMessageToRequest(args));
        was_ok = m_tcpSocket->waitForBytesWritten();
    }
}

void ServerLogicCommunicatorWorker::connectWithServer(const QString& host, const quint16& port)
{
    if(m_connected)
        return;

    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QIODevice::readyRead, this, &ServerLogicCommunicatorWorker::readAnswer);
    connect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ServerLogicCommunicatorWorker::socketErrors);

    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);

    m_tcpSocket->waitForConnected();

    if(m_tcpSocket->isOpen())
    {
        m_connected = true;
        emit connected();
    }
    else
    {
        m_connected = false;
        disconnect(m_tcpSocket, &QIODevice::readyRead, this, &ServerLogicCommunicatorWorker::readAnswer);
        disconnect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ServerLogicCommunicatorWorker::socketErrors);
        delete m_tcpSocket;
    }
}

void ServerLogicCommunicatorWorker::disconnectWithServer()
{
    if(!m_connected)
        return;

    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->waitForDisconnected();

    if(m_tcpSocket->isOpen())
    {
        m_connected = true;
    }
    else
    {
        m_connected = false;
        disconnect(m_tcpSocket, &QIODevice::readyRead, this, &ServerLogicCommunicatorWorker::readAnswer);
        disconnect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ServerLogicCommunicatorWorker::socketErrors);
        delete m_tcpSocket;

        emit disconnected();
    }
}

void ServerLogicCommunicatorWorker::readAnswer()
{
    QString ansver = prepareMessageFromAnsver();

    emit communicationProcessEnd(ansver);
}

void ServerLogicCommunicatorWorker::socketErrors(QAbstractSocket::SocketError socketErrorCode)
{
    QString error = "";

    switch (socketErrorCode)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
           error = "The host was not found. Please check the host name and port settings.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            error = "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
            break;
        default:
            error = QString("The following error occurred: %1.")
                    .arg(m_tcpSocket->errorString());
    }

    emit communicationError(socketErrorCode, error);
}

QByteArray ServerLogicCommunicatorWorker::prepareMessageToRequest(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << message;
    return block;
}

QString ServerLogicCommunicatorWorker::prepareMessageFromAnsver()  // work only Qt 5.7 <
{
    QString message;
    QDataStream in;
    in.setDevice(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    in.startTransaction();
    in >> message;
    if (!in.commitTransaction())
        return "";

    return message;
}
