#ifndef SERVER_LOGIC_COMMUNICATOR_WORKER_H
#define SERVER_LOGIC_COMMUNICATOR_WORKER_H
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

class ServerLogicCommunicatorWorker : public QObject
{
    Q_OBJECT

public:
    ServerLogicCommunicatorWorker();

public slots:
    void communicationProcessStart(const QString& args);
    void connectWithServer(const QString& host, const quint16& port);
    void disconnectWithServer();

private slots:
    void socketErrors(QAbstractSocket::SocketError socketError);
    void readAnswer();

signals:
    void communicationProcessEnd(const QString& args);
    void communicationError(const int& errorCode, const QString& error);
    void connected();
    void disconnected();

private:
    QTcpSocket *m_tcpSocket = nullptr;
    volatile bool m_connected;

    QByteArray prepareMessageToRequest(QString message);
    QString prepareMessageFromAnsver();
};

#endif // SERVER_LOGIC_COMMUNICATOR_WORKER_H


/*
#include <QtCore>
struct Worker : QObject {
  Q_SLOT void aSlot() {
    qDebug() << QThread::currentThread();
    QThread::currentThread()->quit();
  }
  Q_SIGNAL void aSignal();
  Q_OBJECT
};

int main(int argc, char ** argv) {
  QCoreApplication app{argc, argv};
  QThread::currentThread()->setObjectName("main");
  QThread thread;
  thread.setObjectName("thread");
  Worker a, b;
  b.moveToThread(&thread);
  thread.start();
  QObject::connect(&a, &Worker::aSignal, &b, &Worker::aSlot);
  emit a.aSignal(); // the signal is emitted from the main thread
  thread.wait();
}

*/
