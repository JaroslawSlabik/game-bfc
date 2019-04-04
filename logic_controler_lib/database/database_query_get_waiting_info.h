#ifndef DATABASE_QUERY_GET_WAITING_INFO_H
#define DATABASE_QUERY_GET_WAITING_INFO_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryGetWaitingInfo  : public I_QueryTemplate
{
public:
    qlonglong m_id_player;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;
        qlonglong id_bitwy;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryGetWaitingInfo();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_GET_WAITING_INFO_H
