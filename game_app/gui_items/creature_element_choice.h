#ifndef CREATURE_ELEMENT_CHOICE_H
#define CREATURE_ELEMENT_CHOICE_H

#include "gui_items/i_gui_item.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "creature.h"
#include "button.h"
#include "../graphic_lib/opengl_text_render_2d.h"
#include "power_icon.h"

class CreatureElementChoice : public I_GUIItem
{
public:
    CreatureElementChoice();
    ~CreatureElementChoice();

    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);
    bool draw(Shader* shader);

    void clear();

    ElementType_e getChoiceElement();

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;
    void selectedCreature(CreatureInfo creature);

private slots:
    void buttonEarthElementClicked();
    void buttonWaterElementClicked();
    void buttonAirElementClicked();
    void buttonFireElementClicked();

private:
    Button* m_earth_element;
    Button* m_water_element;
    Button* m_air_element;
    Button* m_fire_element;
    Creature* m_creature;
    OpenGLObject2D* m_background;
    OpenGLObject2D* m_used_mask;
    OpenGLTextRender2D* m_name;
    OpenGLTextRender2D* m_health_label;
    OpenGLTextRender2D* m_health_value;
    OpenGLTextRender2D* m_shield_label;
    OpenGLTextRender2D* m_shield_value;
    OpenGLTextRender2D* m_attack_label;
    OpenGLTextRender2D* m_attack_value;
    OpenGLTextRender2D* m_move_label;
    OpenGLTextRender2D* m_move_value;
    ElementIcon* m_element_icon;
    QVector2D m_position;
    QVector2D m_size;

    void resize();

    Q_OBJECT

};

#endif // CREATURE_ELEMENT_CHOICE_H
