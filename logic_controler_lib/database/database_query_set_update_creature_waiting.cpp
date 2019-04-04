#include "database_query_set_update_creature_waiting.h"
#include <QVariant>

void DatabaseQuerySetUpdateCreatureWaiting::DatabaseOut::setResult(QSqlRecord res)
{
    Q_UNUSED(res);
    //was_ok          = res.value("was_ok_ret").toBool();
    //db_message      = res.value("message_ret").toString();
}

DatabaseQuerySetUpdateCreatureWaiting::DatabaseQuerySetUpdateCreatureWaiting()
{

}

QString DatabaseQuerySetUpdateCreatureWaiting::prepareQuery()
{
    return QString("NOT USE")
            .arg(m_id_player_waiting).arg(m_id_player);
}

void DatabaseQuerySetUpdateCreatureWaiting::setResult(QSqlQuery& result_query)
{
    Q_UNUSED(result_query);
    //result_query.first();
    //m_db_out.setResult(result_query.record());
}

DatabaseQuerySetUpdateCreatureWaiting::DatabaseOut DatabaseQuerySetUpdateCreatureWaiting::getResult()
{
    return m_db_out;
}
