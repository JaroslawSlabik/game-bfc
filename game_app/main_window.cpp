#include "main_window.h"

#include <QMouseEvent>
#include <QDir>

#include <math.h>

#include "boxmesh.h"
#include "plate_mesh.h"
#include "opengl_object_2d.h"


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    texture(0),
    texture2(0),
    angularSpeed(0)
{
    connect(this, SIGNAL(mouseEvent(QEvent::Type,QVector2D,Qt::MouseButton)), this, SLOT(mouseEventRec(QEvent::Type,QVector2D,Qt::MouseButton)));

    connect(this, SIGNAL(mouseEvent(QEvent::Type,QVector2D,Qt::MouseButton)), &mapa, SLOT(mouseEventRec(QEvent::Type,QVector2D,Qt::MouseButton)));
    connect(&mapa, SIGNAL(elementClicked(int,int)), this, SLOT(clickedElementMap(int,int)));

    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    mouseEventType = QEvent::MouseButtonPress;
    mousePosition = QVector2D(e->localPos());
    mouseButton = e->button();

    emit mouseEvent(mouseEventType, mousePosition, mouseButton);
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    mouseEventType = QEvent::MouseButtonDblClick;
    mousePosition = QVector2D(e->localPos());
    mouseButton = e->button();

    emit mouseEvent(mouseEventType, mousePosition, mouseButton);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mouseEventType = QEvent::MouseButtonRelease;
    mousePosition = QVector2D(e->localPos());
    mouseButton = e->button();

    emit mouseEvent(mouseEventType, mousePosition, mouseButton);
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    mouseEventType = QEvent::MouseMove;
    mousePosition = QVector2D(e->localPos());
    mouseButton = e->button();

    emit mouseEvent(mouseEventType, mousePosition, mouseButton);
}

void MainWidget::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{

    if(type == QEvent::MouseButtonPress && button == Qt::LeftButton)
    {
        mousePressPosition = pos;
        qDebug() << "mouse X: " << pos.x() << " Y: " << pos.y();

        qDebug() << "pointOnObject: " << object->pointOnObject(pos);

        bool wasOK = false;

        if(object->pointOnObject(pos) == true) //jeśli obiect został klikniety to zmien jego kolor
        {
            qDebug() << "old color: " << object->getColor(&wasOK);
            if(!wasOK)
                qDebug() << "Bład podczas getColor";

            object->setBaseColor(QColor(150,158,157));

            qDebug() << "new color: " << object->getColor(&wasOK);
            if(!wasOK)
                qDebug() << "Bład podczas getColor";
        }

        object->setObjectID(300);

        long id = object->getObjectID(&wasOK);
        qDebug() << "id: " << id << " wasOK: " << wasOK;


        power_icon->setPower(PowerIcon::wind);

        progres_bar->setStatus(0.25f);
    }

    if(type == QEvent::MouseButtonRelease && button == Qt::LeftButton)
    {
        // Mouse release position - mouse press position
        QVector2D diff = pos - mousePressPosition;

        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        // Accelerate angular speed relative to the length of the mouse sweep
        qreal acc = diff.length() / 100.0;

        // Calculate new rotation axis as weighted sum
        rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

        // Increase angular speed
        angularSpeed += acc;
    }

    if(type == QEvent::MouseMove && button == Qt::NoButton)
    {
        //qDebug() << "mouseMoveEvent X: " << mousePosition.x() << " Y: " << mousePosition.y();

    }

    //update();
}

void MainWidget::clickedElementMap(int x, int y)
{
    qDebug() << "ELEMENT MAPY (" << x<< ";" << y << ") ZOSTAL KLIKNIETY";
}

void MainWidget::selectedHeroId(unsigned int id)
{
    qDebug() << "SELECTED HERO: " << id;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    view.setToIdentity();

    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        //view.translate(0.0, 0.0, -5.0); //Dla perspective
        //view.rotate(rotation); //Dla perspective
        //view.translate(-1.5, 0.0, 0.0); // Dla perspective
        //view.translate(1, 1.0, 0.0); // Dla Orho
        // Request an update
        //update();
        return;
    }

    //view.translate(angularSpeed, 0,0);
    //view.translate(0.0, 0.0, -5.0); // Dla perspective
    //view.translate(-1.5, 0.0, 0.0); // Dla perspective
    //view.translate(1, 1.0, 0.0); // Dla Orho
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    //wczytanie shaderów
    if(!shader.loadFromFile(":/vshader.glsl",":/fshader.glsl"))
        qDebug() << "EEEE" ;

    //wczytanie i ustawienie tekstury
    bool wasOK = false;
    texture3 = new Texture(QString(":/cube2.png"), &wasOK);
    if(!wasOK)
        qDebug() << "Nie udało sie wczytać tekstury";
    texture3->setMinificationFilter(TextureFilter::Nearest); // Set nearest filtering mode for texture minification
    texture3->setMinificationFilter(TextureFilter::Linear); // Set bilinear filtering mode for texture magnification
    texture3->setWrapMode(TextureWrapMode::Repeat); // Wrap texture coordinates by repeating

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    object = new OpenGLObject2D;
    power_icon = new PowerIcon();
    progres_bar = new ProgresBar();
    object->setMesh(new PlateMesh());
    dcroll_heroes = new ScrollBarHeroes(QVector2D(20,100), QVector2D(200,600));
    connect(this, SIGNAL(mouseEvent(QEvent::Type,QVector2D,Qt::MouseButton)), dcroll_heroes, SLOT(mouseEventRec(QEvent::Type,QVector2D,Qt::MouseButton)));
    connect(dcroll_heroes, SIGNAL(selectedHeroId(unsigned int)), this, SLOT(selectedHeroId(unsigned int)));

    text_render = new OpenGLTextRender2D;
    text_render->setFontName("Arial.ttf");
    text_render->setFontSize(36);
    text_render->setColorText(QColor(0,255,0));
    text_render->setTextRender("ja tekstś");
    text_render->setBaseColor(QColor(0,0,255));
    text_render->setPosition(QVector2D(20,200));

    //object->setPosition(20.0, 30.0, 0.0);
    //object ->setScale(100.0,100.0,1.0);
    //object->setRotate(rotation);
    //object->setPosition(-1.5, 0.0, 0.0);
    //object->setBaseColor(QColor(255,255,255));
    object->setPosition(200.0, 300.0);
    object->setScale(50.0,50.0);
    object->setBaseColor(QColor(255,250,255));
    object->setTexture(texture3->getTexture());

    object->setTextureRect(250,0,250,250);

    power_icon->setPosition(400,400);
    power_icon->setScale(50,50);
    power_icon->setPower(PowerIcon::earth);

    progres_bar->setStatus(1.0f);
    progres_bar->setPosition(QVector2D(450,450));
    progres_bar->setSize(QVector2D(100, 20));
    progres_bar->setColorBackground(QColor(100,100,100));
    progres_bar->setColorStatus(QColor(0,255,255));

    dcroll_heroes->setSizeItem(QVector2D(80,80), QVector2D(50,50));

    QList<Hero::HeroInfo> hero_list;
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    hero_list << Hero::HeroInfo();
    dcroll_heroes->setHeroesList(hero_list);


    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    if(mapa.loadFromFile(QDir::currentPath() + "/mapa.txt"))
    {
        GameMap::Map item_map = mapa.getMap();

        qDebug() << "x: " <<item_map.x_size;
        qDebug() << "y: " <<item_map.y_size;
        for(int i = 0; i < item_map.y_size; ++i)
        {
            for(int j = 0; j < item_map.x_size; ++j)
            {
                qDebug() << "item(" << j << ";" << i << ") : " << item_map.map[i][j];
            }
        }
    }
    else
    {
        qDebug() << "Nie wczytano mapy z pliku";
    }



}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    //projection.perspective(fov, aspect, zNear, zFar); // Dla 3D
    projection.ortho(0.0f, w, h, 0.0f, -10.0f, 10.0f); // dla 2D

}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0, 0.0);

    shader.bindShader();

    if(!shader.setMatrixProjection(projection))
        qDebug() << "222";
    if(!shader.setMatrixView(view))
        qDebug() << "222";


    //object->setPosition(0.0, 0.0, -5.0);
    //object->setRotate(rotation);
    //object->setPosition(-1.5, 0.0, 0.0);

    text_render->draw(&shader);

    dcroll_heroes->draw(&shader);

    progres_bar->draw(&shader);

    power_icon->draw(&shader);

    object->setPosition(200.0, 300.0);
    object->draw(&shader);

    mapa.draw(&shader);

    shader.releaseShader();


    update(); // to trzeba optymalizować wywoływac np 20 razy na sekundę(20FPS)
}
