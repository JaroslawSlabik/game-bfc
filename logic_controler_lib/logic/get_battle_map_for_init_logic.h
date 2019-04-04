#ifndef GET_BATTLE_MAP_LOGIC_H
#define GET_BATTLE_MAP_LOGIC_H
#include "i_logic_template.h"
#include "get_battle_map_for_init_logic_args.h"

#include "../database/database_query_get_battle_map_for_init.h"

class GetBattleMapForInitLogic : public I_LogicTemplate
{
private:
    GetBattleMapForInitLogic();
    static GetBattleMapForInitLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetBattleMapForInit m_get_battle_map_for_init;

    GetBattleMapForInitLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetBattleMapForInitLogic* getTemplate();

    virtual ~GetBattleMapForInitLogic();
};

#endif // GET_BATTLE_MAP_LOGIC_H
