#ifndef DATABASE_QUERY_SET_UPDATE_CREATURE_WAITING_H
#define DATABASE_QUERY_SET_UPDATE_CREATURE_WAITING_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"
//TODO: delete this class
class DatabaseQuerySetUpdateCreatureWaiting : public I_QueryTemplate
{
public:
    qlonglong m_id_player_waiting;
    qlonglong m_id_player;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQuerySetUpdateCreatureWaiting();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_SET_UPDATE_CREATURE_WAITING_H
