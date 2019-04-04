#ifndef DATABASE_QUERY_ATTACK_H
#define DATABASE_QUERY_ATTACK_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryAttack  : public I_QueryTemplate
{
public:
    qlonglong m_id_gracz_potwor;
    qlonglong m_id_wrog_potwor;
    int m_damage;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryAttack();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_ATTACK_H
