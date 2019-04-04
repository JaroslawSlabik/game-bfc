#include <QCoreApplication>
#include <QtCore>

#include <stdlib.h>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("server_app");
    QCoreApplication::setApplicationVersion("1.0");


    bool debug = true;
    unsigned short port = 0;
    QString path_to_config_file = QDir::currentPath() + "\\" + QCoreApplication::applicationName() + ".ini";
    QFileInfo check_settings_file(path_to_config_file);
    if(false == check_settings_file.exists() || false == check_settings_file.isFile())
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);
        settings.beginGroup("DATABASE_CONNECTION_SETTINGS");
        settings.setValue("host_name", QVariant(""));
        settings.setValue("database_name", QVariant(""));
        settings.setValue("user_name", QVariant(""));
        settings.setValue("password", QVariant(""));
        settings.setValue("port", QVariant(0));
        settings.setValue("driver_name", QVariant(""));
        settings.endGroup();

        settings.beginGroup("SERVER_SETTINGS");
        settings.setValue("port", QVariant(0));
        settings.setValue("debug", QVariant(true));
        settings.endGroup();

        return 0;
    }
    else
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);
        settings.beginGroup("SERVER_SETTINGS");
        QVariant debug_v = settings.value("debug", QVariant());
        QVariant port_v = settings.value("port", QVariant());
        settings.endGroup();

        if(!debug_v.isValid() || debug_v.isNull() ||
           !port_v.isValid() || port_v.isNull() ||
           port_v.toUInt() == 0)
        {
            return 0;
        }

        debug = debug_v.toBool();
        port = static_cast<unsigned short>(port_v.toUInt());
    }

    Server server;
    if (!server.listen(QHostAddress::Any, port))
    {
        qDebug() << "Unable to start the server: " << server.errorString();
        return -1;
    }

    qDebug() << QString("The server is running and listen on IP: %1 and port: %2")
                         .arg(server.serverAddress().toIPv4Address()).arg(server.serverPort());

    return app.exec();
}
