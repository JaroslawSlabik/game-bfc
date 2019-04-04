#include "player_info.h"

qlonglong PlayerInfo::m_id_player;
QString PlayerInfo::m_name;
int PlayerInfo::m_level;
qlonglong PlayerInfo::m_experience;
qlonglong PlayerInfo::m_experience_to_next_level;
int PlayerInfo::m_points_to_distribution;

void PlayerInfo::setIdPlayer(qlonglong id_player)
{
    m_id_player = id_player;
}

qlonglong PlayerInfo::getIdPlayer()
{
    return m_id_player;
}

void PlayerInfo::setName(QString name)
{
    m_name = name;
}

QString PlayerInfo::getName()
{
    return m_name;
}

void PlayerInfo::setLevel(int level)
{
    m_level = level;
}

int PlayerInfo::getLevel()
{
    return m_level;
}

void PlayerInfo::setExperience(qlonglong experience)
{
    m_experience = experience;
}

qlonglong PlayerInfo::getExperience()
{
    return m_experience;
}

void PlayerInfo::setExperienceToNextLevel(qlonglong experience_to_next_level)
{
    m_experience_to_next_level = experience_to_next_level;
}

qlonglong PlayerInfo::getExperienceToNextLevel()
{
    return m_experience_to_next_level;
}

void PlayerInfo::setPointsToDistribution(int points_to_distribution)
{
    m_points_to_distribution = points_to_distribution;
}

int PlayerInfo::getPointsToDistribution()
{
    return m_points_to_distribution;
}
