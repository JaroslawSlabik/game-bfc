#include "database_query_get_info_about_enemy_pawn.h"
#include <QVariant>

QList<DatabaseQueryGetInfoAboutEnemyPawn::DatabaseOut> DatabaseQueryGetInfoAboutEnemyPawn::m_db_out;

void DatabaseQueryGetInfoAboutEnemyPawn::DatabaseOut::setResult(QSqlRecord res)
{
    id_boahtera_gracza  = res.value("id_boahtera_gracza_ret").toInt();
    zdrowie             = res.value("zdrowie_ret").toInt();
    ochrona             = res.value("ochrona_ret").toInt();
    punkty_ruchu        = res.value("punkty_ruchu_ret").toInt();
    pozycja_x           = res.value("pozycja_x_ret").toInt();
    pozycja_y           = res.value("pozycja_y_ret").toInt();
}

DatabaseQueryGetInfoAboutEnemyPawn::DatabaseQueryGetInfoAboutEnemyPawn()
{

}

QString DatabaseQueryGetInfoAboutEnemyPawn::prepareQuery()
{
    return QString("SELECT * FROM public.get_info_about_enemy_pawn(%1);")
            .arg(m_id_player);
}

void DatabaseQueryGetInfoAboutEnemyPawn::setResult(QSqlQuery& result_query)
{
    m_db_out.clear();

    while(result_query.next())
    {
        DatabaseQueryGetInfoAboutEnemyPawn::DatabaseOut out;
        out.setResult(result_query.record());
        m_db_out.push_back(out);
    }
}

QList<DatabaseQueryGetInfoAboutEnemyPawn::DatabaseOut> DatabaseQueryGetInfoAboutEnemyPawn::getResult()
{
    return m_db_out;
}
