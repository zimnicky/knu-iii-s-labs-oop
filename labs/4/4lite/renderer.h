#ifndef RENDERER_H
#define RENDERER_H

#include <QtOpenGL>
#include <QtGui>
#include "field.h"
#include "camera.h"
#include "apple.h"

class Renderer: public QGLWidget
{
protected:

    Field field;
    Camera camera;
    vector<Apple> apples;
    int rotateTimer;
    int startingTimer;

    bool gameStarted = false;
    uint countApples;
    uint time;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *);

    void timerEvent(QTimerEvent *);

    void startGame();

    void checkCollisions();
public:
    Renderer(QWidget* parent = 0);
    virtual ~Renderer();
};

#endif // RENDERER_H
