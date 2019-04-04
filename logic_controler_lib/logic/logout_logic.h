#ifndef LOGOUT_LOGIC_H
#define LOGOUT_LOGIC_H

#include "i_logic_template.h"

class LogOutLogic : public I_LogicTemplate
{
private:
    LogOutLogic();
    static LogOutLogic* s_logout_logic;
    static QString s_logic_name;

    enum ArgumentNames
    {
        ID_GRACZA = 1,
        COUNT
    };

    QString result = "";
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static LogOutLogic* getTemplate();

    virtual ~LogOutLogic();
};


#endif // LOGOUT_LOGIC_H
