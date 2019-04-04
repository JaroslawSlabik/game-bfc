#include "logic_list.h"

LogicList::LogicMember LogicList::logic_list[] = {
       {LogicList::LogicMember::LogIn, "login"},
       {LogicList::LogicMember::LogOut, "logout"},
       {LogicList::LogicMember::GetCreatures, "getcreatures"},
       {LogicList::LogicMember::GetPlayerInfo, "getplayerinfo"},
       {LogicList::LogicMember::SetCreatureAttributes, "setcreatureattributes"},
       {LogicList::LogicMember::SetCreatureWaiting, "setcreaturewaiting"},
       {LogicList::LogicMember::SetPlayerWaiting, "setplayerwaiting"},
       {LogicList::LogicMember::SetAbortWaitingLogic, "setabortwaitinglogic"},
       {LogicList::LogicMember::GetWaitingInfoLogic, "getwaitinginfologic"},
       {LogicList::LogicMember::GetBattleMapForInitLogic, "getbattlemapforinitlogic"},
       {LogicList::LogicMember::GetBattlePawnForInitLogic, "getbattlepawnforinitlogic"},
       {LogicList::LogicMember::AttackLogic, "attacklogic"},
       {LogicList::LogicMember::MoveToPointLogic, "movetopointlogic"},
       {LogicList::LogicMember::NewTurnLogic, "newturnlogic"},
       {LogicList::LogicMember::GetInfoAboutEnemyPawnLogic, "getinfoaboutenemypawnlogic"},
       {LogicList::LogicMember::RegistrationPlayerLogic, "registrationplayerlogic"}
};

QString LogicList::getLogicName(LogicMember::LogicNameEnum logic_name)
{
    for(LogicMember l : logic_list)
    {
        if(l.logicNameEnum == logic_name)
            return l.logicName;
    }

    return "";
}

LogicList::LogicMember::LogicNameEnum LogicList::getLogicEnum(QString logic_name)
{
    for(LogicMember l : logic_list)
    {
        if(l.logicName == logic_name)
            return l.logicNameEnum;
    }

    return LogicMember::LogicNameEnum::Bad;
}
