#include "database_query_registration_player.h"
#include <QVariant>

void DatabaseQueryRegistrationPlayer::DatabaseOut::setResult(QSqlRecord res)
{
    was_ok          = res.value("was_ok_ret").toBool();
    db_message      = res.value("message_ret").toString();
    status          = res.value("status_ret").toInt();
}

DatabaseQueryRegistrationPlayer::DatabaseQueryRegistrationPlayer()
{

}

QString DatabaseQueryRegistrationPlayer::prepareQuery()
{
    return QString("SELECT * FROM public.registration_player('%1', '%2', '%3', '%4');")
            .arg(m_name)
            .arg(m_surname)
            .arg(m_email)
            .arg(m_password);
}

void DatabaseQueryRegistrationPlayer::setResult(QSqlQuery& result_query)
{
    result_query.first();
    m_db_out.setResult(result_query.record());
}

DatabaseQueryRegistrationPlayer::DatabaseOut DatabaseQueryRegistrationPlayer::getResult()
{
    return m_db_out;
}
