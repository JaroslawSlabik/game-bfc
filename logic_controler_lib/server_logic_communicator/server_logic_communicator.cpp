#include "server_logic_communicator.h"

ServerLogicCommunicator::ServerLogicCommunicator() :
    m_myThread(new QThread()),
    m_myWorker(new ServerLogicCommunicatorWorker)
{
    m_myWorker->moveToThread(m_myThread);
    m_myThread->start();

    /*CONNECTIONS*/
    //connect with server
    QObject::connect(this, &ServerLogicCommunicator::connectWithServer, m_myWorker, &ServerLogicCommunicatorWorker::connectWithServer, Qt::QueuedConnection);
    QObject::connect(m_myWorker, &ServerLogicCommunicatorWorker::connected, this, &ServerLogicCommunicator::connectedWithServer, Qt::QueuedConnection);
    //disconnect with server
    QObject::connect(this, &ServerLogicCommunicator::disconnectWithServer, m_myWorker, &ServerLogicCommunicatorWorker::disconnectWithServer, Qt::QueuedConnection);
    QObject::connect(m_myWorker, &ServerLogicCommunicatorWorker::disconnected, this, &ServerLogicCommunicator::disconnectedWithServer, Qt::QueuedConnection);
    //errors
    QObject::connect(m_myWorker, &ServerLogicCommunicatorWorker::communicationError, this, &ServerLogicCommunicator::errors, Qt::QueuedConnection);
    //comunication query
    QObject::connect(this, &ServerLogicCommunicator::communicationProcessStart, m_myWorker, &ServerLogicCommunicatorWorker::communicationProcessStart, Qt::QueuedConnection);
    QObject::connect(m_myWorker, &ServerLogicCommunicatorWorker::communicationProcessEnd, this, &ServerLogicCommunicator::communicationProcessEnd,  Qt::QueuedConnection);
}

ServerLogicCommunicator::~ServerLogicCommunicator()
{
    m_myThread->wait();
    m_myThread->terminate();

    delete m_myThread;
}

void ServerLogicCommunicator::connect(const QString& host, const quint16& port)
{
    emit connectWithServer(host, port);
}

void ServerLogicCommunicator::connectedWithServer()
{
    emit connected();
}

void ServerLogicCommunicator::disconnect()
{
    emit disconnectWithServer();
}

void ServerLogicCommunicator::disconnectedWithServer()
{
    emit disconnected();
}

void ServerLogicCommunicator::errors(const int& errorCode, const QString& error)
{
    emit communicationError(errorCode, error);
}

void ServerLogicCommunicator::sendQuery(const QString& query)
{
    QString args = query;

    emit communicationProcessStart(args);
}

void ServerLogicCommunicator::communicationProcessEnd(const QString& args)
{
    emit receiveResponse(args);
}
