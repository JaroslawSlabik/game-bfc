#ifndef MAP_POSITION_PAWN_CHOICE_H
#define MAP_POSITION_PAWN_CHOICE_H
#include "gui_items/i_gui_item.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "creature.h"
#include "../logic_controler_lib/global_struct/elements.h"
#include "../logic_controler_lib/logic/set_creature_waiting_logic_args.h"
#include "gui_items/power_icon.h"

class MapPositionPawnChoice : public I_GUIItem
{
public:
    MapPositionPawnChoice();
    ~MapPositionPawnChoice();

    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);

    bool draw(Shader* shader);

    void clear();

signals:
    void putOnMap(qlonglong id_creature);
    void putOffFromMap(qlonglong id_creature);

    void selectedPawn();
    void selectedEmptyCell();
    void selectedOutsideMap();
    void selectedEmptyCellButLackSeats();

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;

    void selectedCreature(CreatureInfo creature);

    void putOn(ElementType_e element);
    void putOff();

private:
    Q_OBJECT

    OpenGLObject2D** m_map_fields;
    Creature** m_map_fields_creature;
    ElementIcon** m_map_fields_element;
    bool** m_mark_position_map;

    CreatureInfo m_selected_creature_info;
    ElementType_e m_selected_element;

    void clearMark();
    void setMarkPosition(int x, int y);
    void getMarkPosition(int& x_pos, int& y_pos);

    SetCreatureWaitingLogicArgs args;

    OpenGLObject2D* m_background;
    QVector2D m_position;
    QVector2D m_size;

    void resize();

};

#endif // MAP_POSITION_PAWN_CHOICE_H
