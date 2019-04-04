#include "logic.h"

#include "login_logic.h"
#include "logout_logic.h"
#include "get_creatures_logic.h"
#include "get_player_info_logic.h"
#include "set_creature_attributes_logic.h"
#include "set_creature_waiting_logic.h"
#include "set_player_waiting_logic.h"
#include "set_abort_waiting_logic.h"
#include "get_waiting_info_logic.h"
#include "get_battle_map_for_init_logic.h"
#include "get_battle_pawn_for_init_logic.h"
#include "move_to_point_logic.h"
#include "attack_logic.h"
#include "get_info_about_enemy_pawn_logic.h"
#include "new_turn_logic.h"
#include "registration_player_logic.h"

Logic::Logic()
{
    //NOTE: lazy initialization
    m_map_of_logic.insert(LogInLogic::getLogicName(), LogInLogic::getTemplate());
    m_map_of_logic.insert(LogOutLogic::getLogicName(), LogOutLogic::getTemplate());
    m_map_of_logic.insert(GetCreaturesLogic::getLogicName(), GetCreaturesLogic::getTemplate());
    m_map_of_logic.insert(GetPlayerInfoLogic::getLogicName(), GetPlayerInfoLogic::getTemplate());
    m_map_of_logic.insert(SetCreatureAttributesLogic::getLogicName(), SetCreatureAttributesLogic::getTemplate());
    m_map_of_logic.insert(SetCreatureWaitingLogic::getLogicName(), SetCreatureWaitingLogic::getTemplate());
    m_map_of_logic.insert(SetPlayerWaitingLogic::getLogicName(), SetPlayerWaitingLogic::getTemplate());
    m_map_of_logic.insert(SetAbortWaitingLogic::getLogicName(), SetAbortWaitingLogic::getTemplate());
    m_map_of_logic.insert(GetWaitingInfoLogic::getLogicName(), GetWaitingInfoLogic::getTemplate());
    m_map_of_logic.insert(GetBattleMapForInitLogic::getLogicName(), GetBattleMapForInitLogic::getTemplate());
    m_map_of_logic.insert(GetBattlePawnForInitLogic::getLogicName(), GetBattlePawnForInitLogic::getTemplate());
    m_map_of_logic.insert(MoveToPointLogic::getLogicName(), MoveToPointLogic::getTemplate());
    m_map_of_logic.insert(AttackLogic::getLogicName(), AttackLogic::getTemplate());
    m_map_of_logic.insert(GetInfoAboutEnemyPawnLogic::getLogicName(), GetInfoAboutEnemyPawnLogic::getTemplate());
    m_map_of_logic.insert(NewTurnLogic::getLogicName(), NewTurnLogic::getTemplate());
    m_map_of_logic.insert(RegistrationPlayerLogic::getLogicName(), RegistrationPlayerLogic::getTemplate());
}

void Logic::setLogicTemplate(I_LogicTemplate* template_logic)
{
    m_logic = template_logic;
}

bool Logic::setArguments(QString arguments)
{
    QStringList argumentList = arguments.split(";");
    if(argumentList.isEmpty())
        return false;

    //NOTE: fast initialization
    //bool fit = false;
    //if(argumentList.at(m_pos_logic_name) == LogInLogic::getLogicName())
    //{
    //    setLogicTemplate(LogInLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == LogOutLogic::getLogicName())
    //{
    //    setLogicTemplate(LogOutLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetCreaturesLogic::getLogicName())
    //{
    //    setLogicTemplate(GetCreaturesLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetPlayerInfoLogic::getLogicName())
    //{
    //    setLogicTemplate(GetPlayerInfoLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == SetCreatureAttributesLogic::getLogicName())
    //{
    //    setLogicTemplate(SetCreatureAttributesLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == SetCreatureWaitingLogic::getLogicName())
    //{
    //    setLogicTemplate(SetCreatureWaitingLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == SetPlayerWaitingLogic::getLogicName())
    //{
    //    setLogicTemplate(SetPlayerWaitingLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == SetAbortWaitingLogic::getLogicName())
    //{
    //    setLogicTemplate(SetAbortWaitingLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetWaitingInfoLogic::getLogicName())
    //{
    //    setLogicTemplate(GetWaitingInfoLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetBattleMapForInitLogic::getLogicName())
    //{
    //    setLogicTemplate(GetBattleMapForInitLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetBattlePawnForInitLogic::getLogicName())
    //{
    //    setLogicTemplate(GetBattlePawnForInitLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == MoveToPointLogic::getLogicName())
    //{
    //    setLogicTemplate(MoveToPointLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == AttackLogic::getLogicName())
    //{
    //    setLogicTemplate(AttackLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == GetInfoAboutEnemyPawnLogic::getLogicName())
    //{
    //    setLogicTemplate(GetInfoAboutEnemyPawnLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == NewTurnLogic::getLogicName())
    //{
    //    setLogicTemplate(NewTurnLogic::getTemplate());
    //    fit = true;
    //}
    //if(argumentList.at(m_pos_logic_name) == RegistrationPlayerLogic::getLogicName())
    //{
    //    setLogicTemplate(RegistrationPlayerLogic::getTemplate());
    //    fit = true;
    //}
    //if(!fit)
    //    return false;

    //NOTE: lazy initialization
    m_logic = m_map_of_logic.value(argumentList.at(m_pos_logic_name), nullptr);

    if(m_logic == nullptr)
        return false;

    return m_logic->setArguments(argumentList, m_last_error);
}

bool Logic::work(QString dbConnectionNmae)
{
    if(m_logic == nullptr)
        return false;

    return m_logic->work(dbConnectionNmae, m_last_error);
}

QString Logic::getResult()
{
    QString res = "";
    if(m_logic != nullptr)
        res = m_logic->getResult();

    return res;
}

QString Logic::getLastError()
{
    return m_last_error;
}
