#include "pawn_review.h"

#include "plate_mesh.h"

PawnReview::PawnReview(QObject* parent)
{
    m_title_review = new OpenGLTextRender2D();
    m_title_review->setFontName("Arial.ttf");
    m_title_review->setFontSize(15);
    m_title_review->setColorText(QColor(0, 0, 0));

    m_background_1 = new OpenGLObject2D();
    m_background_1->setMesh(new PlateMesh());
    m_background_1->setBaseColor(QColor(255, 0, 0));

    m_background_2 = new OpenGLObject2D();
    m_background_2->setMesh(new PlateMesh());
    m_background_2->setBaseColor(QColor(255, 255, 255));

    m_pawn = new Pawn();

    m_name = new OpenGLTextRender2D();
    m_name->setFontName("Arial.ttf");
    m_name->setFontSize(15);
    m_name->setColorText(QColor(0, 0, 0));

    m_health = new OpenGLTextRender2D();
    m_health->setFontName("Arial.ttf");
    m_health->setFontSize(15);
    m_health->setColorText(QColor(0, 0, 0));

    m_shield = new OpenGLTextRender2D();
    m_shield->setFontName("Arial.ttf");
    m_shield->setFontSize(15);
    m_shield->setColorText(QColor(0, 0, 0));

    m_attack = new OpenGLTextRender2D();
    m_attack->setFontName("Arial.ttf");
    m_attack->setFontSize(15);
    m_attack->setColorText(QColor(0, 0, 0));

    m_points_of_move = new OpenGLTextRender2D();
    m_points_of_move->setFontName("Arial.ttf");
    m_points_of_move->setFontSize(15);
    m_points_of_move->setColorText(QColor(0, 0, 0));

    m_map_element_icon = new ElementIcon;

}

PawnReview::~PawnReview()
{
    delete m_title_review;

    delete m_background_1;
    delete m_background_2;

    delete m_pawn;

    delete m_name;
    delete m_health;
    delete m_shield;
    delete m_attack;
    delete m_points_of_move;

    delete m_map_element_icon;
}

void PawnReview::setInfo(CreatureInfo info)
{
    m_pawn->setInfo(info);

    m_name->setTextRender(QString("Nazwa: %1").arg(info.m_name));
    m_health->setTextRender(QString("Zdrowie: %1").arg(info.m_actual_health));
    m_shield->setTextRender(QString("Obrona: %1").arg(info.m_actual_shield));
    m_attack->setTextRender(QString("Atak: %1").arg(info.m_attack));
    m_points_of_move->setTextRender(QString("Ruchy: %1").arg(info.m_actual_move));

    m_map_element_icon->setElement(info.m_element);
}

bool PawnReview::draw(Shader *shader)
{
    m_title_review->draw(shader);

    m_background_1->draw(shader);
    m_background_2->draw(shader);

    if(-1 == m_pawn->getInfo().m_id)
    {
        return true;
    }

    m_pawn->draw(shader);

    m_name->draw(shader);
    m_health->draw(shader);
    m_shield->draw(shader);
    m_attack->draw(shader);
    m_points_of_move->draw(shader);
    m_map_element_icon->draw(shader);

    return true;
}

void PawnReview::setPosition(float x, float y)
{
    m_position = QVector2D(x, y);

    resize();
}

void PawnReview::setSize(float x, float y)
{
    m_size = QVector2D(x, y);

    resize();
}

void PawnReview::setTitle(QString title)
{
    m_title_review->setTextRender(title);
}

void PawnReview::setPermanentlyInfo(CreatureInfo info)
{
    m_info = info;

    setInfo(m_info);
}

void PawnReview::setMomentInfo(CreatureInfo info)
{
    setInfo(info);
}

void PawnReview::revertToPermanentlyInfo()
{
    setInfo(m_info);
}

void PawnReview::clear()
{
    m_info = CreatureInfo();

    setInfo(m_info);
}

void PawnReview::resize()
{
    // set position
    m_title_review->setPosition(m_position.x() + 10, m_position.y() - 5);

    m_background_1->setPosition(m_position.x(), m_position.y());
    m_background_2->setPosition(m_position.x() + 2, m_position.y() + 2);

    m_pawn->setPosition(m_position.x() + 4, m_position.y() + 4);

    m_map_element_icon->setPosition(m_position.x() + (m_size.x()/4) + 4, m_position.y() + 4);

    float new_y = m_position.y() + m_pawn->getSize().y() + 25;

    m_name->setPosition(m_position.x() + 5, new_y);
    m_health->setPosition(m_position.x() + 5, new_y + 20);
    m_shield->setPosition(m_position.x() + 5, new_y + 40);
    m_attack->setPosition(m_position.x() + 5, new_y + 60);
    m_points_of_move->setPosition(m_position.x() + 5, new_y + 80);

    // set size
    m_background_1->setScale(m_size.x(), m_size.y());
    m_background_2->setScale(m_size.x() - 4, m_size.y() - 4);
    m_pawn->setSize(m_size.x()/4, m_size.y()/4);

    m_map_element_icon->setScale(m_size.x()/4, m_size.y()/4);
}
