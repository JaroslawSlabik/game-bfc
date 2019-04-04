#include "database_query_set_insert_creature_waiting.h"

#include <QVariant>

void DatabaseQuerySetInsertCreatureWaiting::DatabaseOut::setResult(QSqlRecord res)
{
    Q_UNUSED(res);
    //was_ok          = res.value("was_ok_ret").toBool();
    //db_message      = res.value("message_ret").toString();
}

DatabaseQuerySetInsertCreatureWaiting::DatabaseQuerySetInsertCreatureWaiting()
{

}

QString DatabaseQuerySetInsertCreatureWaiting::prepareQuery()
{
    return QString("SELECT * FROM public.set_waiting_creature(%1, %2, %3, %4);")
            .arg(m_id_creature).arg(m_id_element).arg(m_pos_x).arg(m_pos_y);
}

void DatabaseQuerySetInsertCreatureWaiting::setResult(QSqlQuery& result_query)
{
    Q_UNUSED(result_query);
    //result_query.first();
    //m_db_out.setResult(result_query.record());
}

DatabaseQuerySetInsertCreatureWaiting::DatabaseOut DatabaseQuerySetInsertCreatureWaiting::getResult()
{
    return m_db_out;
}
