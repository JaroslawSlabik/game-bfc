#ifndef I_TEXTURE_H
#define I_TEXTURE_H
#include <QOpenGLTexture>

struct TextureRect
{
    int x;
    int y;
    int size;
    int height;
};

class I_Texture
{
protected:
    unsigned int m_id_texture = 0;
    QOpenGLTexture* m_texture;

public:
    virtual void bindTexture();
    virtual void releaseTexture();

    /**/

    virtual int getHeight();
    virtual int getWidth();
    virtual unsigned int getTextureID();
};

#endif // I_TEXTURE_H
