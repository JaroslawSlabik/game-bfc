#ifndef SET_ABORT_WAITING_LOGIC_H
#define SET_ABORT_WAITING_LOGIC_H
#include "i_logic_template.h"
#include "set_abort_waiting_logic_args.h"

#include "../database/database_query_set_abort_waiting.h"

class SetAbortWaitingLogic : public I_LogicTemplate
{
private:
    SetAbortWaitingLogic();
    static SetAbortWaitingLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQuerySetAbortWaiting m_set_abort_waiting;

    SetAbortWaitingLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static SetAbortWaitingLogic* getTemplate();

    virtual ~SetAbortWaitingLogic();
};


#endif // SET_ABORT_WAITING_LOGIC_H
