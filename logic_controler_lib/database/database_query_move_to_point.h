#ifndef DATABASE_QUERY_MOVE_TO_POINT_H
#define DATABASE_QUERY_MOVE_TO_POINT_H
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "i_query_template.h"

class DatabaseQueryMoveToPoint  : public I_QueryTemplate
{
public:
    qlonglong m_id_creature_player;
    int m_pozycja_x;
    int m_pozycja_y;

    struct DatabaseOut : public I_QueryTemplate::Out
    {
        bool was_ok;
        int status;
        QString db_message;

        virtual void setResult(QSqlRecord rec) override;
    };

    DatabaseOut getResult();

    DatabaseQueryMoveToPoint();
    virtual QString prepareQuery() override;
    virtual void setResult(QSqlQuery& result_query) override;

private:
    DatabaseOut m_db_out;
};

#endif // DATABASE_QUERY_MOVE_TO_POINT_H
