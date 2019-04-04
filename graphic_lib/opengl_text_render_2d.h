#ifndef OPENGL_TEXT_RENDER_2D_H
#define OPENGL_TEXT_RENDER_2D_H

#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TYPES_H
#include FT_OUTLINE_H
#include FT_RENDER_H

#include "opengl_object_2d.h"

class OpenGLTextRender2D : public OpenGLObject2D
{
public:
    OpenGLTextRender2D();
    OpenGLTextRender2D(const QString& font_name, int size, const QString& text, const QColor& color = QColor());
    ~OpenGLTextRender2D();

    bool setFontName(const QString& font_name);
    bool setFontSize(int size);
    bool setFontSize(int size, int& size_top_in_px,int& size_bottom_in_px);
    void setTextRender(const QString& text);
    void setColorText(const QColor& color);

    FT_Face getFontFace();
    QString getTextRender();

    virtual bool draw(Shader* shader) override;

private:

    bool init();
    void closeFreeType();
    void closeFont();

    bool m_freetype_init = false;
    bool m_font_face_init = false;

    QFont m_font;
    QColor m_color = QColor(255,255,255);
    QString m_text;
    FT_Face m_font_face;
    FT_Library m_freetype;
    QRect m_glyphRect;
};

#endif // OPENGL_TEXT_RENDER_2D_H
