#ifndef FIELD_H
#define FIELD_H

#include <QtOpenGL>
#include <vector>


using namespace std;

class Field
{
protected:
    GLfloat width, length;
    vector<GLfloat> points;
    vector<GLfloat> textureCoords;
    vector<GLubyte> indices;

    GLuint texture;
public:
    Field();
    void setTexture(GLuint texture);
    void setSize(GLfloat w, GLfloat l);

    void draw();
};

#endif // FIELD_H
