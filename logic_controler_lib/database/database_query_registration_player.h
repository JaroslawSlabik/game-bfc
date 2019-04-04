#ifndef DATABASE_QUERY_REGISTRATION_PLAYER_H
#define DATABASE_QUERY_REGISTRATION_PLAYER_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryRegistrationPlayer  : public I_QueryTemplate
{
public:
    QString m_name;
    QString m_surname;
    QString m_email;
    QString m_password;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryRegistrationPlayer();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_REGISTRATION_PLAYER_H
