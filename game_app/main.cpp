#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include "../logic_controler_lib/server_logic_communicator/server_logic_communicator.h"
#ifndef QT_NO_OPENGL
#include "main_window.h"
#include "gui_frame/gui_frame_manager.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("game_app");
    QApplication::setApplicationVersion("1.0");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QString host = "";
    unsigned short port = 0;
    QString path_to_config_file = QDir::currentPath() + "\\" + QCoreApplication::applicationName() + ".ini";
    QFileInfo check_settings_file(path_to_config_file);
    if(false == check_settings_file.exists() || false == check_settings_file.isFile())
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);

        settings.beginGroup("SERVER_SETTINGS");
        settings.setValue("host", QVariant());
        settings.setValue("port", QVariant(0));
        settings.endGroup();

        return 0;
    }
    else
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);
        settings.beginGroup("SERVER_SETTINGS");
        QVariant host_v = settings.value("host", QVariant());
        QVariant port_v = settings.value("port", QVariant());
        settings.endGroup();

        if(!host_v.isValid() || host_v.isNull() ||
           !port_v.isValid() || port_v.isNull() ||
           port_v.toUInt() == 0 || host_v.toString().isEmpty())
        {
            return 0;
        }

        host = host_v.toString();
        port = static_cast<unsigned short>(port_v.toUInt());
    }

#ifndef QT_NO_OPENGL
    ServerLogicCommunicator comunicator;

    GUIFrameManager manager(GUIFrameManager::Frame::loginFrame);

    //CONNECTS
    QObject::connect(&manager, &GUIFrameManager::sendToServer, &comunicator, &ServerLogicCommunicator::sendQuery);
    QObject::connect(&comunicator, &ServerLogicCommunicator::receiveResponse, &manager, &GUIFrameManager::receiveFromServer);
    QObject::connect(&comunicator, &ServerLogicCommunicator::connected, &manager, &GUIFrameManager::serverConnected);
    QObject::connect(&comunicator, &ServerLogicCommunicator::disconnected, &manager, &GUIFrameManager::serverDisconnected);

    comunicator.connect(host, port);
    manager.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
