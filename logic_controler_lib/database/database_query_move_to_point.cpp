#include "database_query_move_to_point.h"
#include <QVariant>

void DatabaseQueryMoveToPoint::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
}

DatabaseQueryMoveToPoint::DatabaseQueryMoveToPoint()
{

}

QString DatabaseQueryMoveToPoint::prepareQuery()
{
    return QString("SELECT * FROM public.move_to_point(%1, %2, %3);")
            .arg(m_id_creature_player).arg(m_pozycja_x).arg(m_pozycja_y);
}

void DatabaseQueryMoveToPoint::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryMoveToPoint::DatabaseOut DatabaseQueryMoveToPoint::getResult()
{
    return m_db_out;
}
