#include "database_query_set_abort_waiting.h"

#include <QVariant>

void DatabaseQuerySetAbortWaiting::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
}

DatabaseQuerySetAbortWaiting::DatabaseQuerySetAbortWaiting()
{

}

QString DatabaseQuerySetAbortWaiting::prepareQuery()
{
    return QString("SELECT * FROM public.abort_waiting(%1);")
            .arg(m_id_player);
}

void DatabaseQuerySetAbortWaiting::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQuerySetAbortWaiting::DatabaseOut DatabaseQuerySetAbortWaiting::getResult()
{
    return m_db_out;
}
