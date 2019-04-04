#include "database_query_get_battle_map_for_init.h"
#include <QVariant>

void DatabaseQueryGetBattleMapForInit::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
    map_file        = res.value("map_ret").toByteArray();
    map_element          = res.value("zywiol_ret").toInt();
}

DatabaseQueryGetBattleMapForInit::DatabaseQueryGetBattleMapForInit()
{

}

QString DatabaseQueryGetBattleMapForInit::prepareQuery()
{
    return QString("SELECT * FROM public.get_battle_map_for_init(%1);")
            .arg(m_id_player);
}

void DatabaseQueryGetBattleMapForInit::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryGetBattleMapForInit::DatabaseOut DatabaseQueryGetBattleMapForInit::getResult()
{
    return m_db_out;
}
