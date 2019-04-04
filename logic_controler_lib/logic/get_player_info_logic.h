#ifndef GET_PLAYER_INFO_LOGIC_H
#define GET_PLAYER_INFO_LOGIC_H

#include "i_logic_template.h"
#include "get_player_info_logic_args.h"

#include "../database/database_query_get_player_info.h"

class GetPlayerInfoLogic : public I_LogicTemplate
{
private:
    GetPlayerInfoLogic();
    static GetPlayerInfoLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetPlayerInfo m_get_player_info;

    GetPlayerInfoLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetPlayerInfoLogic* getTemplate();

    virtual ~GetPlayerInfoLogic();
};

#endif // GET_PLAYER_INFO_LOGIC_H
