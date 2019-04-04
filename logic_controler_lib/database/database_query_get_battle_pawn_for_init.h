#ifndef DATABASE_QUERY_GET_BATTLE_PAWN_FOR_INIT_H
#define DATABASE_QUERY_GET_BATTLE_PAWN_FOR_INIT_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryGetBattlePawnForInit  : public I_QueryTemplate
{
public:
    qlonglong m_id_player;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        qlonglong id_boahtera_gracza;
        QString nazwa;
        QString opis;
        QByteArray tekstura;
        int zdrowie;
        int ochrona;
        int atak;
        int punkty_ruchu;
        int pozycja_x;
        int pozycja_y;
        int zywiol;
        bool wrog;

        virtual void setResult(QSqlRecord rec) override;
    };

    QList<DatabaseOut> getResult();

    DatabaseQueryGetBattlePawnForInit();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    static QList<DatabaseOut> m_db_out;
};

#endif // DATABASE_QUERY_GET_BATTLE_PAWN_FOR_INIT_H
