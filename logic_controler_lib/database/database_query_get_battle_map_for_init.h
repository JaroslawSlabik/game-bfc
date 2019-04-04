#ifndef DATABASE_QUERY_GET_BATTLE_MAP_FOR_INIT_H
#define DATABASE_QUERY_GET_BATTLE_MAP_FOR_INIT_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryGetBattleMapForInit  : public I_QueryTemplate
{
public:
    qlonglong m_id_player;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;
        QByteArray map_file;
        int map_element;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryGetBattleMapForInit();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_GET_BATTLE_MAP_FOR_INIT_H
