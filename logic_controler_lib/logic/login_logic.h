#ifndef LOGIN_LOGIC_H
#define LOGIN_LOGIC_H

#include "i_logic_template.h"
#include "login_logic_args.h"

#include "../database/database_query_gracz_select.h"

class LogInLogic : public I_LogicTemplate
{
private:
    LogInLogic();
    static LogInLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGraczSelect m_select_gracze;

    LogInLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static LogInLogic* getTemplate();

    virtual ~LogInLogic();
};

#endif // LOGIN_LOGIC_H
