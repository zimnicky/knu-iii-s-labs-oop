#ifndef APPLE_H
#define APPLE_H

#include <QtOpenGL>
#include <GL/glu.h>

class Apple
{
protected:
    double rotation;
    QVector3D position;

    GLuint texture;
    GLUquadric* model;
    bool visible;
public:
    Apple();

    void setTexture(GLuint texture);
    void setPosition(const QVector3D &pos);
    void rotate(double angle);
    void draw();
    void setVisible(bool v);

    bool getVisible();
    QVector3D getPos();
};

#endif // APPLE_H
