#ifndef MAP_OF_PAWN_H
#define MAP_OF_PAWN_H
#include <QObject>

#include "gui_items/i_gui_item.h"
#include "gui_items/pawn.h"
#include "opengl_object_2d.h"
#include "shader.h"
#include "../logic_controler_lib/global_struct/creature_info.h"
#include "../logic_controler_lib/global_struct/elements.h"
#include "../logic_controler_lib/global_struct/board_cell_types.h"

class MapOfPawn : public I_GUIItem, public OpenGLObject2D
{
public:
    explicit MapOfPawn(QObject *parent = 0) ;
    ~MapOfPawn();

    virtual bool draw(Shader* shader) override;
    void setPositionPawn(int x, int y, int new_x, int new_y);

    void loadPawnsFromServer();

public slots:
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void receiveFromServer(const QString& response) override;
    void selectedCell(int x, int y, bool mark);
    void selectedNotCell();
    void Initialization(QVector2D position, QVector2D size);
    void Update(QVector2D position, QVector2D size);
    void movePawnBaseVector(int x, int y, std::pair<int, int> vector);
    void endWork();
    void updatePawnInfo(std::pair<int, int> position, CreatureInfo info);


signals:
    void selectPawn(CreatureInfo info, bool mark);
    void selectNotPawn(bool mark);
    void setNewPositionPawn(int x, int y, int new_x, int new_y);
    void initializationPawns(QMap<std::pair<int, int>, CreatureInfo> map_of_creature_info);

private:
    QMap<std::pair<int, int>, Pawn*> m_map_of_pawn;
    QVector2D m_position_map;
    QVector2D m_size_cell;
    std::pair<int, int> m_selected_pawn;
    std::pair<int, int> m_selected_cell;
    std::pair<int, int> m_selected_enemy_pawn;
    bool m_do_something;

    Q_OBJECT
};

#endif // MAP_OF_PAWN_H
