#ifndef I_LOGIC_TEMPLATE_H
#define I_LOGIC_TEMPLATE_H

#include <QStringList>

class I_LogicTemplate
{
public:
    virtual bool setArguments(QStringList arguments, QString& error) = 0;
    virtual bool work(QString dbConnectionNmae, QString& error) = 0;
    virtual QString getResult() = 0;
};

#endif // I_LOGIC_TEMPLATE_H
