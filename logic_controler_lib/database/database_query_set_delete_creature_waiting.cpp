#include "database_query_set_delete_creature_waiting.h"

#include <QVariant>

void DatabaseQuerySetDeleteCreatureWaiting::DatabaseOut::setResult(QSqlRecord res)
{
   Q_UNUSED(res);
   //was_ok          = res.value("was_ok_ret").toBool();
   //db_message      = res.value("message_ret").toString();
}

DatabaseQuerySetDeleteCreatureWaiting::DatabaseQuerySetDeleteCreatureWaiting()
{

}

QString DatabaseQuerySetDeleteCreatureWaiting::prepareQuery()
{
    return QString("SELECT * FROM public.delete_waiting_creature(%1);")
            .arg(m_id_creature);
}

void DatabaseQuerySetDeleteCreatureWaiting::setResult(QSqlQuery& result_query)
{
    Q_UNUSED(result_query);
    //result_query.first();
    //m_db_out.setResult(result_query.record());
}

DatabaseQuerySetDeleteCreatureWaiting::DatabaseOut DatabaseQuerySetDeleteCreatureWaiting::getResult()
{
    return m_db_out;
}
