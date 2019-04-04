#include "database_query_get_player_creatures.h"
#include <QVariant>

QList<DatabaseQueryGetPlayerCreatures::DatabaseOut> DatabaseQueryGetPlayerCreatures::m_db_out;

void DatabaseQueryGetPlayerCreatures::DatabaseOut::setResult(QSqlRecord res)
{
    id_potwora_gracza = res.value("id_potwor_gracza_ret").toLongLong();
    nazwa = res.value("nazwa_ret").toString();
    opis = res.value("opis_ret").toString();
    tekstura = res.value("tekstura_ret").toByteArray();
    zdrowie = res.value("zdrowie_ret").toInt();
    ochrona = res.value("ochrona_ret").toInt();
    atak = res.value("atak_ret").toInt();
    punkty_ruchu = res.value("punkty_ruchu_ret").toInt();
}

DatabaseQueryGetPlayerCreatures::DatabaseQueryGetPlayerCreatures()
{

}

QString DatabaseQueryGetPlayerCreatures::prepareQuery()
{
    return QString("SELECT * FROM public.pobierz_liste_potworow(%1,%2, 1);")
            .arg(m_id_gracza).arg(m_lp);
}

void DatabaseQueryGetPlayerCreatures::setResult(QSqlQuery& result_query)
{
    m_db_out.clear();

    while(result_query.next())
    {
        DatabaseQueryGetPlayerCreatures::DatabaseOut out;
        out.setResult(result_query.record());
        m_db_out.push_back(out);
    }
}

QList<DatabaseQueryGetPlayerCreatures::DatabaseOut> DatabaseQueryGetPlayerCreatures::getResult()
{
    return m_db_out;
}
