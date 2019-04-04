#include "database_query_get_battle_pawn_for_init.h"
#include <QVariant>

QList<DatabaseQueryGetBattlePawnForInit::DatabaseOut> DatabaseQueryGetBattlePawnForInit::m_db_out;

void DatabaseQueryGetBattlePawnForInit::DatabaseOut::setResult(QSqlRecord res)
{
    id_boahtera_gracza  = res.value("id_boahtera_gracza_ret").toInt();
    nazwa               = res.value("nazwa_ret").toString();
    opis                = res.value("opis_ret").toString();
    tekstura            = res.value("tekstura_ret").toByteArray();
    zdrowie             = res.value("zdrowie_ret").toInt();
    ochrona             = res.value("ochrona_ret").toInt();
    atak                = res.value("atak_ret").toInt();
    punkty_ruchu        = res.value("punkty_ruchu_ret").toInt();
    pozycja_x           = res.value("pozycja_x_ret").toInt();
    pozycja_y           = res.value("pozycja_y_ret").toInt();
    zywiol              = res.value("zywiol_ret").toInt();
    wrog                = res.value("wrog_ret").toBool();
}

DatabaseQueryGetBattlePawnForInit::DatabaseQueryGetBattlePawnForInit()
{

}

QString DatabaseQueryGetBattlePawnForInit::prepareQuery()
{
    return QString("SELECT * FROM public.get_battle_pawn_for_init(%1);")
            .arg(m_id_player);
}

void DatabaseQueryGetBattlePawnForInit::setResult(QSqlQuery& result_query)
{
    m_db_out.clear();

    while(result_query.next())
    {
        DatabaseQueryGetBattlePawnForInit::DatabaseOut out;
        out.setResult(result_query.record());
        m_db_out.push_back(out);
    }
}

QList<DatabaseQueryGetBattlePawnForInit::DatabaseOut> DatabaseQueryGetBattlePawnForInit::getResult()
{
    return m_db_out;
}
