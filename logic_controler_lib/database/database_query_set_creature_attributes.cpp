#include "database_query_set_creature_attributes.h"

#include <QVariant>

void DatabaseQuerySetCreatureAttributes::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
}

DatabaseQuerySetCreatureAttributes::DatabaseQuerySetCreatureAttributes()
{

}

QString DatabaseQuerySetCreatureAttributes::prepareQuery()
{
    return QString("SELECT * FROM public.aktualizacja_potwora_wykonaj(%1, %2, %3, %4, %5);")
            .arg(m_id).arg(m_health).arg(m_shield).arg(m_attack).arg(m_move);
}

void DatabaseQuerySetCreatureAttributes::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQuerySetCreatureAttributes::DatabaseOut DatabaseQuerySetCreatureAttributes::getResult()
{
    return m_db_out;
}
