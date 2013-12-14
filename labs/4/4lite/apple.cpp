#include "apple.h"

Apple::Apple()
{
    model = gluNewQuadric();
    gluQuadricTexture(model, GL_TRUE);
}


void Apple::setPosition(const QVector3D &pos)
{
    position = pos;
}

void Apple::rotate(double angle)
{
    rotation += angle;
}

void Apple::draw()
{
    if (!visible)
        return;
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        glTranslatef(position.x(), position.y(), position.z());
        glRotatef(rotation, 0, 1, 0);
        gluSphere(model, 1, 100, 100);
    glPopMatrix();
}


void Apple::setTexture(GLuint texture)
{
    this->texture = texture;
}

void Apple::setVisible(bool v)
{
    visible = v;
}


QVector3D Apple::getPos()
{
    return position;
}


bool Apple::getVisible()
{
    return visible;
}
