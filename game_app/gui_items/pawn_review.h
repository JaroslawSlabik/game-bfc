#ifndef PAWN_REVIEW_H
#define PAWN_REVIEW_H
#include <QObject>

#include "pawn.h"
#include "opengl_text_render_2d.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "progres_bar.h"
#include "../logic_controler_lib/global_struct/creature_info.h"
#include "../logic_controler_lib/global_struct/elements.h"

class PawnReview : public QObject
{
public:
    explicit PawnReview(QObject* parent = 0);
    ~PawnReview();

    void setInfo(CreatureInfo info);

    bool draw(Shader *shader);
    void setPosition(float x, float y);
    void setSize(float x, float y);
    void setTitle(QString title);

public slots:
    void setPermanentlyInfo(CreatureInfo info);
    void setMomentInfo(CreatureInfo info);
    void revertToPermanentlyInfo();
    void clear();

private:
    QVector2D m_position;
    QVector2D m_size;

    OpenGLObject2D* m_background_1;
    OpenGLObject2D* m_background_2;

    OpenGLTextRender2D* m_title_review;

    Pawn* m_pawn;
    OpenGLTextRender2D* m_name;
    OpenGLTextRender2D* m_health;
    OpenGLTextRender2D* m_shield;
    OpenGLTextRender2D* m_attack;
    OpenGLTextRender2D* m_points_of_move;
    ElementIcon* m_map_element_icon;

    CreatureInfo m_info;

    void resize();

    Q_OBJECT
};

#endif // PAWN_REVIEW_H
