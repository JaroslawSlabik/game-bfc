#include "texture.h"

#include <QFile>

Texture::Texture()
{
    m_texture = nullptr;
}

Texture::Texture(QString path_to_image, bool* was_ok)
{
    m_texture = nullptr;
    if(was_ok)
        *was_ok = loadFromFile(path_to_image);
    else
        loadFromFile(path_to_image);
}

Texture::Texture(QByteArray bytes, bool* was_ok)
{
    m_texture = nullptr;

    if(was_ok)
        *was_ok = loadFromBytes(bytes);
    else
        loadFromBytes(bytes);
}

Texture::Texture(QImage image, bool* was_ok)
{
    m_texture = nullptr;

    if(was_ok)
        *was_ok = loadFromImage(image);
    else
        loadFromImage(image);
}

Texture::~Texture()
{
    delete m_texture;
}

/**/

bool Texture::loadFromFile(const QString& path_to_image, bool horizontal, bool vertical)
{
    if(!QFile::exists(path_to_image))
        return false;

    QFile file(path_to_image);
    if(!file.open(QFile::ReadOnly))
        return false;

    QByteArray bytes = file.readAll();

    file.close();

    return loadFromBytes(bytes, horizontal, vertical);
}

/**/

bool Texture::loadFromBytes(const QByteArray& bytes, bool horizontal, bool vertical)
{
    if(bytes.size() < 5)
        return false;

    return loadFromImage(QImage::fromData(bytes), horizontal, vertical);
}

/**/

bool Texture::loadFromImage(const QImage& image, bool horizontal, bool vertical)
{
    if(image.isNull())
        return false;

    if(m_texture == nullptr)
    {
        m_texture = new QOpenGLTexture(image.mirrored(horizontal, vertical));
        m_id_texture = m_texture->textureId();
        return true;
    }

    delete m_texture;

    m_texture = new QOpenGLTexture(image.mirrored(horizontal, vertical));
    m_id_texture = m_texture->textureId();

    return true;
}

/**/

void Texture::setMinificationFilter(TextureFilter filtr)
{
    if(m_texture != nullptr)
        m_texture->setMinificationFilter(filtr);
}

void Texture::setWrapMode(TextureWrapMode wrap_mode)
{
    if(m_texture != nullptr)
        m_texture->setWrapMode(wrap_mode);
}

I_Texture* Texture::getTexture()
{
    return this;
}
