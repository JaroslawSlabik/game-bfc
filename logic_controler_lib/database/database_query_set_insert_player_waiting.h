#ifndef DATABASE_QUERY_SET_INSERT_PLAYER_WAITING_H
#define DATABASE_QUERY_SET_INSERT_PLAYER_WAITING_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"
//TODO: zmiana nazwy na DatabaseQuerySetPlayerWaiting
class DatabaseQuerySetInsertPlayerWaiting : public I_QueryTemplate
{
public:
    qlonglong m_id_player;
    int m_id_game_mode;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQuerySetInsertPlayerWaiting();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_SET_INSERT_PLAYER_WAITING_H
