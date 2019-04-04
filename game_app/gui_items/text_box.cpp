#include "text_box.h"
#include "plate_mesh.h"

TextBox::TextBox(QObject* parent)
{
    m_text_render = new OpenGLTextRender2D;
    m_text_label = new OpenGLTextRender2D;

    this->setMesh(new PlateMesh);

    m_max_lenght = std::numeric_limits<int>::max();

    m_focus = false;
    m_mouse_on_object = false;
}

void TextBox::setColorClicked(const QColor& color)
{
    m_color_clicked = color;
}

void TextBox::setColorMoveOn(const QColor& color)
{
    m_color_moved_on = color;
}

void TextBox::setText(const QString& text)
{
    m_text = text;

    QString text_to_draw = "";
    if(!m_char_mask.isNull())
        text_to_draw.fill(m_char_mask, m_text.length());
    else
        text_to_draw = m_text;

    m_text_render->setTextRender(text_to_draw);
}

QString TextBox::getText()
{
    return m_text;
}

bool TextBox::setFont(const QString& font_name, int size)
{
    if(!m_text_render->setFontName(font_name))
        return false;

    if(!m_text_label->setFontName(font_name))
        return false;

    m_size_top_in_pixels = 0;
    m_size_bottom_in_pixels = 0;
    if(!m_text_render->setFontSize(size, m_size_top_in_pixels, m_size_bottom_in_pixels))
        return false;

    this->setScale((this->getScale().x() <= 1.0f)? 1.0f : this->getScale().x(), m_size_top_in_pixels - m_size_bottom_in_pixels);

    if(!m_text_label->setFontSize(size))
        return false;

    return true;
}

void TextBox::setColorText(const QColor& color)
{
    m_text_render->setColorText(color);
}

void TextBox::setMaskChar(const QChar& char_mask)
{
    m_char_mask = char_mask;
}

void TextBox::setMaxLenght(int lenght)
{
    if(lenght < 1)
        lenght = 0;

    m_max_lenght = lenght;
}

void TextBox::setColorLabel(const QColor& color)
{
    m_text_label->setColorText(color);
}

void TextBox::setTextLabel(const QString& text, const QVector2D& pos)
{
    m_text_label->setTextRender(text);
    setTextPositionLabel(pos);
}

void TextBox::setTextPositionLabel(const QVector2D& pos)
{
    float x = this->getPosition().x() + pos.x();
    float y = this->getPosition().y() + pos.y();

    m_text_label->setPosition(x, y);
}

bool TextBox::draw(Shader* shader)
{
    m_text_render->setPosition(this->getPosition().x(), this->getPosition().y() + m_size_top_in_pixels - 2);

    if(!this->drawGL(shader))
        return false;

    if(!m_text_render->draw(shader))
        return false;

    if(!m_text_label->draw(shader))
        return false;

    return true;
}

void TextBox::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
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
    else
    {
        if(type == QEvent::MouseButtonRelease && button == Qt::MouseButton::LeftButton && !this->pointOnObject(pos))
        {
            m_focus = false;
            this->setBaseColor(m_color_base);
        }
    }
}

void TextBox::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    if(type == QEvent::KeyRelease && m_focus)
    {
        if(key != Qt::Key::Key_Backspace)
        {
            if(m_max_lenght >= m_text.length() + text.length())
            {
                m_text += text;
                QString text_to_draw = "";
                if(!m_char_mask.isNull())
                    text_to_draw.fill(m_char_mask, m_text.length());
                else
                    text_to_draw = m_text;
                m_text_render->setTextRender(text_to_draw);
                emit changed();
            }
        }
        else
        {
            if(m_text.length() >= 1)
            {
                m_text.chop(1);
                QString text_to_draw = "";
                if(!m_char_mask.isNull())
                    text_to_draw.fill(m_char_mask, m_text.length());
                else
                    text_to_draw = m_text;
                m_text_render->setTextRender(text_to_draw);
                emit changed();
            }
        }
    }
}
