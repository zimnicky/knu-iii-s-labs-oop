#include "renderer.h"
#include <GL/glu.h>

Renderer::Renderer(QWidget* parent)
{
    QGLFormat glFormat;
    glFormat.setDoubleBuffer(true);
    QGLWidget(glFormat, parent);
    field.setSize(50, 50);

    apples.resize(10);
    for(auto &i: apples)
    {
        GLfloat x = rand() % 100 - 50;
        GLfloat z = rand() % 100 - 50;
        double angle = (rand()%10) / M_PI;
        i.setPosition(QVector3D(x,1,z));
        i.rotate(angle);
        i.setVisible(true);
    }

    gameStarted = false;
}

Renderer::~Renderer()
{
}

void Renderer::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, h);
}



void Renderer::initializeGL()
{
    QPixmap pixmap(":/textures/grass.jpg");
    GLuint texture = bindTexture(pixmap, GL_TEXTURE_2D);
    field.setTexture(texture);

    pixmap.load(":/textures/apple_red.jpg");
    texture = bindTexture(pixmap, GL_TEXTURE_2D);

    for(auto &i: apples)
        i.setTexture(texture);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);


    GLfloat diffuse[] = {1,1,1,10};
    GLfloat ambient[] = {1,1,1,0};
    GLfloat specular[] = {1,1,1,0.1};
    GLfloat lightPos[] = {0, 100, 0, 0};

//    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
//    glLightfv(GL_LIGHT0, GL_SPECULAR,  ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_LIGHT0);

    rotateTimer = startTimer(10);

    camera.setPosition(QVector3D(0,50,50));
    camera.setTarget(QVector3D(0, 0, 0));

}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 210, 200,0);
    glLoadIdentity();

    glMultMatrixf(camera.getViewProjectMatrix().constData());

    field.draw();
    for(auto &i: apples)
        i.draw();
}


void Renderer::keyPressEvent(QKeyEvent *e)
{

    if (e->key() == Qt::Key_Space)
        startGame();

    if (!gameStarted)
    {
        return;
    }

    float angle = M_1_PI/6;
    if (e->key() == Qt::Key_W)
        camera.moveFront(0.5);
    if (e->key() == Qt::Key_S)
        camera.moveFront(-0.5);
    if (e->key() == Qt::Key_A)
        camera.rotateViewLeft(angle);
    if (e->key() == Qt::Key_D)
        camera.rotateViewLeft(-angle);
    checkCollisions();
    setWindowTitle(QString("%1 %2 %3 ").arg(camera.getPos().x()).arg(camera.getPos().y()).arg(camera.getPos().z()));
    setWindowTitle(windowTitle() + QString("(%1 %2 %3)").arg(camera.getTarget().x()).arg(camera.getTarget().y()).arg(camera.getTarget().z()));
    repaint();
}


void Renderer::timerEvent(QTimerEvent *t)
{
    if (t->timerId() == rotateTimer)
    {
        double angle = M_PI/6;
        for(auto &i: apples)
            i.rotate(angle);
        repaint();
    }
    else if (t->timerId() == startingTimer)
    {
        camera.moveFront(0.5);
        setWindowTitle(QString("%1 %2 %3 ").arg(camera.getPos().x()).arg(camera.getPos().y()).arg(camera.getPos().z()));
        setWindowTitle(windowTitle() + QString("(%1 %2 %3)").arg(camera.getTarget().x()).arg(camera.getTarget().y()).arg(camera.getTarget().z()));

        if (camera.getPos().y() <= 3)
        {
            camera.setPosition(QVector3D(0,2,0));
            camera.setTarget(QVector3D(0,2,-50));
            killTimer(t->timerId());
            gameStarted = true;
            startingTimer = -1;
            startTimer(100);
        }
    }
    else
    {
        time += 100;
    }
}


void Renderer::startGame()
{
    camera.setPosition(QVector3D(0,50,50));
    camera.setTarget(QVector3D(0, 0, 0));
    if (gameStarted)
        for(auto &i: apples)
        {
            GLfloat x = rand() % 100 - 50;
            GLfloat z = rand() % 100 - 50;
            double angle = (rand()%10) / M_PI;
            i.setPosition(QVector3D(x,1,z));
            i.rotate(angle);
            i.setVisible(true);
        }
    countApples = 0;
    time = 0;
    startingTimer = startTimer(10);
}


void Renderer::checkCollisions()
{
    for(auto &i: apples)
    {
        if (i.getVisible() && (camera.getPos() - i.getPos() - 2*camera.upVector()).length() <= 3)
        {
            i.setVisible(false);
            countApples++;
            if (countApples == apples.size() - 1)
            {
                QMessageBox::information(this, "You are finished", QString("Your time is %1 seconds").arg(time/1000));
            }
        }
    }
}
