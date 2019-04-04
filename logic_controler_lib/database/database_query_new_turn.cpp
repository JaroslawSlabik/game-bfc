#include "database_query_new_turn.h"
#include <QVariant>

void DatabaseQueryNewTurn::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
}

DatabaseQueryNewTurn::DatabaseQueryNewTurn()
{

}

QString DatabaseQueryNewTurn::prepareQuery()
{
    return QString("SELECT * FROM public.new_turn(%1);")
            .arg(m_id_player);
}

void DatabaseQueryNewTurn::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryNewTurn::DatabaseOut DatabaseQueryNewTurn::getResult()
{
    return m_db_out;
}
