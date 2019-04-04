#include "database_query_gracz_select.h"

#include <QVariant>

void DatabaseQueryGraczSelect::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    id_gracza       = res.value("id_gracza_ret").toLongLong();
}

DatabaseQueryGraczSelect::DatabaseQueryGraczSelect()
{

}

QString DatabaseQueryGraczSelect::prepareQuery()
{
    return QString("SELECT * FROM public.logowanie_gracza_wykonaj('%1','%2');")
            .arg(m_login).arg(m_password);
}

void DatabaseQueryGraczSelect::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryGraczSelect::DatabaseOut DatabaseQueryGraczSelect::getResult()
{
    return m_db_out;
}
