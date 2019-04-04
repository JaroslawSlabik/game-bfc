#ifndef GET_WAITING_INFO_LOGIC_H
#define GET_WAITING_INFO_LOGIC_H
#include "i_logic_template.h"
#include "get_waiting_info_logic_args.h"

#include "../database/database_query_get_waiting_info.h"

class GetWaitingInfoLogic : public I_LogicTemplate
{
private:
    GetWaitingInfoLogic();
    static GetWaitingInfoLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetWaitingInfo m_get_waiting_info;

    GetWaitingInfoLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetWaitingInfoLogic* getTemplate();

    virtual ~GetWaitingInfoLogic();
};

#endif // GET_WAITING_INFO_LOGIC_H
