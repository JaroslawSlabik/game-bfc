#ifndef PLAYER_ATTRIBUTES_H
#define PLAYER_ATTRIBUTES_H

#include "gui_items/i_gui_item.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "../logic_controler_lib/logic/get_player_info_logic_args.h"
#include "../logic_controler_lib/global_struct/player_info.h"
#include "../logic_controler_lib/global_struct/creature_info.h"
#include "progres_bar.h"
#include "../graphic_lib/opengl_text_render_2d.h"

class PlayerAttributes : public I_GUIItem, public OpenGLObject2D
{
    Q_OBJECT

public:
    explicit PlayerAttributes(QObject *parent = 0) ;
    ~PlayerAttributes();

    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);

    virtual bool draw(Shader* shader) override;

    void loadPlayerFromServer();
    void loadPlayerFromPLayerInfo(const PlayerInfo& info);

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;

    void minusClicked();
    void plusClicked();
    void anulujClicked();
    void saveClicked(CreatureInfo creature);

signals:
    void existPoints(bool exist);

private:
    GetPlayerInfoLogicArgs args;
    ProgresBar* m_progres_bar;
    OpenGLTextRender2D* m_level_text;
    OpenGLTextRender2D* m_point_to_distribution_value;
    OpenGLObject2D* m_point_to_distribution_icon;
    OpenGLTextRender2D* m_points_experience;  // -> [experience] / [experience_to_next_level]
    OpenGLObject2D* m_level_background;
    QVector2D m_position;
    QVector2D m_size;

    int m_points_to_distribution = 0;

    void inicjalize();

    void refreshPointsToDistributionOnView(int points);

    void resize();
};

#endif // PLAYER_ATTRIBUTES_H
