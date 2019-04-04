#include "database_query_attack.h"
#include <QVariant>

void DatabaseQueryAttack::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
}

DatabaseQueryAttack::DatabaseQueryAttack()
{

}

QString DatabaseQueryAttack::prepareQuery()
{
    return QString("SELECT * FROM public.attack(%1, %2, %3);")
            .arg(m_id_gracz_potwor).arg(m_id_wrog_potwor).arg(m_damage);
}

void DatabaseQueryAttack::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryAttack::DatabaseOut DatabaseQueryAttack::getResult()
{
    return m_db_out;
}
