#ifndef BOARD_CELL_TYPES_H
#define BOARD_CELL_TYPES_H
#include <QHash>
#include <QString>
#include <QObject>

typedef enum
{
    soil = 1,
    river,
    ice,
    mount,
    cave,
    BoardCellModelCount
}BoardCellModel_e;

typedef enum
{
    obstacle_permanent = 1,
    obstacle_on_earth,
    obstacle_in_air,
    no_obstacle,
    BoardCellTypeCount
}BoardCellType_e;

Q_DECLARE_METATYPE(BoardCellType_e);
Q_DECLARE_METATYPE(BoardCellModel_e);

//TODO: move to database
static const QHash<QString, std::pair<BoardCellModel_e, BoardCellType_e>> s_boardCellTypeHash = [] () -> const QHash<QString, std::pair<BoardCellModel_e, BoardCellType_e>> {
    QHash<QString, std::pair<BoardCellModel_e, BoardCellType_e>> d;
    d.insert("A", std::make_pair(BoardCellModel_e::soil, BoardCellType_e::no_obstacle));
    d.insert("B", std::make_pair(BoardCellModel_e::river, BoardCellType_e::obstacle_on_earth));
    d.insert("C", std::make_pair(BoardCellModel_e::ice, BoardCellType_e::no_obstacle));
    d.insert("D", std::make_pair(BoardCellModel_e::mount, BoardCellType_e::obstacle_on_earth));
    d.insert("E", std::make_pair(BoardCellModel_e::cave, BoardCellType_e::obstacle_permanent));
    return d;
} ();

#endif // BOARD_CELL_TYPES_H
