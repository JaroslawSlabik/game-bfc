#ifndef LOGIC_LIST_H
#define LOGIC_LIST_H
#include <QString>

class LogicList
{
public:
    struct LogicMember
    {
        typedef enum
        {
            LogIn,
            LogOut,
            GetCreatures,
            GetPlayerInfo,
            SetCreatureAttributes,
            SetCreatureWaiting,
            SetPlayerWaiting,
            SetAbortWaitingLogic,
            GetWaitingInfoLogic,
            GetBattleMapForInitLogic,
            GetBattlePawnForInitLogic,
            AttackLogic,
            MoveToPointLogic,
            NewTurnLogic,
            GetInfoAboutEnemyPawnLogic,
            RegistrationPlayerLogic,
            Count,
            Bad
        } LogicNameEnum;

        LogicNameEnum logicNameEnum;

        QString logicName;
    };

    static LogicMember logic_list[];

    static QString getLogicName(LogicMember::LogicNameEnum logic_name);

    static LogicMember::LogicNameEnum getLogicEnum(QString logic_name);
};

#endif // LOGIC_LIST_H
