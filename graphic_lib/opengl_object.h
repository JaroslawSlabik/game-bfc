#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuaternion>

#include "i_mesh.h"
#include "i_texture.h"
#include "shader.h"

class OpenGLObject : protected QOpenGLFunctions
{
public:
    OpenGLObject();
    virtual ~OpenGLObject();

    /**/

    void setTexture(I_Texture* texture);
    void setMesh(I_Mesh* mesh);
    void setBaseColor(QColor color);
    void setObjectID(unsigned int id_object);
    void setTextureRect(int x, int y, int width, int height);
    void setVisible(bool visible);

    /**/

    I_Texture* getTexture();
    I_Mesh* getMesh();
    QColor getColor(bool* wasOK = nullptr);
    unsigned int getObjectID(bool* wasOK = nullptr);
    TextureRect getTextureRect();
    bool getVisible();

    /**/

    virtual bool pointOnObject(QVector2D point) = 0;

    /**/

    virtual bool draw(Shader* shader);

private:
    I_Mesh* m_mesh;
    I_Texture* m_texture;

protected:
    QMatrix4x4 m_model_matrix;
    bool m_visible = true;

    bool drawGL(Shader* shader);
};

#endif // OPENGL_OBJECT_H
