#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include "QObject"

struct PlayerInfo
{
private:
    static qlonglong m_id_player;
    static QString m_name;
    static int m_level;
    static qlonglong m_experience;
    static qlonglong m_experience_to_next_level;
    static int m_points_to_distribution;

public:
    static void setIdPlayer(qlonglong);
    static qlonglong getIdPlayer();

    static void setName(QString);
    static QString getName();

    static void setLevel(int);
    static int getLevel();

    static void setExperience(qlonglong);
    static qlonglong getExperience();

    static void setExperienceToNextLevel(qlonglong);
    static qlonglong getExperienceToNextLevel();

    static void setPointsToDistribution(int);
    static int getPointsToDistribution();

    static void clear()
    {
        m_id_player = -1;
        m_name = "";
        m_level = -1;
        m_experience = -1;
        m_experience_to_next_level = -1;
        m_points_to_distribution = -1;
    }
};



Q_DECLARE_METATYPE(PlayerInfo)

#endif // PLAYER_INFO_H
