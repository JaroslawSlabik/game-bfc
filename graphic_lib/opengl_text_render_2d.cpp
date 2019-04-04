#include "opengl_text_render_2d.h"

#include <QFile>

#include "texture.h"
#include "plate_mesh.h"
#include "opengl_object_2d.h"

#define TRUNC(x) ((x) >> 6)

OpenGLTextRender2D::OpenGLTextRender2D()
{
    init();
}

OpenGLTextRender2D::OpenGLTextRender2D(const QString& font_name, int size, const QString& text, const QColor& color)
{
    init();

    setFontName(font_name);
    setFontSize(size);
    setTextRender(text);
    setColorText(color);
}

OpenGLTextRender2D::~OpenGLTextRender2D()
{
    closeFont();

    closeFreeType();
}

bool OpenGLTextRender2D::init()
{
    FT_Error error = FT_Init_FreeType(&m_freetype);
    if(error != FT_Err_Ok) // 0 jest interpretowane jako sukces
    {
        m_freetype_init = false;
        qDebug() << "Init FreeType falied";
        return false;
    }

    m_freetype_init = true;

    this->setMesh(new PlateMesh());

    return true;
}

void OpenGLTextRender2D::closeFreeType()
{
    if(m_freetype_init)
    {
        FT_Done_FreeType(m_freetype);
        m_freetype_init = false;
    }
}

void OpenGLTextRender2D::closeFont()
{
    if(m_font_face_init)
    {
        FT_Done_Face(m_font_face);
        m_font_face_init = false;
    }
}

bool OpenGLTextRender2D::setFontName(const QString& font_name)
{
    FT_Error error = FT_Err_Ok;

    if(!m_freetype_init)
        return false;

    closeFont();

    bool was_ok = QFile::exists(font_name);
    if(!was_ok)
        return false;

    error = FT_New_Face(m_freetype, font_name.toStdString().c_str(), 0, &m_font_face);
    if(error != FT_Err_Ok)
        return false;

    m_font_face_init = true;

    return setFontSize(10);
}

bool OpenGLTextRender2D::setFontSize(int size)
{
    FT_Error error = FT_Err_Ok;

    if(!m_font_face_init)
        return false;

    error = FT_Set_Char_Size(m_font_face, size << 6, size << 6, 96, 96);
    if(error != FT_Err_Ok)
        return false;

    return true;
}

bool OpenGLTextRender2D::setFontSize(int size, int& size_top_in_px,int& size_bottom_in_px)
{
    if(!setFontSize(size))
        return false;

    //próbkowanie wielkości czcionki w pixelach
    FT_UInt glyph_index = FT_Get_Char_Index(m_font_face, 'J');

    FT_Error error = FT_Load_Glyph(m_font_face, glyph_index, FT_LOAD_DEFAULT);
    if(error != FT_Err_Ok)
        return false;

    size_top_in_px = TRUNC(m_font_face->size->metrics.ascender);

    glyph_index = FT_Get_Char_Index(m_font_face, 'j');

    error = FT_Load_Glyph(m_font_face, glyph_index, FT_LOAD_DEFAULT);
    if(error != FT_Err_Ok)
        return false;

    size_bottom_in_px = TRUNC(m_font_face->size->metrics.descender);

    return true;
}

void OpenGLTextRender2D::setTextRender(const QString& text)
{
    m_text = text;
}

void OpenGLTextRender2D::setColorText(const QColor& color)
{
    m_color = color;
}

FT_Face OpenGLTextRender2D::getFontFace()
{
    return  m_font_face;
}

QString OpenGLTextRender2D::getTextRender()
{
    return m_text;
}

bool OpenGLTextRender2D::draw(Shader* shader)
{
    if(!m_visible)
        return true;

    if(!m_font_face_init || !m_freetype_init)
        return false;

    FT_Error error = FT_Err_Ok;
    bool was_ok = false;

    FT_UInt glyph_index = 0;

    QVector2D pos = this->getPosition();

    for(QString::const_iterator it = m_text.begin(); it != m_text.end(); ++it)
    {
        glyph_index = FT_Get_Char_Index(m_font_face, it->unicode());

        error = FT_Load_Glyph(m_font_face, glyph_index, FT_LOAD_DEFAULT);
        if(error != FT_Err_Ok)
            return false;

        FT_Pos left = m_font_face->glyph->metrics.horiBearingX;
        FT_Pos right = left + m_font_face->glyph->metrics.width;
        FT_Pos top = m_font_face->glyph->metrics.horiBearingY;
        FT_Pos bottom = top - m_font_face->glyph->metrics.height;

        m_glyphRect = QRect(QPoint(TRUNC(left), -TRUNC(top) + 1), QSize(TRUNC(right - left) + 1, TRUNC(top - bottom) + 1));

        error = FT_Render_Glyph(m_font_face->glyph, FT_RENDER_MODE_NORMAL);
        if(error != FT_Err_Ok)
            return false;

        QImage glyphImage(m_font_face->glyph->bitmap.buffer,
                          static_cast<int>(m_font_face->glyph->bitmap.width),
                          static_cast<int>(m_font_face->glyph->bitmap.rows),
                          m_font_face->glyph->bitmap.pitch,
                          QImage::Format_Indexed8);

        Texture texture(glyphImage, &was_ok);
        // jeśli nie udało to  wstaw przerwę o szerokości litery 'k'
        if(!was_ok)
        {
            glyph_index = FT_Get_Char_Index(m_font_face, 'k');

            error = FT_Load_Glyph(m_font_face, glyph_index, FT_LOAD_DEFAULT);
            if(error != FT_Err_Ok)
                return false;

            FT_Pos left = m_font_face->glyph->metrics.horiBearingX;
            FT_Pos right = left + m_font_face->glyph->metrics.width;
            FT_Pos top = m_font_face->glyph->metrics.horiBearingY;
            FT_Pos bottom = top - m_font_face->glyph->metrics.height;

            m_glyphRect = QRect(QPoint(TRUNC(left), -TRUNC(top) + 1), QSize(TRUNC(right - left) + 1, TRUNC(top - bottom) + 1));

            pos.setX(pos.x() + m_glyphRect.width());
            continue;
        }

        pos.setX(pos.x() + m_glyphRect.x());

        OpenGLObject2D object;
        object.setMesh(new PlateMesh());
        object.setTexture(texture.getTexture());
        object.setBaseColor(m_color);
        object.setPosition(QVector2D(pos.x(), pos.y() + m_glyphRect.y()));
        object.setScale(QVector2D(texture.getTexture()->getWidth(), texture.getTexture()->getHeight()));

        pos = QVector2D(pos.x() + m_glyphRect.width(), pos.y());

        was_ok = shader->setEnableFont(true);
        if(!was_ok)
            return false;

        was_ok = object.draw(shader);
        if(!was_ok)
            return false;

        was_ok = shader->setEnableFont(false);
        if(!was_ok)
            return false;
    }

    was_ok = drawGL(shader);

    return was_ok;
}
