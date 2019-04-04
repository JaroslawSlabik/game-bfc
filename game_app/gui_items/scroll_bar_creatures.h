#ifndef SCROLL_BAR_CREATURES_H
#define SCROLL_BAR_CREATURES_H

#include "gui_items/i_gui_item.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "creature.h"
#include "../logic_controler_lib/logic/get_creatures_logic_args.h"
#include "../logic_controler_lib/global_struct/creature_info.h"

class ScrollBarCreatures : public I_GUIItem, public OpenGLObject2D
{
public:
    explicit ScrollBarCreatures(QObject *parent = 0) ;
    ~ScrollBarCreatures();

    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);
    bool setSizeItem(const QVector2D& size_selected, const QVector2D& size_unselected);

    virtual bool draw(Shader* shader) override;

    void loadCreaturesFromServer();
    void clear();

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;
    void saveClicked(CreatureInfo creature);
    void putOnMapAccepted(qlonglong id_creature);
    void putOffFromMapAccepted(qlonglong id_creature);

signals:
    void selectedCreature(CreatureInfo creature);

private:
    const float m_size_button_y = 20.0f;
    int m_selected_index = 0;
    void init();
    void select_next();
    void select_back();
    void refresh(int selected_index, int size_list);

    Creature* m_back;
    Creature* m_selected;
    Creature* m_next;

    OpenGLObject2D* m_button_back;
    OpenGLObject2D* m_body;
    OpenGLObject2D* m_button_next;

    bool m_draw_next = true;
    bool m_draw_selected = true;
    bool m_draw_back = false;

    bool m_is_used_next = false;
    bool m_is_used_selected = false;
    bool m_is_used_back = false;

    OpenGLObject2D* m_used_mask_back;
    OpenGLObject2D* m_used_mask_selected;
    OpenGLObject2D* m_used_mask_next;

    GetCreaturesLogicArgs args;

    static QList<std::pair<bool, CreatureInfo>> m_creature_info_list;

    Texture* m_texture_is_used;

    Q_OBJECT

};

#endif // SCROLL_BAR_CREATURES_H
