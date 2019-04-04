#ifndef SERVER_LOGIC_COMMUNICATOR_H
#define SERVER_LOGIC_COMMUNICATOR_H
#include <QObject>
#include <QThread>
#include <QString>

#include "server_logic_communicator_worker.h"

class ServerLogicCommunicator : public QObject
{
    Q_OBJECT

public:
    ServerLogicCommunicator();
    ~ServerLogicCommunicator();

public slots:
    void sendQuery(const QString& query);
    void connect(const QString& host, const quint16& port);
    void disconnect();

signals:
    void receiveResponse(const QString& resonse);
    void connected();
    void disconnected();
    void communicationError(const int& errorCode, const QString& error);

private slots:
    void communicationProcessEnd(const QString& args);
    void connectedWithServer();
    void disconnectedWithServer();
    void errors(const int& errorCode, const QString& error);

signals: /*prywatne, nie używać po za klasą*/
    void communicationProcessStart(const QString& args);
    void connectWithServer(const QString& host, const quint16& port);
    void disconnectWithServer();

private:
    QThread* m_myThread;
    ServerLogicCommunicatorWorker* m_myWorker;
};

#endif // SERVER_LOGIC_COMMUNICATOR_H
