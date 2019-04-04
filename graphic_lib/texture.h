#ifndef TEXTURE_H
#define TEXTURE_H
#include "i_texture.h"

typedef QOpenGLTexture::Filter TextureFilter;
typedef QOpenGLTexture::WrapMode TextureWrapMode;


class Texture : public I_Texture
{
public:
    Texture();
    Texture(QString path_to_image, bool* was_ok = nullptr);
    Texture(QByteArray bytes, bool* was_ok = nullptr);
    Texture(QImage image, bool* was_ok = nullptr);
    ~Texture();

    /**/

    bool loadFromFile(const QString& path_to_image, bool horizontal = false, bool vertical = true);
    bool loadFromBytes(const QByteArray& bytes, bool horizontal = false, bool vertical = true);
    bool loadFromImage(const QImage& image, bool horizontal = false, bool vertical = true);

    /**/

    void setMinificationFilter(TextureFilter filtr);
    void setWrapMode(TextureWrapMode wrap_mode);

    /**/

    I_Texture* getTexture();
};

#endif // TEXTURE_H
