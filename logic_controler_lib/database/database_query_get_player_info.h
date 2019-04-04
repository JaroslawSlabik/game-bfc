#ifndef DATABASE_QUERY_GET_PLAYER_INFO_H
#define DATABASE_QUERY_GET_PLAYER_INFO_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryGetPlayerInfo  : public I_QueryTemplate
{
public:
    qlonglong m_id_gracza;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        QString imie;
        unsigned int level;
        qlonglong exp;
        qlonglong exp_next_level;
        unsigned int points_to_distribute;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryGetPlayerInfo();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_GET_PLAYER_INFO_H
