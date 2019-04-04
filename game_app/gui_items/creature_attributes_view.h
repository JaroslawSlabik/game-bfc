#ifndef CREATURE_ATTRIBUTES_VIEW_H
#define CREATURE_ATTRIBUTES_VIEW_H



#include "gui_items/i_gui_item.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "creature.h"
#include "button.h"
#include "../logic_controler_lib/logic/set_creature_attributes_logic_args.h"
#include "../graphic_lib/opengl_text_render_2d.h"

class CreatureAttributesView : public I_GUIItem
{
public:
    CreatureAttributesView();
    ~CreatureAttributesView();

    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);

    bool draw(Shader* shader);

    void clear();

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;
    void selectedCreature(CreatureInfo creature);
    void existPoints(bool exist);

private slots:
    void button_minus_clicked(int attribute_id);
    void button_plus_clicked(int attribute_id);
    void button_anuluj_clicked();
    void button_save_clicked();

signals:
    void plusClicked();
    void minusClicked();
    void anulujClicked();
    void saveClicked(CreatureInfo creature);

private:

    void inicjalize();
    void setAttributesToShow(CreatureInfo creature);

    Creature* m_creature;
    CreatureInfo m_creature_info_modification;
    bool m_exist_points_to_distribution;


    Button* m_anuluj;
    Button* m_save;
    Button* m_plus;
    Button* m_minus;
    OpenGLTextRender2D* m_titles_of_attributes;
    OpenGLTextRender2D* m_points_of_attributes;
    OpenGLTextRender2D* m_name;
    OpenGLTextRender2D* m_description;
    OpenGLObject2D* m_background;

    SetCreatureAttributesLogicArgs args;

    QVector2D m_position;
    QVector2D m_size;

    void resize();

    Q_OBJECT

};

#endif // CREATURE_ATTRIBUTES_VIEW_H
