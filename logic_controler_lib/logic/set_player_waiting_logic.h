#ifndef SET_PLAYER_WAITING_LOGIC_H
#define SET_PLAYER_WAITING_LOGIC_H
#include "i_logic_template.h"
#include "set_player_waiting_logic_args.h"

#include "../database/database_query_set_insert_player_waiting.h"
#include "../database/database_query_set_update_creature_waiting.h"

class SetPlayerWaitingLogic : public I_LogicTemplate
{
private:
    SetPlayerWaitingLogic();
    static SetPlayerWaitingLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQuerySetInsertPlayerWaiting m_set_player_waiting;

    SetPlayerWaitingLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static SetPlayerWaitingLogic* getTemplate();

    virtual ~SetPlayerWaitingLogic();
};

#endif // SET_PLAYER_WAITING_LOGIC_H
