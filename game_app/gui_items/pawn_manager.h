#ifndef PAWN_MANAGER_H
#define PAWN_MANAGER_H
#include <QObject>
#include <QMetaType>
#include <QTimer>
#include <list>
#include <math.h>
#include <queue>
#include "gui_items/i_gui_item.h"
#include "../logic_controler_lib/global_struct/creature_info.h"
#include "../logic_controler_lib/global_struct/elements.h"
#include "../logic_controler_lib/global_struct/board_cell_types.h"

/* IMPLEMENTATION OF ALGORITHM A STAR*/

class PawnManager : public I_GUIItem
{
public:
    PawnManager();
    ~PawnManager();

public slots:
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void receiveFromServer(const QString& response) override;

    void setNewPositionPawn(int x, int y, int new_x, int new_y);
    void initializationPawns(QMap<std::pair<int, int>, CreatureInfo> map_of_creature_info);
    void initializationBoard(QMap<std::pair<int, int>, BoardCellType_e> map_of_board_cell_type, int size_x, int size_y);

signals:
    void movePawnBaseVector(int x, int y, std::pair<int, int> vector);
    void updatePawnInfo(std::pair<int, int> position, CreatureInfo info);
    void endWork();

private:
    void findPathUsingAStarAlgorithm(const int& xStart, const int& yStart, const int& xFinish, const int& yFinish);

    void attack(std::pair<int, int> player_position, CreatureInfo& player_creature_info, std::pair<int, int> enemy_position, CreatureInfo& enemy_creature_info);
    void move(std::pair<int, int> dir, CreatureInfo& player_creature_info);
    void updatePosition(std::pair<int, int> current_position, CreatureInfo& creature_info, std::pair<int, int> new_position);
    void updateInfo(std::pair<int, int> current_position, CreatureInfo& creature_info);

    QMap<std::pair<int, int>, CreatureInfo> m_map_of_creature_info;
    QMap<std::pair<int, int>, BoardCellType_e> m_map_of_board_cell_type;

    std::pair<int, int> m_current_pos_pawn;

    int m_size_map_x;
    int m_size_map_y;

    std::list<std::pair<int, int>> m_direction_list;

    class NodeObject
    {
    public:
        NodeObject();
        NodeObject(int x_pos, int y_pos, int level, int priority);
        NodeObject(const NodeObject& node);
        int getPosX() const;
        int getPosY() const;
        int getLevel() const;
        int getPriority() const;
        void updatePriority(const int & xDest, const int & yDest);
        void nextLevel();

        struct CompareNode
        {
            bool operator()(const NodeObject& left, const NodeObject& right);
        };

    private:
        void init(int x_pos, int y_pos, int level, int priority);
        int distanceCalculation(const int & xDest, const int & yDest);

        int m_x_pos;
        int m_y_pos;
        int m_level;
        int m_priority;
    };

    bool m_player_turn = false;

    Q_OBJECT
};

#endif // PAWN_MANAGER_H
