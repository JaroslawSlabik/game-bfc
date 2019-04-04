#include "server.h"

#include <stdlib.h>
#include <QThread>

#include "server_thread.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    ServerThread *worker = new ServerThread(socketDescriptor, &mutex, this);
    QThread *thread = new QThread(this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    /*TODO: przetestować*/connect(worker, &ServerThread::sessionCanBeClose, thread, &QThread::quit);
    worker->moveToThread(thread);
    thread->start();
}
