#include "i_texture.h"
#include <QDebug>
void I_Texture::bindTexture()
{
    if(m_texture != nullptr && m_id_texture > 0)
    {
        m_texture->bind(m_id_texture);
    }
}

void I_Texture::releaseTexture()
{
    if(m_texture != nullptr && m_id_texture > 0)
    {
        m_texture->release(m_id_texture);
    }
}

/**/

int I_Texture::getHeight()
{
    if(m_texture != nullptr && m_id_texture > 0)
    {
        return m_texture->height();
    }

    return -1;
}

int I_Texture::getWidth()
{
    if(m_texture != nullptr && m_id_texture > 0)
    {
        return m_texture->width();
    }

    return -1;
}

unsigned int I_Texture::getTextureID()
{
    return m_id_texture;
}
