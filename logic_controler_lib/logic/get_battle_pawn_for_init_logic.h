#ifndef GET_BATTLE_PAWN_FOR_INIT_LOGIC_H
#define GET_BATTLE_PAWN_FOR_INIT_LOGIC_H

#include "i_logic_template.h"
#include "get_battle_pawn_for_init_logic_args.h"

#include "../database/database_query_get_battle_pawn_for_init.h"

class GetBattlePawnForInitLogic : public I_LogicTemplate
{
private:
    GetBattlePawnForInitLogic();
    static GetBattlePawnForInitLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetBattlePawnForInit m_get_battle_pawn_for_init;

    GetBattlePawnForInitLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetBattlePawnForInitLogic* getTemplate();

    virtual ~GetBattlePawnForInitLogic();

};

#endif // GET_BATTLE_PAWN_FOR_INIT_LOGIC_H
