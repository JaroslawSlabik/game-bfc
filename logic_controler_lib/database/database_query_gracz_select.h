#ifndef DATABASE_QUERY_GRACZ_SELECT_H
#define DATABASE_QUERY_GRACZ_SELECT_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"


class DatabaseQueryGraczSelect : public I_QueryTemplate
{
public:
    QString m_login;
    QString m_password;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        QString db_message;
        qlonglong id_gracza;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryGraczSelect();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_GRACZ_SELECT_H
