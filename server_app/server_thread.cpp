#include "server_thread.h"

#include <QDebug>
#include <QtNetwork>

#include "../logic_controler_lib/database/database.h"

#include "../logic_controler_lib/logic/logout_logic.h"

int ServerThread::num;

ServerThread::ServerThread(int socketDescriptor, QMutex* mutex, QObject *parent)
    : m_socketDescriptor(socketDescriptor),
      m_mutex(mutex)
{
    m_tcpSocket = new QTcpSocket();
    m_logic = new Logic();
    m_timer_auto_logic = new QTimer();

    if (!m_tcpSocket->setSocketDescriptor(m_socketDescriptor))
    {
        loger(QString("Error QTcpSocket: %1").arg(m_tcpSocket->error()).arg(m_thread_id), LogType::ERROR_LOG);
        return;
    }

    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ServerThread::incomingData);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &ServerThread::disconnected);
    connect(m_timer_auto_logic, &QTimer::timeout, this, &ServerThread::autoWorkLogic);

    sessionCounter(+1);
}

void ServerThread::incomingData()
{
    //DATA IN
    QString message = prepareMessageFromRequest();

    if(m_thread_id.isEmpty())
    {
        m_thread_id = getThreadId();
        loger(QString("New connection from thread: %1, all connections: %2").arg(m_thread_id).arg(num), LogType::DEBUG_LOG);
    }
    loger(QString("Receive: %1 from thread: %2").arg(message).arg(m_thread_id), LogType::DEBUG_LOG);


    Database::getInstance(m_thread_id);

    QString ansver = "";
    QString error = "";
    bool was_ok= false;

    was_ok = m_logic->setArguments(message);
    if(was_ok)
        was_ok = m_logic->work(getThreadId());

    if(!was_ok)
        error = m_logic->getLastError();

    ansver = m_logic->getResult();

    if(!was_ok)
    {
        loger(QString("Error: %1 from thread: %2").arg(error).arg(m_thread_id), LogType::ERROR_LOG);
    }
    else
    {
        loger(QString("Ansver: %1 from thread: %2").arg(ansver).arg(m_thread_id), LogType::DEBUG_LOG);
    }

    //DATA OUT
    send(ansver);
}

void ServerThread::disconnected()
{
    loger(QString("disconnect from thread: %1").arg(m_thread_id), LogType::DEBUG_LOG);

    QString ansver = "";
    QString error = "";
    bool was_ok = logicSpace(LogOutLogic::getLogicName(), ansver, error);
    if(!was_ok || ansver.isEmpty())
    {
        loger(QString("Error: %1 from thread: %2").arg(error).arg(m_thread_id), LogType::ERROR_LOG);
    }
    else
    {
        loger(QString("Ansver: %1 from thread: %2").arg(ansver).arg(m_thread_id), LogType::DEBUG_LOG);
    }

    Database::deleteInstance(m_thread_id);

    sessionCounter(-1);
    m_tcpSocket->deleteLater();
    QThread::usleep(500);
    emit sessionCanBeClose();
}

QByteArray ServerThread::prepareMessageToAnsver(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << message;
    return block;
}

QString ServerThread::prepareMessageFromRequest()
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

bool ServerThread::logicSpace(QString request, QString& ansver, QString& error)
{
    bool was_ok = false;

    was_ok = m_logic->setArguments(request);

    if(was_ok)
        was_ok = m_logic->work(getThreadId());

    if(!was_ok)
        error = m_logic->getLastError();

    ansver = m_logic->getResult();

    return was_ok;
}

void ServerThread::sessionCounter(int in)
{
    m_mutex->lock();
    num = num + in;
    m_mutex->unlock();
}

void ServerThread::loger(QString log, LogType type)
{
    bool debug_is_running = true;//DOTO: pobierać z bazy
    QString file_name = QDir::currentPath() + "/";
    switch(type)
    {
        case LogType::DEBUG_LOG:
        if(debug_is_running == false)
            return;
        file_name += "debug_log-"; break;
        case LogType::ERROR_LOG: file_name += "error_log-"; break;
    }
    file_name += QDate::currentDate().toString("yyyy-MM-dd") + ".txt";

    if(debug_is_running)
        qDebug() << "LOG(" << QDate::currentDate() << "): " << log;

    m_mutex->lock();
    QFile file(file_name);
    if(file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << log << endl;
        file.close();
    }
    m_mutex->unlock();
}

QString ServerThread::getThreadId()
{
    QString id = QString("0x%1").arg(reinterpret_cast<int>(QThread::currentThread()), 16);
    id.replace(" ", "");
    return id;
}

bool ServerThread::send(QString message)
{
    if(message.isEmpty())
        return false;

    m_tcpSocket->write(prepareMessageToAnsver(message));
    m_tcpSocket->waitForBytesWritten();

    return true;
}

void ServerThread::autoWorkLogic()
{

}
