#include "camera.h"

Camera::Camera():position(0.1, 10, 0.1),target(0,0,0),up(0,1,0)
{
}

void Camera::setPosition(const QVector3D &pos)
{
    position = pos;
}

QMatrix4x4 Camera::getViewProjectMatrix()
{
    QMatrix4x4 res;
    res.frustum(-1, 1, -1, 1, 1, 1000);
    res.lookAt(position, target, up);
    return res;
}

void Camera::moveFront(GLfloat dist)
{
    QVector3D v = target - position;
    v.normalize();
    position += v*dist;
    target += v*dist;
}

void Camera::rotateView(double angle, QVector3D v)
{
        QVector3D view = target - position;

        double cosa =cos(angle);
        double sina =sin(angle);

        QVector3D newView((cosa+(1-cosa)*v.x()*v.x())*view.x(),
                        ((1 - cosa)*v.x()*v.y()+v.z()*sina)*view.x(),
                        ((1 - cosa)*v.x()*v.z()-v.y()*sina)*view.x());

        newView.setX(newView.x() + ((1-cosa)*v.x()*v.y()-v.z()*sina)*view.y() +
                     ((1-cosa)*v.x()*v.z()+v.y()*sina)*view.z());


        newView.setY(newView.y() + (cosa + (1 - cosa)*v.y()*v.y())*view.y() +
                     ((1 - cosa)*v.y()*v.z()-v.z()*sina)*view.z());

        newView.setZ(newView.z() + ((1 - cosa)*v.y()*v.z()+v.x()*sina)*view.y() +
                     (cosa + (1 - cosa)*v.z()*v.z())*view.z());

        target = position + newView;
}


void Camera::rotateViewLeft(double angle)
{
    QVector3D v = QVector3D::crossProduct(target - position, up);
    v.normalize();
    v = up;
    rotateView(angle, v);
}


void Camera::setTarget(const QVector3D &t)
{
    target = t;
}

QVector3D Camera::getPos()
{
    return position;
}

QVector3D Camera::getTarget()
{
    return target;
}

QVector3D Camera::upVector()
{
    return up;
}
