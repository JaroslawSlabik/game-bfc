#ifndef DATABASE_QUERY_SET_INSERT_CREATURE_WAITING_H
#define DATABASE_QUERY_SET_INSERT_CREATURE_WAITING_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQuerySetInsertCreatureWaiting : public I_QueryTemplate
{
public:
    qlonglong m_id_creature;
    int m_pos_x;
    int m_pos_y;
    int m_id_element;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQuerySetInsertCreatureWaiting();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_SET_INSERT_CREATURE_WAITING_H
