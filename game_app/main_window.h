#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

#include "texture.h"
#include "shader.h"
#include "opengl_object_3d.h"
#include "opengl_object_2d.h"

#include "gui_items/game_map.h"

#include "gui_items/power_icon.h"

#include "gui_items/progres_bar.h"

#include "gui_items/scroll_bar_heroes.h"

#include "opengl_text_render_2d.h"

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:
    QBasicTimer timer;
    Shader shader;

    QOpenGLTexture *texture;
    QOpenGLTexture *texture2;
    Texture* texture3;

    OpenGLObject2D* object;
    ElementIcon* power_icon;
    ProgresBar* progres_bar;
    ScrollBarHeroes* dcroll_heroes;
    OpenGLTextRender2D* text_render;

    QMatrix4x4 projection;
    QMatrix4x4 view;

    QEvent::Type mouseEventType;
    QVector2D mousePosition;
    Qt::MouseButton mouseButton;

    QVector2D mousePressPosition;

    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    GameMap mapa;

signals:
    void mouseEvent(QEvent::Type, QVector2D, Qt::MouseButton);

private slots:
    void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button);
    void clickedElementMap(int x, int y);
    void selectedHeroId(unsigned int id);


};

#endif // MAINWIDGET_H
