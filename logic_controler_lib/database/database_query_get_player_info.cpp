#include "database_query_get_player_info.h"

#include <QVariant>

void DatabaseQueryGetPlayerInfo::DatabaseOut::setResult(QSqlRecord res)
{
    level                   = res.value("poziom_ret").toUInt();
    exp                     = res.value("doswiadczenie_ret").toLongLong();
    exp_next_level          = res.value("doswiadczenie_nastepny_poziom_ret").toLongLong();
    imie                    = res.value("imie_ret").toString();
    points_to_distribute    = res.value("punkty_do_rozdania_ret").toUInt();
}

DatabaseQueryGetPlayerInfo::DatabaseQueryGetPlayerInfo()
{

}

QString DatabaseQueryGetPlayerInfo::prepareQuery()
{
    return QString("SELECT * FROM public.pobierz_dane_gracza(%1);")
            .arg(m_id_gracza);
}

void DatabaseQueryGetPlayerInfo::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryGetPlayerInfo::DatabaseOut DatabaseQueryGetPlayerInfo::getResult()
{
    return m_db_out;
}
