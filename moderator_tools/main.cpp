#include <QCoreApplication>
#include <QCommandLineParser>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSettings>
#include <QDir>
#include "i_tool.h"
#include "create_battle_map.h"
#include "create_creature.h"
#include "texture_to_base64.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("moderator_tools");
    QCoreApplication::setApplicationVersion("1.0");

    QMap<QString, QString> map_options;
    QString path_to_config_file = QDir::currentPath() + "\\" + QCoreApplication::applicationName() + ".ini";
    QFileInfo check_settings_file(path_to_config_file);
    if(false == check_settings_file.exists() || false == check_settings_file.isFile())
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);

        settings.beginGroup("DATABASE_CONFIG");
        settings.setValue("host_name", QVariant());
        settings.setValue("database_name", QVariant());
        settings.setValue("user_name", QVariant());
        settings.setValue("password", QVariant());
        settings.setValue("driver", QVariant());
        settings.endGroup();
        settings.beginGroup("OPTIONS");
        settings.setValue("tool_name", QVariant());
        settings.setValue("id_element", QVariant());
        settings.setValue("texture", QVariant());
        settings.setValue("name", QVariant());
        settings.setValue("description", QVariant());
        settings.setValue("map", QVariant());
        settings.setValue("creature_health", QVariant());
        settings.setValue("creature_shield", QVariant());
        settings.setValue("creature_attack", QVariant());
        settings.setValue("creature_point_move", QVariant());
        settings.setValue("creature_method_move", QVariant());
        settings.endGroup();

        return 0;
    }
    else
    {
        QSettings settings(path_to_config_file, QSettings::Format::IniFormat);
        settings.beginGroup("DATABASE_CONFIG");
        map_options.insert("host_name", settings.value("host_name").toString());
        map_options.insert("database_name", settings.value("database_name").toString());
        map_options.insert("user_name", settings.value("user_name").toString());
        map_options.insert("password", settings.value("password").toString());
        map_options.insert("driver", settings.value("driver").toString());
        settings.endGroup();

        settings.beginGroup("OPTIONS");
        map_options.insert("t", settings.value("tool_name").toString());
        map_options.insert("e", settings.value("id_element").toString());
        map_options.insert("x", settings.value("texture").toString());
        map_options.insert("n", settings.value("name").toString());
        map_options.insert("d", settings.value("description").toString());
        map_options.insert("m", settings.value("map").toString());
        map_options.insert("h", settings.value("creature_health").toString());
        map_options.insert("s", settings.value("creature_shield").toString());
        map_options.insert("a", settings.value("creature_attack").toString());
        map_options.insert("p", settings.value("creature_point_move").toString());
        map_options.insert("v", settings.value("creature_method_move").toString());
        settings.endGroup();
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(map_options.value("driver"));
    db.setHostName(map_options.value("host_name"));
    db.setDatabaseName(map_options.value("database_name"));
    db.setUserName(map_options.value("user_name"));
    db.setPassword(map_options.value("password"));
    bool was_ok = db.open();
    if(false == was_ok)
    {
        qDebug() << "Error connecting to database: " + db.lastError().text();
        return 0;
    }

    QMap<QString, ITool*> map_tools;
    map_tools.insert(QString("new-map"), new CreateBattleMap());
    map_tools.insert(QString("new-creature"), new CreateCreature());
    map_tools.insert(QString("texture"), new TextureToBase64());

    QString error_message = "";
    ITool* tool = map_tools.value(map_options.value("t"), nullptr);
    if(nullptr == tool)
    {
        qDebug() << "Not choice tool.";
        return 0;
    }

    was_ok = tool->setOptionFromComandLine(map_options, error_message);
    if(false == was_ok)
    {
        qDebug() << "Error during set option from comand line: " + error_message;
        return 0;
    }

    was_ok = tool->work(error_message);
    if(false == was_ok)
    {
        qDebug() << "Error during work: " + error_message;
        return 0;
    }

    return a.exec();
}
