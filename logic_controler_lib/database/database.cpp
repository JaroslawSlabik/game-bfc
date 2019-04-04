#include "database.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>

Database* Database::s_db = nullptr;
QSqlDatabase Database::s_database;

bool Database::s_settings_is_read;
QString Database::s_host_anme;
QString Database::s_database_anme;
QString Database::s_user_name;
QString Database::s_password;
int Database::s_port;
QString Database::s_driver_name;


Database::Database()
{

}

Database* Database::getInstance(const QString &connectionName)
{
    if(s_db == nullptr)
        s_db = new Database();

    if(!s_settings_is_read)
        loadDatabaseConfigFromFile(QDir::currentPath() + "/" + QCoreApplication::applicationName() + ".ini");

    if(!s_settings_is_read)
        return s_db;

    if(!QSqlDatabase::contains(connectionName))
    {
        s_database = QSqlDatabase::addDatabase(s_driver_name, connectionName);
        s_database.setHostName(s_host_anme);
        s_database.setDatabaseName(s_database_anme);
        s_database.setUserName(s_user_name);
        s_database.setPassword(s_password);
        s_database.setPort(s_port);
        if(!s_database.open())
            qDebug() << "DB ERROR: " << s_database.lastError().text();
    }
    else
    {
        s_database = QSqlDatabase::database(connectionName);
    }

    return s_db;
}

bool Database::deleteInstance(const QString &connectionName)
{
    if(!QSqlDatabase::contains(connectionName))
        return false;

    s_database = QSqlDatabase::database(connectionName);
    if(!s_database.isValid())
        return false;

    if(s_database.isOpen())
        s_database.close();

    QSqlDatabase::removeDatabase(connectionName);

    return true;
}

bool Database::execQuery(I_QueryTemplate* query)
{
    if(!s_settings_is_read)
    {
        m_error = "Database settings connection is not load.";
        return false;
    }

    if(!s_database.isValid())
    {
        m_error = "Database is not valid";
        return false;
    }

    if(!s_database.isOpen())
    {
        m_error = "Database "+ s_database.connectionName() +" is not open";
        return false;
    }

    QSqlQuery query_worker(s_database);
    qDebug() << "QUERY: " + query->prepareQuery();
    if(!query_worker.exec(query->prepareQuery()))
    {
        m_error = "QUERY: " + query->prepareQuery() + " ERROR: " + query_worker.lastError().text();
        return false;
    }

    if(!query_worker.isActive())
    {
        m_error = "query_worker is not active";
        return false;
    }

    query->setResult(query_worker);

    return true;
}

QString Database::getLastError()
{
    return m_error;
}

void Database::loadDatabaseConfigFromFile(QString filePath)
{
    if(s_settings_is_read == true)
        return;

    if(!QFile::exists(filePath))
    {
        QSettings settings(filePath, QSettings::IniFormat);
        settings.beginGroup("DATABASE_CONNECTION_SETTINGS");
        settings.setValue("host_name", QVariant(""));
        settings.setValue("database_name", QVariant(""));
        settings.setValue("user_name", QVariant(""));
        settings.setValue("password", QVariant(""));
        settings.setValue("port", QVariant(0));
        settings.setValue("driver_name", QVariant(""));
        settings.endGroup();
        settings.sync();

        s_settings_is_read = false;
        return;
    }

    bool is_read = true;

    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("DATABASE_CONNECTION_SETTINGS");

    QVariant host_name_v = settings.value("host_name", QVariant());
    if(!host_name_v.isValid() || host_name_v.isNull())
        is_read = false;
    s_host_anme = host_name_v.toString();

    QVariant database_name_v = settings.value("database_name", QVariant());
    if(!database_name_v.isValid() || database_name_v.isNull())
        is_read = false;
    s_database_anme = database_name_v.toString();

    QVariant user_name_v = settings.value("user_name", QVariant());
    if(!user_name_v.isValid() || user_name_v.isNull())
        is_read = false;
    s_user_name = user_name_v.toString();

    QVariant password_v = settings.value("password", QVariant());
    if(!password_v.isValid() || password_v.isNull())
        is_read = false;
    s_password = password_v.toString();

    QVariant port_v = settings.value("port", QVariant());
    if(!port_v.isValid() || port_v.isNull())
        is_read = false;
    s_port = port_v.toInt();

    QVariant driver_name_v = settings.value("driver_name", QVariant());
    if(!driver_name_v.isValid() || driver_name_v.isNull())
        is_read = false;
    s_driver_name = driver_name_v.toString();


    settings.endGroup();

    if(is_read)
        s_settings_is_read = true;
}
