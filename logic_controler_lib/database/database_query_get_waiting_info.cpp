#include "database_query_get_waiting_info.h"

#include <QVariant>

void DatabaseQueryGetWaitingInfo::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
    id_bitwy        = res.value("id_bitwy_ret").toLongLong();
}

DatabaseQueryGetWaitingInfo::DatabaseQueryGetWaitingInfo()
{

}

QString DatabaseQueryGetWaitingInfo::prepareQuery()
{
    return QString("SELECT * FROM public.get_waiting_info(%1);")
            .arg(m_id_player);
}

void DatabaseQueryGetWaitingInfo::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryGetWaitingInfo::DatabaseOut DatabaseQueryGetWaitingInfo::getResult()
{
    return m_db_out;
}
