#include "button.h"
#include <QThread>

#include "plate_mesh.h"

Button::Button(QObject* parent)
{
    m_text_render = new OpenGLTextRender2D;

    this->setMesh(new PlateMesh);

    m_focus = false;
    m_mouse_on_object = false;
}

void Button::setColorClicked(const QColor& color)
{
    m_color_clicked = color;
}

void Button::setColorMoveOn(const QColor& color)
{
    m_color_moved_on = color;
}

void Button::setText(const QString& text, const QVector2D& pos_txt)
{
    m_text = text;
    m_text_render->setTextRender(m_text);
    setTextPosition(pos_txt);
}

void Button::setTextPosition(const QVector2D& pos_txt)
{
    float x = this->getPosition().x() + pos_txt.x();
    float y = this->getPosition().y() + pos_txt.y();

    m_text_render->setPosition(x, y);
}

void Button::setColorText(const QColor& color)
{
    m_text_render->setColorText(color);
}

bool Button::setFont(const QString& font_name, int size)
{
    if(!m_text_render->setFontName(font_name))
        return false;

    if(!m_text_render->setFontSize(size))
        return false;

    return true;
}

QString Button::getText()
{
    return m_text;
}

bool Button::draw(Shader* shader)
{
    if(false == this->getVisible())
    {
        return true;
    }

    if(!this->drawGL(shader))
        return false;

    if(!m_text_render->draw(shader))
        return false;

    if(m_focus )
    {
        m_focus = false;
        QThread::usleep(200);
        if(m_mouse_on_object)
            this->setBaseColor(m_color_moved_on);
        else
            this->setBaseColor(m_color_base);
    }

    return true;
}

void Button::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(false == this->getVisible())
    {
        return;
    }

    if(!m_focus)
    {
        if(this->pointOnObject(pos))
        {
            if(m_mouse_on_object == false)
            {
                m_color_base = this->getColor();
                this->setBaseColor(m_color_moved_on);
                m_mouse_on_object = true;
                emit moveOn();
            }

            if(type == QEvent::MouseButtonRelease && button == Qt::MouseButton::LeftButton)
            {
                m_focus = true;
                this->setBaseColor(m_color_clicked);
                emit clicked();
            }
        }
        else
        {
            if(m_mouse_on_object == true)
            {
                m_mouse_on_object = false;
                this->setBaseColor(m_color_base);
            }
        }
    }
}

void Button::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}
