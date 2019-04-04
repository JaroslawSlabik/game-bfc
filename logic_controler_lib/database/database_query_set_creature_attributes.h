#ifndef DATABASE_QUERY_SET_CREATURE_ATTRIBUTES_H
#define DATABASE_QUERY_SET_CREATURE_ATTRIBUTES_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"


class DatabaseQuerySetCreatureAttributes : public I_QueryTemplate
{
public:
    qlonglong m_id;
    int m_health;
    int m_shield;
    int m_attack;
    int m_move;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQuerySetCreatureAttributes();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_SET_CREATURE_ATTRIBUTES_H
