#ifndef DATABASE_QUERY_GET_PLAYER_CREATURES_H
#define DATABASE_QUERY_GET_PLAYER_CREATURES_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QByteArray>

#include "i_query_template.h"

class DatabaseQueryGetPlayerCreatures : public I_QueryTemplate
{
public:
    qlonglong m_id_gracza;
    qlonglong m_lp;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        qlonglong id_potwora_gracza;
        QString nazwa;
        QString opis;
        QByteArray tekstura;
        int zdrowie;
        int ochrona;
        int atak;
        int punkty_ruchu;

        virtual void setResult(QSqlRecord rec) override;

        virtual ~DatabaseOut(){}
    };

    QList<DatabaseOut> getResult();

    DatabaseQueryGetPlayerCreatures();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

    virtual ~DatabaseQueryGetPlayerCreatures(){}
private:
    static QList<DatabaseOut> m_db_out;
};

#endif // DATABASE_QUERY_GET_PLAYER_CREATURES_H
