#include "pawn.h"

#include "plate_mesh.h"

Pawn::Pawn(QObject* parent)
{
    m_background = new OpenGLObject2D();
    m_background->setMesh(new PlateMesh());
    m_background->setBaseColor(QColor(123, 123,123, 50));

    m_health_bar = new ProgresBar();
    m_health_bar->setColorBackground(QColor(255, 0, 0));
    m_health_bar->setColorStatus(QColor(0, 255, 0));

    m_shield_bar = new ProgresBar();
    m_shield_bar->setColorBackground(QColor(255, 0, 0));
    m_shield_bar->setColorStatus(QColor(0, 0, 255));

    m_creature = new Creature();

    m_element_icon = new ElementIcon();
}

Pawn::Pawn(CreatureInfo info, QObject* parent)
{
    m_background = new OpenGLObject2D();
    m_background->setMesh(new PlateMesh());
    m_background->setBaseColor(QColor(123, 123,123, 50));

    m_health_bar = new ProgresBar();
    m_health_bar->setColorBackground(QColor(255, 0, 0));
    m_health_bar->setColorStatus(QColor(0, 255, 0));

    m_shield_bar = new ProgresBar();
    m_shield_bar->setColorBackground(QColor(255, 0, 0));
    m_shield_bar->setColorStatus(QColor(0, 0, 255));

    m_element_icon = new ElementIcon();

    m_creature = new Creature();

    setInfo(info);
}

void Pawn::setPosition(float x, float y)
{
    m_position = QVector2D(x, y);

    resize();
}

void Pawn::setSize(float x, float y)
{
    m_size = QVector2D(x, y);

    resize();
}

QVector2D Pawn::getSize()
{
    return m_size;
}

CreatureInfo Pawn::getInfo()
{
    return m_creature->getInfo();
}

void Pawn::setInfo(CreatureInfo info)
{
    m_creature->setInfo(info);
    m_element_icon->setElement(info.m_element);

    m_health_bar->setStatus(static_cast<float>(info.m_actual_health) / static_cast<float>(info.m_health));

    m_shield_bar->setStatus(static_cast<float>(info.m_actual_shield) / static_cast<float>(info.m_shield));
}

bool Pawn::draw(Shader *shader)
{
    m_background->draw(shader);

    m_creature->draw(shader);

    m_element_icon->draw(shader);

    m_health_bar->draw(shader);

    m_shield_bar->draw(shader);

    return false;
}

void Pawn::resize()
{
    m_background->setPosition(m_position);
    m_background->setScale(m_size);

    m_creature->setPosition(m_position.x() + ((m_size.x() * 0.25f) * 0.5f), m_position.y() + ((m_size.y() * 0.25f) * 0.5f));
    m_creature->setScale(m_size.x() * 0.75f, m_size.y() * 0.75f);

    m_element_icon->setPosition(m_position.x() + m_size.x() - (m_size.x() * 0.25f) - (m_size.x() * 0.01f), m_position.y() + (m_size.y() * 0.01f));
    m_element_icon->setScale(m_size.x() * 0.25f, m_size.y() * 0.25f);

    m_health_bar->setPosition(QVector2D(m_position.x() + (m_size.x() * 0.01f), m_creature->getPosition().y() + m_creature->getScale().y()));
    m_health_bar->setSize(QVector2D(m_size.x() - ((m_size.x() * 0.01f) * 2),  (m_size.y() * 0.05f)));

    m_shield_bar->setPosition(QVector2D(m_position.x() + (m_size.x() * 0.01f), m_creature->getPosition().y() + m_creature->getScale().y() + (m_size.y() * 0.05f)));
    m_shield_bar->setSize(QVector2D(m_size.x() - ((m_size.x() * 0.01f) * 2),  (m_size.y() * 0.05f)));
}
