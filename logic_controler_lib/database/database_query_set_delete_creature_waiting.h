#ifndef DATABASE_QUERY_SET_DELETE_CREATURE_WAITING_H
#define DATABASE_QUERY_SET_DELETE_CREATURE_WAITING_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQuerySetDeleteCreatureWaiting : public I_QueryTemplate
{
public:
    qlonglong m_id_creature;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQuerySetDeleteCreatureWaiting();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_SET_DELETE_CREATURE_WAITING_H
