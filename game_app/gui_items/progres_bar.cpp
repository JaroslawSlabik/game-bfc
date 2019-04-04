#include "progres_bar.h"

#include "plate_mesh.h"

ProgresBar::ProgresBar()
{
    m_background = new OpenGLObject2D();
    m_status = new OpenGLObject2D();

    m_background->setMesh(new PlateMesh());
    m_status->setMesh(new PlateMesh());
}

ProgresBar::ProgresBar(float status, const QVector2D& pos, const QVector2D& size)
{
    m_background = new OpenGLObject2D();
    m_status = new OpenGLObject2D();

    m_background->setMesh(new PlateMesh());
    m_status->setMesh(new PlateMesh());

    setStatus(status);
    setPosition(pos);
    setSize(size);
}

ProgresBar::~ProgresBar()
{
    if(m_background)
        delete m_background;

    if(m_status)
        delete m_status;
}

bool ProgresBar::setStatus(float status)
{
    if(status >= 0.f && status <= 1.f)
    {
        m_actual_status = status;
        m_status->setScale(m_lenght * m_actual_status, m_status->getScale().y());
        return true;
    }

    return false;
}

void ProgresBar::setPosition(const QVector2D& pos)
{
    m_background->setPosition(pos);
    m_status->setPosition(pos);
}

void ProgresBar::setSize(const QVector2D& size)
{
    m_lenght = size.x();
    m_background->setScale(size);
    m_status->setScale(size.x(), size.y());

    setStatus(m_actual_status);
}

void ProgresBar::setTextureBackground(I_Texture* texture)
{
    m_background->setTexture(texture);
}

void ProgresBar::setTextureStatus(I_Texture* texture)
{
    m_status->setTexture(texture);
}

void ProgresBar::setColorBackground(const QColor& color)
{
    m_background->setBaseColor(color);
}

void ProgresBar::setColorStatus(const QColor& color)
{
    m_status->setBaseColor(color);
}

float ProgresBar::getStatus()
{
    return m_actual_status;
}

bool ProgresBar::draw(Shader *shader)
{
    m_background->draw(shader);
    m_status->draw(shader);

    return true;
}
