#include "shader.h"

Shader::Shader()
{

}

Shader::Shader(QString vertexShader, QString fragmentShader)
{
    loadFromFile(vertexShader, fragmentShader);
}

Shader::Shader(QString vertexShader, QString fragmentShader, bool& wasOK)
{
    wasOK = loadFromFile(vertexShader, fragmentShader);
}

Shader::~Shader()
{

}

/**/

bool Shader::loadFromFile(QString vertexShader, QString fragmentShader)
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShader))
        return false;

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShader))
        return false;

    if (!program.link())
        return false;

    return bindShader();
}

bool Shader::bindShader()
{
    if(!program.bind())
        return false;

    return readAllLocation();
}

void Shader::releaseShader()
{
    clearAllLocation();

    program.release();
}

/**/

bool Shader::setMatrixProjection(QMatrix4x4 matrix_projection)
{
    int matrixProjectionLocation = program.uniformLocation("u_matrix_projection");
    if(matrixProjectionLocation == -1)
        return false;

    program.setUniformValue(matrixProjectionLocation, matrix_projection);

    return true;
}

bool Shader::setMatrixView(QMatrix4x4 matrix_view)
{
    int matrixViewLocation = program.uniformLocation("u_matrix_view");
    if(matrixViewLocation == -1)
        return false;

    program.setUniformValue(matrixViewLocation, matrix_view);

    return true;
}

bool Shader::setMatrixModel(QMatrix4x4 matrix_model)
{
    int matrixModelLocation = program.uniformLocation("u_matrix_model");
    if(matrixModelLocation == -1)
        return false;

    program.setUniformValue(matrixModelLocation, matrix_model);

    return true;
}

bool Shader::setTextureID(unsigned int id_texture)
{
    int textureLocation = program.uniformLocation("u_texture");
    if(textureLocation == -1)
        return false;

    program.setUniformValue(textureLocation, id_texture);

    return true;
}

bool Shader::setEnableTexture(bool enable)
{
    int no_texture_Location = program.uniformLocation("u_no_texture");
    if(no_texture_Location == -1)
        return false;

    if(enable)
        program.setUniformValue(no_texture_Location, QVector4D(0,0,0,0));
    else
        program.setUniformValue(no_texture_Location, QVector4D(1,1,1,1));

    return true;
}

bool Shader::setEnableFont(bool enable)
{
    int u_font_Location = program.uniformLocation("u_font");
    if(u_font_Location == -1)
        return false;

    if(enable)
        program.setUniformValue(u_font_Location, 1.0f);
    else
        program.setUniformValue(u_font_Location, 0.0f);

    return true;
}

bool Shader::setLocateVertexPositionData(I_Mesh* mesh)
{
    if(mesh == nullptr)
        return false;

    program.setAttributeBuffer(m_vertexLocation, GL_FLOAT, mesh->getOffsetPosition(), mesh->getSizePosition(), mesh->getSizeVertexData());

    return true;
}

bool Shader::setLocateVertexTextureCoordinateData(I_Mesh* mesh)
{
    if(mesh == nullptr)
        return false;

    program.setAttributeBuffer(m_texcoordLocation, GL_FLOAT, mesh->getOffsetTexCoord(), mesh->getSizeTexCoord(), mesh->getSizeVertexData());

    return true;
}

bool Shader::setLocateVertexColorData(I_Mesh* mesh)
{
    if(mesh == nullptr)
        return false;

    program.setAttributeBuffer(m_baseColorLocation, GL_FLOAT, mesh->getOffsetBaseColor(), mesh->getSizeBaseColor(), mesh->getSizeVertexData());
    return true;
}

bool Shader::setLocateVertexAllDate(I_Mesh* mesh)
{
    if(mesh == nullptr)
        return false;

    program.setAttributeBuffer(m_baseColorLocation, GL_FLOAT, mesh->getOffsetBaseColor(), mesh->getSizeBaseColor(), mesh->getSizeVertexData());
    program.setAttributeBuffer(m_texcoordLocation,  GL_FLOAT, mesh->getOffsetTexCoord(),  mesh->getSizeTexCoord(),  mesh->getSizeVertexData());
    program.setAttributeBuffer(m_vertexLocation,    GL_FLOAT, mesh->getOffsetPosition(),  mesh->getSizePosition(),  mesh->getSizeVertexData());

    return true;
}

void Shader::enableLocateVertexAllDate(bool enable)
{
    if(m_enable == enable)
        return;

    if(enable)
    {
        program.enableAttributeArray(m_vertexLocation);
        program.enableAttributeArray(m_texcoordLocation);
        program.enableAttributeArray(m_baseColorLocation);
        m_enable = enable;
    }
    else
    {
        program.enableAttributeArray(m_baseColorLocation);
        program.enableAttributeArray(m_texcoordLocation);
        program.enableAttributeArray(m_vertexLocation);
        m_enable = enable;
    }
}

bool Shader::readAllLocation()
{
    //jeśli lokalizacja jest wczytan (loc != -1) to znaczy że ten program już jest zbindowany
    if(m_vertexLocation != -1)
        return false;

    if(m_texcoordLocation != -1)
        return false;

    if(m_baseColorLocation != -1)
        return false;

    //jeśli po wczytaniu lokalizacji nadal jest -1 to znaczy że nie udalo sie wczytac lokalizację
    m_vertexLocation = program.attributeLocation("a_position");
    if(m_vertexLocation == -1)
        return false;

    m_texcoordLocation = program.attributeLocation("a_texcoord");
    if(m_texcoordLocation == -1)
        return false;

    m_baseColorLocation = program.attributeLocation("a_base_color");
    if(m_baseColorLocation == -1)
        return false;

    return true;
}
void Shader::clearAllLocation()
{
    m_vertexLocation = -1;
    m_texcoordLocation = -1;
    m_baseColorLocation = -1;
}


