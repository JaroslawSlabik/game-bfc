#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

#include "i_query_template.h"

class Database
{
private:
    Database();
    static Database* s_db;
    static QSqlDatabase s_database;
    QString m_error;

    static bool s_settings_is_read;
    static void loadDatabaseConfigFromFile(QString filePath);

    static QString s_host_anme;
    static QString s_database_anme;
    static QString s_user_name;
    static QString s_password;
    static int s_port;
    static QString s_driver_name;

public:
    static Database* getInstance(const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));
    static bool deleteInstance(const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));
    bool execQuery(I_QueryTemplate* query);

    QString getLastError();
};

#endif // DATABASE_H
