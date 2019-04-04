#ifndef SHADER_H
#define SHADER_H
#include <QOpenGLShaderProgram>
#include "i_mesh.h"


class Shader
{
public:
    Shader();
    Shader(QString vertexShader, QString fragmentShader);
    Shader(QString vertexShader, QString fragmentShader, bool& wasOK);
    ~Shader();

    bool loadFromFile(QString vertexShader, QString fragmentShader);
    bool bindShader();
    void releaseShader();

    bool setMatrixProjection(QMatrix4x4 matrix_projection);
    bool setMatrixView(QMatrix4x4 matrix_view);
    bool setMatrixModel(QMatrix4x4 matrix_model);
    bool setTextureID(unsigned int id_texture);
    bool setEnableTexture(bool enable);
    bool setEnableFont(bool enable);
    bool setLocateVertexPositionData(I_Mesh* mesh);
    bool setLocateVertexTextureCoordinateData(I_Mesh* mesh);
    bool setLocateVertexColorData(I_Mesh* mesh);
    bool setLocateVertexAllDate(I_Mesh* mesh);

    void enableLocateVertexAllDate(bool enable);


private:
    QOpenGLShaderProgram program;
    int m_vertexLocation = -1;
    int m_texcoordLocation = -1;
    int m_baseColorLocation = -1;
    bool m_enable = false;

    bool readAllLocation();
    void clearAllLocation();
};

#endif // SHADER_H
