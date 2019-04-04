#include "gui_frame_manager.h"

#include "gui_frame_login.h"
#include "gui_frame_main_window.h"
#include "gui_frame_preparation_for_game.h"
#include "gui_frame_game.h"
#include "gui_frame_registration.h"
#include "gui_frame_end_game.h"

#include <QTimer>

GUIFrameManager::GUIFrameManager(Frame start_frame, QWidget *parent)
{
    m_frame_id_in_use = start_frame;

    if(m_frame_id_in_use == Frame::count)
        m_frame_id_in_use = static_cast<Frame>(0);

    setMouseTracking(true);
}

GUIFrameManager::~GUIFrameManager()
{

}

void GUIFrameManager::mousePressEvent(QMouseEvent *e)
{
    emit mouseEvent(QEvent::Type::MouseButtonPress, QVector2D(e->localPos()), e->button());
}

void GUIFrameManager::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit mouseEvent(QEvent::Type::MouseButtonDblClick, QVector2D(e->localPos()), e->button());
}

void GUIFrameManager::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseEvent(QEvent::Type::MouseButtonRelease, QVector2D(e->localPos()), e->button());
}

void GUIFrameManager::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseEvent(QEvent::Type::MouseMove, QVector2D(e->localPos()), e->button());
}

void GUIFrameManager::keyPressEvent(QKeyEvent *event)
{
    emit keyboardEvent(QEvent::Type::KeyPress, static_cast<Qt::Key>(event->key()), event->text());
}

void GUIFrameManager::keyReleaseEvent(QKeyEvent *event)
{
    emit keyboardEvent(QEvent::Type::KeyRelease, static_cast<Qt::Key>(event->key()), event->text());
}

void GUIFrameManager::timerEvent(QTimerEvent *)
{
    view.setToIdentity();

    view.translate(1, 1.0, 0.0); // Dla Orho
}

void GUIFrameManager::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    // Enable depth buffer
    //glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //wczytanie shaderów
    if(!shader.loadFromFile(":/vshader.glsl",":/fshader.glsl"))
        qDebug() << "EEEE" ;

    m_map_frame.insert(Frame::loginFrame, new GUIFrameLogin(this));
    m_map_frame.insert(Frame::RegistrationFrame, new GUIFrameRegistration(this));
    m_map_frame.insert(Frame::mainWindowFrame, new GUIFrameMainWindow(this));
    m_map_frame.insert(Frame::prepareToGrameFrame, new GUIFramePreparationForGame(this));
    m_map_frame.insert(Frame::gameFrame, new GUIFrameGame(this));
    m_map_frame.insert(Frame::endGameFrame, new GUIFrameEndGame(this));


    m_map_frame.value(m_frame_id_in_use)->initialize();

    skipToFrame(m_frame_id_in_use);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void GUIFrameManager::resizeGL(int w, int h)
{
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection for 3D
    // Calculate aspect ratio
    //qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    //projection.perspective(fov, aspect, zNear, zFar);

    // Set perspective projection for 2D
    projection.ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

}

void GUIFrameManager::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);


    //bind shader
    shader.bindShader();

    //set matrix projection and view
    if(!shader.setMatrixProjection(projection))
        qDebug() << "222";
    if(!shader.setMatrixView(view))
        qDebug() << "222";

    m_map_frame.value(m_frame_id_in_use)->draw(&shader);

    //relase shader
    shader.releaseShader();

    update(); // to trzeba optymalizować wywoływac np 20 razy na sekundę(20FPS)
}

void GUIFrameManager::nextFrame()
{
    if(m_frame_id_in_use + 1 >= Frame::count)
        return;

    m_map_frame.value(m_frame_id_in_use)->hide();
    destroyConnects();
    m_map_frame.value(m_frame_id_in_use)->deinitialize();

    m_frame_id_in_use = static_cast<Frame>(m_frame_id_in_use + 1);

    m_map_frame.value(m_frame_id_in_use)->initialize();
    makeConnects();
    m_map_frame.value(m_frame_id_in_use)->show();
}

void GUIFrameManager::backFrame()
{
    if(m_frame_id_in_use == 0)
        return;

    m_map_frame.value(m_frame_id_in_use)->hide();
    destroyConnects();
    m_map_frame.value(m_frame_id_in_use)->deinitialize();

    m_frame_id_in_use = static_cast<Frame>(m_frame_id_in_use - 1);

    m_map_frame.value(m_frame_id_in_use)->initialize();
    makeConnects();
    m_map_frame.value(m_frame_id_in_use)->show();
}

void GUIFrameManager::skipToFrame(const int& id)
{
    if(id < 0 || id >= Frame::count)
        return;

    m_map_frame.value(m_frame_id_in_use)->hide();
    destroyConnects();
    m_map_frame.value(m_frame_id_in_use)->deinitialize();

    m_frame_id_in_use = static_cast<Frame>(id);

    m_map_frame.value(m_frame_id_in_use)->initialize();
    makeConnects();
    m_map_frame.value(m_frame_id_in_use)->show();
}

void GUIFrameManager::makeConnects()
{
    connect(this, SIGNAL(mouseEvent(QEvent::Type, QVector2D, Qt::MouseButton)), m_map_frame.value(m_frame_id_in_use), SLOT(mouseEventRec(QEvent::Type, QVector2D, Qt::MouseButton)));
    connect(this, SIGNAL(keyboardEvent(QEvent::Type, Qt::Key, QString)), m_map_frame.value(m_frame_id_in_use), SLOT(kayboardEventRec(QEvent::Type, Qt::Key, QString)));
    connect(this, SIGNAL(responseFromServer(QString)), m_map_frame.value(m_frame_id_in_use), SLOT(receiveFromServer(QString)));
    connect(m_map_frame.value(m_frame_id_in_use), SIGNAL(sendToServer(QString)), this, SLOT(queryToServer(QString)));
    connect(m_map_frame.value(m_frame_id_in_use), SIGNAL(nextFrame()), this, SLOT(nextFrame()));
    connect(m_map_frame.value(m_frame_id_in_use), SIGNAL(backFrame()), this, SLOT(backFrame()));
    connect(m_map_frame.value(m_frame_id_in_use), SIGNAL(skipToFrame(int)), this, SLOT(skipToFrame(int)));
}

void GUIFrameManager::destroyConnects()
{
    disconnect(this, SIGNAL(mouseEvent(QEvent::Type, QVector2D, Qt::MouseButton)), m_map_frame.value(m_frame_id_in_use), SLOT(mouseEventRec(QEvent::Type, QVector2D, Qt::MouseButton)));
    disconnect(this, SIGNAL(keyboardEvent(QEvent::Type, Qt::Key, QString)), m_map_frame.value(m_frame_id_in_use), SLOT(kayboardEventRec(QEvent::Type, Qt::Key, QString)));
    disconnect(this, SIGNAL(responseFromServer(QString)), m_map_frame.value(m_frame_id_in_use), SLOT(receiveFromServer(QString)));
    disconnect(m_map_frame.value(m_frame_id_in_use), SIGNAL(sendToServer(QString)), this, SLOT(queryToServer(QString)));
    disconnect(m_map_frame.value(m_frame_id_in_use), SIGNAL(nextFrame()), this, SLOT(nextFrame()));
    disconnect(m_map_frame.value(m_frame_id_in_use), SIGNAL(backFrame()), this, SLOT(backFrame()));
    disconnect(m_map_frame.value(m_frame_id_in_use), SIGNAL(skipToFrame(int)), this, SLOT(skipToFrame(int)));
}

void GUIFrameManager::receiveFromServer(const QString& response)
{
    emit responseFromServer(response);
}

void GUIFrameManager::queryToServer(const QString& query)
{
    emit sendToServer(query);
}

void GUIFrameManager::serverConnected()
{

}

void GUIFrameManager::serverDisconnected()
{

}
