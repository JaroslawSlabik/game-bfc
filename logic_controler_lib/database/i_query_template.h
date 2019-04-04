#ifndef QUERY_TEMPLATE_H
#define QUERY_TEMPLATE_H
#include <QString>
#include <QSqlQuery>

class I_QueryTemplate
{
public:
    virtual QString prepareQuery() = 0;
    virtual void setResult(QSqlQuery& result_query) = 0;
    struct Out
    {
        virtual void setResult(QSqlRecord rec) = 0;
    };

};

#endif // QUERY_TEMPLATE_H
