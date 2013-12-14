#include "field.h"


Field::Field()
{

}

void Field::setSize(GLfloat w, GLfloat l)
{
    width = w;
    length = l;
    points = {-width, 0.f, -length,
               width, 0.f, -length,
               width, 0.f,  length,
              -width, 0.f,  length};
    textureCoords = {
                  -1, -1,
                   1, -1,
                   1, 1,
                  -1, 1};
    indices = {
            0, 1, 2,
            0, 2, 3,
      };
}

void Field::setTexture(GLuint texture)
{
    this->texture = texture;
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Field::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT , 0, points.data());
    glTexCoordPointer(2, GL_FLOAT, sizeof(textureCoords.data()), textureCoords.data());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices.data());

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);
}
