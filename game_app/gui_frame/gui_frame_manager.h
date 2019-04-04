#ifndef I_GUI_FRAME_MANAGER_H
#define I_GUI_FRAME_MANAGER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

#include "i_gui_frame.h"

class GUIFrameManager : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    enum Frame
    {
        loginFrame = 0,
        RegistrationFrame,
        mainWindowFrame,
        prepareToGrameFrame,
        gameFrame,
        endGameFrame,
        count
    };

    explicit GUIFrameManager(Frame start_frame, QWidget *parent = 0);
    ~GUIFrameManager();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QBasicTimer timer;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    Shader shader;

    Frame m_frame_id_in_use;
    QMap<Frame, I_GUIFrame*> m_map_frame;

    void makeConnects();
    void destroyConnects();

signals:
    void mouseEvent(QEvent::Type, QVector2D, Qt::MouseButton);
    void keyboardEvent(QEvent::Type, Qt::Key, QString);
    void sendToServer(const QString& query);
    void responseFromServer(const QString& response);

public slots:
    void receiveFromServer(const QString& response);
    void serverConnected();
    void serverDisconnected();

private slots:
    void nextFrame();
    void backFrame();
    void skipToFrame(const int& id);
    void queryToServer(const QString& query);
};

#endif //I_GUI_FRAME_MANAGER_H
