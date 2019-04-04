#include "opengl_object.h"

OpenGLObject::OpenGLObject() :
    m_mesh(nullptr),
    m_texture(nullptr)
{
    initializeOpenGLFunctions();

}

OpenGLObject::~OpenGLObject()
{
    if(m_mesh)
        delete m_mesh;

    if(m_texture)
        delete m_texture;
}

/**/

void OpenGLObject::setTexture(I_Texture* texture)
{
    m_texture = texture;
}

void OpenGLObject::setMesh(I_Mesh* mesh)
{
    m_mesh = mesh;
}

void OpenGLObject::setBaseColor(QColor color)
{
    int offset = m_mesh->getOffsetBaseColor();
    int size = sizeof(QVector4D);

    QVector4D color_vector = QVector4D(color.red(), color.green(), color.blue(), color.alpha());

    m_mesh->getVertexBuffer().bind();
    for(int i = 0; i < m_mesh->getCountVertex(); ++i)
    {
        m_mesh->getVertexBuffer().write(offset, &color_vector, size);
        offset += sizeof(QVector4D) + sizeof(QVector2D) + sizeof(QVector3D) + m_mesh->getOffsetBaseColor();
    }
    m_mesh->getVertexBuffer().release();
}

void OpenGLObject::setObjectID(unsigned int id_object)
{
    unsigned int Blue =  (unsigned char)id_object;
    unsigned int Green = (unsigned char)(id_object >> 8);
    unsigned int Red =   (unsigned char)(id_object >> 16);

    QVector3D id_object_vec = QVector3D(Red, Green, Blue);

    int offset = m_mesh->getOffsetObjectID();
    int size = sizeof(QVector3D);

    m_mesh->getVertexBuffer().bind();
    m_mesh->getVertexBuffer().write(offset, &id_object_vec, size);
    m_mesh->getVertexBuffer().release();
}

void OpenGLObject::setTextureRect(int x, int y, int width, int height)
{
    int offset = m_mesh->getOffsetTexCoord();
    int size = sizeof(QVector2D);

    QVector2D cord;

    m_mesh->getVertexBuffer().bind();

    cord = QVector2D((float)(width + x) / (float)m_texture->getWidth(), (float)y / (float)m_texture->getHeight());//(1.0f, 0.0f)
    m_mesh->getVertexBuffer().write(offset, &cord, size);
    offset += m_mesh->getSizeVertexData();

    cord = QVector2D((float)x / (float)m_texture->getWidth(), (float)y / (float)m_texture->getHeight());//(0.0f, 0.0f)
    m_mesh->getVertexBuffer().write(offset, &cord, size);
    offset += m_mesh->getSizeVertexData();

    cord = QVector2D((float)(width + x) / (float)m_texture->getWidth(), (float)(height + y) / (float)m_texture->getHeight()); //(1.0f, 1.0f)
    m_mesh->getVertexBuffer().write(offset, &cord, size);
    offset += m_mesh->getSizeVertexData();

    cord = QVector2D((float)x / (float)m_texture->getWidth(), (float)(height + y) / (float)m_texture->getHeight());//(0.0f, 1.0f)
    m_mesh->getVertexBuffer().write(offset, &cord, size);
    offset += m_mesh->getSizeVertexData();


    m_mesh->getVertexBuffer().release();
}

void OpenGLObject::setVisible(bool visible)
{
    m_visible = visible;
}

/**/

I_Texture* OpenGLObject::getTexture()
{
    return m_texture;
}

I_Mesh* OpenGLObject::getMesh()
{
    return m_mesh;
}

QColor OpenGLObject::getColor(bool* wasOK)
{
    QVector4D color = QVector4D();

    int offset = m_mesh->getOffsetBaseColor();
    int size = sizeof(QVector4D);

    m_mesh->getVertexBuffer().bind();

    if(wasOK)
        *wasOK = m_mesh->getVertexBuffer().read(offset, &color, size);
    else
        m_mesh->getVertexBuffer().read(offset, &color, size);

    m_mesh->getVertexBuffer().release();

    if(wasOK)
    {
        if(!*wasOK)
            return QColor();
    }

    return QColor(color.x(), color.y(), color.z(), color.w());
}

unsigned int OpenGLObject::getObjectID(bool* wasOK)
{
    QVector3D id_object = QVector3D();

    int offset = m_mesh->getOffsetObjectID();
    int size = sizeof(QVector3D);

    m_mesh->getVertexBuffer().bind();

    if(wasOK)
        *wasOK = m_mesh->getVertexBuffer().read(offset, &id_object, size);
    else
        m_mesh->getVertexBuffer().read(offset, &id_object, size);


    m_mesh->getVertexBuffer().release();

    if(wasOK)
    {
        if(!wasOK)
            return 0;
    }

    unsigned int index = ((unsigned int)id_object.x() << 16) | ((unsigned int)id_object.y() << 8) | ((unsigned int)id_object.z());

    return index;
}

TextureRect OpenGLObject::getTextureRect()
{

}

bool OpenGLObject::getVisible()
{
    return m_visible;
}

/**/

bool OpenGLObject::drawGL(Shader *shader)
{
    if(!m_visible)
        return true;

    if(!shader->setMatrixModel(m_model_matrix))
    {
        qDebug() << "setMatrixModel";
        return false;
    }

    if(m_mesh == nullptr)
    {
        qDebug() << "m_mesh == nullptr";
        return false;
    }

    if(!m_mesh->bindMesh())
    {
        qDebug() << "bindMesh";
        return false;
    }

    if(m_texture != nullptr)
    {
        m_texture->bindTexture();

        if(!shader->setTextureID(m_texture->getTextureID()))
        {
            qDebug() << "setTextureID";
        }
        if(!shader->setEnableTexture(true))
        {
            qDebug() << "setEnableTexture";
        }
    }
    else
    {
        if(!shader->setEnableTexture(false))
        {
            qDebug() << "setEnableTexture";
        }
    }

    if(!shader->setLocateVertexAllDate(m_mesh))
    {
        qDebug() << "setLocateVertexAllDate" ;
        return false;
    }

    shader->enableLocateVertexAllDate(true);

    glDrawElements(m_mesh->getMode(), m_mesh->getCountVertex(), GL_UNSIGNED_SHORT, 0);

    shader->enableLocateVertexAllDate(false);

    if(m_texture != nullptr)
    {
        m_texture->releaseTexture();
    }

    if(!m_mesh->releaseMesh())
    {
        qDebug() << "releaseMesh";
        return false;
    }

    return true;
}

bool OpenGLObject::draw(Shader* shader)
{
    return drawGL(shader);
}
