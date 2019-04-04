#include "pawn_manager.h"
#include <QThread>

PawnManager::PawnManager()
{
    qRegisterMetaType<QMap<std::pair<int, int>, CreatureInfo>>("QMap<std::pair<int, int>, CreatureInfo>");
    qRegisterMetaType<QMap<std::pair<int, int>, BoardCellType_e>>("QMap<std::pair<int, int>, BoardCellType_e>");
    qRegisterMetaType<std::pair<int, int>>("std::pair<int, int>");

    m_direction_list = std::list<std::pair<int, int>>(
    {
        std::make_pair(1, 0),
        std::make_pair(0, 1),
        std::make_pair(-1, 0),
        std::make_pair(0, -1)
    });
}

PawnManager::~PawnManager()
{
    m_direction_list.clear();
}

void PawnManager::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void PawnManager::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{

}

void PawnManager::receiveFromServer(const QString& response)
{

}

void PawnManager::setNewPositionPawn(int x, int y, int new_x, int new_y)
{
    //if(false == m_player_turn)
    //{
    //    emit endWork();
    //
    //    return;
    //}

    m_current_pos_pawn.first = x;
    m_current_pos_pawn.second = y;

    findPathUsingAStarAlgorithm(m_current_pos_pawn.first, m_current_pos_pawn.second, new_x, new_y);
}

void PawnManager::initializationPawns(QMap<std::pair<int, int>, CreatureInfo> map_of_creature_info)
{
    m_map_of_creature_info = map_of_creature_info;
}

void PawnManager::initializationBoard(QMap<std::pair<int, int>, BoardCellType_e> map_of_board_cell_type, int size_x, int size_y)
{
    m_map_of_board_cell_type = map_of_board_cell_type;
    m_size_map_x = size_x;
    m_size_map_y = size_y;
}

void PawnManager::findPathUsingAStarAlgorithm(const int& xStart, const int& yStart, const int& xFinish, const int& yFinish)
{
    QMap<std::pair<int, int>, int> m_nodes_visited;
    QMap<std::pair<int, int>, int> m_nodes_not_yet_visited;
    QMap<std::pair<int, int>, std::pair<int, int>> m_directions_map;

    std::priority_queue<NodeObject, std::vector<NodeObject>, NodeObject::CompareNode> queue[2]; // list of open (not-yet-tried) nodes
    int queue_index = 0;
    NodeObject n0;
    NodeObject m0;
    int x = 0;
    int y = 0;
    std::pair<int, int> map_key;

    MovingCreatureType_e moving_creature_type = m_map_of_creature_info.value(std::make_pair(xStart, yStart)).m_move_type;

    // create the start node and push into list of open nodes
    n0 = NodeObject(xStart, yStart, 0, 0);
    n0.updatePriority(xFinish, yFinish);
    queue[queue_index].push(n0);
    m_nodes_not_yet_visited.insert(std::make_pair(xStart, yStart), n0.getPriority()); // mark it on the open nodes map

    // A* search
    while(!queue[queue_index].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes

        n0 = NodeObject(queue[queue_index].top());

        x=n0.getPosX();
        y=n0.getPosY();

        queue[queue_index].pop(); // remove the node from the open list

        map_key = std::make_pair(x,y);
        m_nodes_not_yet_visited.insert(map_key, 0);
        // mark it on the closed nodes map
        m_nodes_visited.insert(map_key, 1);

        if(x == xFinish && y == yFinish)
        {
            // empty the leftover nodes
            while(!queue[queue_index].empty())
            {
                queue[queue_index].pop();
            }

            // generate the path from finish to start by following the directions
            std::list<std::pair<int, int>> list_directions_from_finish_to_start;
            while(!(x==xStart && y==yStart))
            {
                map_key = std::make_pair(x,y);
                map_key = m_directions_map.value(map_key);
                x = x + map_key.first;
                y = y + map_key.second;

                map_key = std::make_pair(map_key.first * (-1), map_key.second * (-1));

                list_directions_from_finish_to_start.push_front(map_key);
            }

            for(std::pair<int, int> dir : list_directions_from_finish_to_start)
            {
                QThread::sleep(1);

                CreatureInfo current_creature_info = m_map_of_creature_info.value(m_current_pos_pawn);

                std::pair<int, int> next_position = std::make_pair(m_current_pos_pawn.first + dir.first, m_current_pos_pawn.second + dir.second);

                CreatureInfo probably_enemy_creature_info = m_map_of_creature_info.value(next_position);
                if(-1 != probably_enemy_creature_info.m_id && true == probably_enemy_creature_info.m_enemy)
                {
                    attack(m_current_pos_pawn, current_creature_info, next_position, probably_enemy_creature_info);

                    return;
                }

                move(dir, current_creature_info);
            }

            emit endWork();

            return;
        }

        // generate moves (child nodes) in all possible directions
        for(std::pair<int, int> direction : m_direction_list)
        {
            map_key = std::make_pair(x + direction.first, y + direction.second);

            if(m_nodes_visited.value(map_key) == 1)
            {
                continue;
            }

            if(map_key.first < 0 || map_key.first >= m_size_map_x || map_key.second < 0 ||  map_key.second >= m_size_map_y)
            {
                continue;
            }

            BoardCellType_e board_cell_type = m_map_of_board_cell_type.value(map_key);
            if((board_cell_type == BoardCellType_e::obstacle_permanent) ||
               (board_cell_type == BoardCellType_e::obstacle_in_air && moving_creature_type == MovingCreatureType_e::fly) ||
               (board_cell_type == BoardCellType_e::obstacle_on_earth && moving_creature_type == MovingCreatureType_e::walk))
            {
                continue;
            }

            if(-1 != m_map_of_creature_info.value(map_key, CreatureInfo()).m_id)
            {
                if(map_key.first != xFinish && map_key.second != yFinish)
                {
                    continue;
                }
                else
                {
                    if(false == m_map_of_creature_info.value(map_key, CreatureInfo()).m_enemy)
                    {
                        continue;
                    }
                }
            }

            // generate a child node
            m0 = NodeObject(map_key.first, map_key.second, n0.getLevel(), n0.getPriority());
            m0.nextLevel();
            m0.updatePriority(xFinish, yFinish);

            // if it is not in the open list then add into that
            if(0 == m_nodes_not_yet_visited.value(map_key, 0))
            {
                m_nodes_not_yet_visited.insert(map_key, m0.getPriority());
                queue[queue_index].push(m0);

                // mark its parent node directio
                m_directions_map.insert(map_key, std::make_pair(direction.first * -1, direction.second * -1));
            }
            else if(m0.getPriority() < m_nodes_not_yet_visited.value(map_key))
            {
                // update the priority info
                m_nodes_not_yet_visited.insert(map_key, m0.getPriority());

                // update the parent direction info
                m_directions_map.insert(map_key, std::make_pair(direction.first * -1, direction.second * -1));

                while(queue[queue_index].top().getPosX() != map_key.first || queue[queue_index].top().getPosY() != map_key.second)
                {
                    queue[1-queue_index].push(queue[queue_index].top());
                    queue[queue_index].pop();
                }

                queue[queue_index].pop(); // remove the wanted node

                // empty the larger size pq to the smaller one
                if(queue[queue_index].size() > queue[1-queue_index].size())
                    queue_index=1-queue_index;

                while(!queue[queue_index].empty())
                {
                    queue[1-queue_index].push(queue[queue_index].top());
                    queue[queue_index].pop();
                }

                queue_index=1-queue_index;

                queue[queue_index].push(m0); // add the better node instead
            }
        }
    }

    //not find path
    emit endWork();
}

void PawnManager::attack(std::pair<int, int> player_position, CreatureInfo& player_creature_info, std::pair<int, int> enemy_position, CreatureInfo& enemy_creature_info)
{
    if(enemy_creature_info.m_actual_health > 0 && player_creature_info.m_actual_move >= 2)
    {
        player_creature_info.m_actual_move -= 2;

        //TODO: attack
        enemy_creature_info.m_actual_health--;
    }

    updateInfo(player_position, player_creature_info);
    updateInfo(enemy_position, enemy_creature_info);

    emit endWork();

    return;
}

void PawnManager::move(std::pair<int, int> dir, CreatureInfo& player_creature_info)
{
    if(0 == player_creature_info.m_actual_move)
    {
        emit endWork();
        return;
    }

    player_creature_info.m_actual_move--;

    updateInfo(m_current_pos_pawn, player_creature_info);
    updatePosition(m_current_pos_pawn, player_creature_info, dir);
}

void PawnManager::updatePosition(std::pair<int, int> current_position, CreatureInfo& creature_info, std::pair<int, int> dir)
{
    m_map_of_creature_info.remove(current_position);
    std::pair<int, int> new_position = std::make_pair(m_current_pos_pawn.first + dir.first, m_current_pos_pawn.second + dir.second);
    m_map_of_creature_info.insert(new_position, creature_info);

    emit movePawnBaseVector(m_current_pos_pawn.first, m_current_pos_pawn.second, dir);

    m_current_pos_pawn = new_position;
}

void PawnManager::updateInfo(std::pair<int, int> current_position, CreatureInfo& creature_info)
{
    m_map_of_creature_info.insert(current_position, creature_info);

    emit updatePawnInfo(current_position, creature_info);
}

PawnManager::NodeObject::NodeObject()
{
    init(0, 0, 0, 0);
}

PawnManager::NodeObject::NodeObject(int x_pos, int y_pos, int level, int priority)
{
    init(x_pos, y_pos, level, priority);
}

PawnManager::NodeObject::NodeObject(const NodeObject& node)
{
    init(node.getPosX(), node.getPosY(), node.getLevel(), node.getPriority());
}

int PawnManager::NodeObject::getPosX() const
{
    return m_x_pos;
}

int PawnManager::NodeObject::getPosY() const
{
    return m_y_pos;
}

int PawnManager::NodeObject::getLevel() const
{
    return m_level;
}

int PawnManager::NodeObject::getPriority() const
{
    return m_priority;
}

void PawnManager::NodeObject::updatePriority(const int & xDest, const int & yDest)
{
     m_priority = m_level + distanceCalculation(xDest, yDest);
}

void PawnManager::NodeObject::nextLevel()
{
     m_level += 1;
}

void PawnManager::NodeObject::init(int x_pos, int y_pos, int level, int priority)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_level = level;
    m_priority = priority;
}

int PawnManager::NodeObject::distanceCalculation(const int & xDest, const int & yDest)
{
    int x_distance = xDest - m_x_pos;
    int y_distance = yDest - m_y_pos;

    return static_cast<int>(sqrt((x_distance * x_distance) + (y_distance * y_distance)));
}

bool PawnManager::NodeObject::CompareNode::operator()(const NodeObject& left, const NodeObject& right)
{
    return left.getPriority() > right.getPriority();
}
