#ifndef CAMERA_H
#define CAMERA_H

#include <QtOpenGL>

class Camera
{
protected:
    QVector3D position;
    QVector3D target;
    QVector3D up;

public:
    Camera();
    QMatrix4x4 getViewProjectMatrix();
    void setPosition(const QVector3D &pos);
    void setTarget(const QVector3D &t);

    QVector3D getPos();
    QVector3D getTarget();
    QVector3D upVector();


    void moveFront(GLfloat dist);
    void rotateView(double angle, QVector3D vector);
    void rotateViewLeft(double angle);
};

#endif // CAMERA_H
