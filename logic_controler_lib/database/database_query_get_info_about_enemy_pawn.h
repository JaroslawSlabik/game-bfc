#ifndef DATABASE_QUERY_GET_INFO_ABOUT_ENEMY_PAWN_H
#define DATABASE_QUERY_GET_INFO_ABOUT_ENEMY_PAWN_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryGetInfoAboutEnemyPawn  : public I_QueryTemplate
{
public:
    qlonglong m_id_player;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        qlonglong id_boahtera_gracza;
        int zdrowie;
        int ochrona;
        int punkty_ruchu;
        int pozycja_x;
        int pozycja_y;

        virtual void setResult(QSqlRecord rec) override;
    };

    QList<DatabaseOut> getResult();

    DatabaseQueryGetInfoAboutEnemyPawn();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    static QList<DatabaseOut> m_db_out;
};

#endif // DATABASE_QUERY_GET_INFO_ABOUT_ENEMY_PAWN_H
