#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QTcpSocket>
#include <QMutex>
#include <QTimer>

#include "../logic_controler_lib/logic/logic.h"

class ServerThread : public QObject
{
    Q_OBJECT

public:
    explicit ServerThread(int socketDescriptor, QMutex* mutex, QObject *parent);

public slots:
    void incomingData();
    void disconnected();
    void autoWorkLogic();

signals:
    void error(QTcpSocket::SocketError socketError);
    void sessionCanBeClose();

private:
    enum LogType
    {
        ERROR_LOG,
        DEBUG_LOG
    };

    int m_socketDescriptor;
    QTcpSocket* m_tcpSocket = nullptr;

    Logic* m_logic = nullptr;
    QMutex* m_mutex = nullptr;

    QString prepareMessageFromRequest();
    QByteArray prepareMessageToAnsver(QString message);

    bool logicSpace(QString request, QString&ansver, QString& error);

    void sessionCounter(int in);
    void loger(QString log, LogType type);

    QString m_thread_id = "";
    qint64 m_gracz_id = 0;
    QString getThreadId();
    bool send(QString message);
    QTimer* m_timer_auto_logic = nullptr;

    static int num;
};

#endif //SERVER_THREAD_H
