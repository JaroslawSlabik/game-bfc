#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QMutex>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QMutex mutex;
};

#endif //SERVER_H
