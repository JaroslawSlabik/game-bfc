#include "database_query_set_insert_player_waiting.h"
#include <QVariant>

void DatabaseQuerySetInsertPlayerWaiting::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok      = res.value("was_ok_ret").toBool();
    db_message  = res.value("message_ret").toString();
    status      = res.value("status_ret").toInt();
}

DatabaseQuerySetInsertPlayerWaiting::DatabaseQuerySetInsertPlayerWaiting()
{

}

QString DatabaseQuerySetInsertPlayerWaiting::prepareQuery()
{
    return QString("SELECT * FROM public.set_waiting_player(%1, %2);")
            .arg(m_id_player).arg(m_id_game_mode);
}

void DatabaseQuerySetInsertPlayerWaiting::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQuerySetInsertPlayerWaiting::DatabaseOut DatabaseQuerySetInsertPlayerWaiting::getResult()
{
    return m_db_out;
}
