#include "shape.h"

void drawPlane(float x, float y) {
    if (x<1)
        x=1;
    if (y<1)
        y=1;
    glBegin(GL_QUADS);
    glVertex3f(-x/2, 0, -y/2);
    glVertex3f(-x/2, 0, y/2);
    glVertex3f(x/2, 0, y/2);
    glVertex3f(x/2, 0, -y/2);
    glEnd();
}

void drawVertPlane(float x, float y) {
    if (x<1)
        x=1;
    if (y<1)
        y=1;
    glBegin(GL_QUADS);
    glVertex3f(-x/2, -y/2, 0);
    glVertex3f(-x/2, y/2, 0);
    glVertex3f(x/2, y/2, 0);
    glVertex3f(x/2, -y/2, 0);
    glEnd();
}

void drawCube(float x, float y, float z) {
    glBegin(GL_QUADS);

    //Back of cube:
    glVertex3f(-x/2, y/2, -z/2);
    glVertex3f(x/2, y/2, -z/2);
    glVertex3f(x/2, -y/2, -z/2);
    glVertex3f(-x/2, -y/2, -z/2);

    //front of the cube
    glVertex3f(-x/2, y/2, z/2);
    glVertex3f(x/2, y/2, z/2);
    glVertex3f(x/2, -y/2, z/2);
    glVertex3f(-x/2, -y/2, z/2);

    //Left side of the cube
    glVertex3f(-x/2, y/2, z/2);
    glVertex3f(-x/2, y/2, -z/2);
    glVertex3f(-x/2, -y/2, -z/2);
    glVertex3f(-x/2, -y/2, z/2);

    //RIGHT side of the cube
    glVertex3f(x/2, y/2, z/2);
    glVertex3f(x/2, y/2, -z/2);
    glVertex3f(x/2, -y/2, -z/2);
    glVertex3f(x/2, -y/2, z/2);

    //Top of the cube
    glVertex3f(-x/2, y/2, -z/2);
    glVertex3f(-x/2, y/2, z/2);
    glVertex3f(x/2, y/2, z/2);
    glVertex3f(x/2, y/2, -z/2);

    //Bottom of the cube
    glVertex3f(-x/2, -y/2, -z/2);
    glVertex3f(-x/2, -y/2, z/2);
    glVertex3f(x/2, -y/2, z/2);
    glVertex3f(x/2, -y/2, -z/2);

    glEnd();
}

void drawFace() {
  glPushMatrix();
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(0.15f, 2.15f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glVertex3f(-0.30f, 2.5f, -0.2f);
    glVertex3f(-0.15f, 2.15f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glVertex3f(0.30f, 2.5f, -0.2f);
    glVertex3f(0.15f, 2.15f, 0.0f);
  glEnd();
  //---
  glPopMatrix();
  glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(-0.30f, 2.5f, -0.2f);
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(-0.45f, 2.15f, -0.25f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1);
    glVertex3f(0.30f, 2.5f, -0.2f);
    glVertex3f(0.15f, 2.15f, 0.0f);
    glVertex3f(0.45f, 2.15f, -0.25f);
  glEnd();
  //---
  // Start Nose:
  glBegin(GL_TRIANGLES);
    glColor3f(0,1,0 );
    glVertex3f(0.0f, 1.85f, 0.15f);
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(0.15f, 2.15f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1 );
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(0.0f, 1.85f, 0.15f);
    glVertex3f(-0.15f, 1.75f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1 );
    glVertex3f(0.15f, 2.15f, 0.0f);
    glVertex3f(0.0f, 1.85f, 0.15f);
    glVertex3f(0.15f, 1.75f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.5f,0.0f );
    glVertex3f(0.0f, 1.85f, 0.15f);
    glVertex3f(-0.15f, 1.75f, 0.0f);
    glVertex3f(0.15f, 1.75f, 0.0f);
  glEnd();
  //End nose
  //---
  //Begin eyes
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,0.75 );
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(-0.30f, 1.95f, -0.15f);
    glVertex3f(-0.15f, 1.75f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,0.75 );
    glVertex3f(0.15f, 2.15f, 0.0f);
    glVertex3f(0.30f, 1.95f, -0.15f);
    glVertex3f(0.15f, 1.75f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0,0.75,0 );
    glVertex3f(-0.15f, 2.15f, 0.0f);
    glVertex3f(-0.30f, 1.95f, -0.15f);
    glVertex3f(-0.45f, 2.15f, -0.25f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0.75,0 );
    glVertex3f(0.15f, 2.15f, 0.0f);
    glVertex3f(0.30f, 1.95f, -0.15f);
    glVertex3f(0.45f, 2.15f, -0.25f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.75,0,0 );
    glVertex3f(-0.45f, 2.15f, -0.25f);
    glVertex3f(-0.30f, 1.95f, -0.15f);
    glVertex3f(-0.45f, 1.75f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.75,0,0 );
    glVertex3f(0.45f, 2.15f, -0.25f);
    glVertex3f(0.30f, 1.95f, -0.15f);
    glVertex3f(0.45f, 1.75f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.5,0 );
    glVertex3f(-0.30f, 1.95f, -0.15f);
    glVertex3f(-0.15f, 1.75f, 0.0f);
    glVertex3f(-0.45f, 1.75f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.5,0 );
    glVertex3f(0.30f, 1.95f, -0.15f);
    glVertex3f(0.15f, 1.75f, 0.0f);
    glVertex3f(0.45f, 1.75f, 0.0f);
  glEnd();
  //---
  float colorsRand[3] = { (float)1/(rand() % 10 + 1),
                       (float)1/(rand() % 10 + 1),
                       (float)1/(rand() % 10 + 1) };
  glColor3f(colorsRand[0],colorsRand[1],colorsRand[2]);
  glPushMatrix();
  glTranslatef(-0.3f, 1.95f, -0.15f);
  drawCube(0.05f, 0.05f, 0.05f);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.3f, 1.95f, -0.15f);
  drawCube(0.05f, 0.05f, 0.05f);
  glPopMatrix();
  //---
  //Begin Jaw
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0 );
    glVertex3f(0.0f, 1.75f, 0.0f);
    glVertex3f(-0.40f, 1.65f, -0.05f);
    glVertex3f(0.40f, 1.65f, -0.05f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,1 );
    glVertex3f(0.0f, 1.75f, 0.0f);
    glVertex3f(0.45f, 1.75f, 0.0f);
    glVertex3f(0.40f, 1.65f, -0.05f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,1 );
    glVertex3f(0.0f, 1.75f, 0.0f);
    glVertex3f(-0.45f, 1.75f, 0.0f);
    glVertex3f(-0.40f, 1.65f, -0.05f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0,0.5 );
    glVertex3f(-0.45f, 1.75f, 0.0f);
    glVertex3f(-0.35f, 1.35f, 0.0f);
    glVertex3f(-0.40f, 1.65f, -0.05f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0,0.5 );
    glVertex3f(0.45f, 1.75f, 0.0f);
    glVertex3f(0.35f, 1.35f, 0.0f);
    glVertex3f(0.40f, 1.65f, -0.05f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.5,0.5 );
    glVertex3f(-0.45f, 1.75f, 0.0f);
    glVertex3f(-0.35f, 1.35f, 0.0f);
    glVertex3f(-0.40f, 1.25f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.5,0.5 );
    glVertex3f(0.45f, 1.75f, 0.0f);
    glVertex3f(0.35f, 1.35f, 0.0f);
    glVertex3f(0.40f, 1.25f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.25,0.25,0.25 );
    glVertex3f(-0.35f, 1.35f, 0.0f);
    glVertex3f(-0.28f, 1.25f, 0.0f);
    glVertex3f(-0.40f, 1.25f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.25,0.25,0.25 );
    glVertex3f(0.35f, 1.35f, 0.0f);
    glVertex3f(0.28f, 1.25f, 0.0f);
    glVertex3f(0.40f, 1.25f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.25,0.25 );
    glVertex3f(-0.35f, 1.35f, 0.0f);
    glVertex3f(-0.28f, 1.25f, 0.0f);
    glVertex3f(0.0f, 1.30f, 0.0f);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.25,0.25 );
    glVertex3f(0.35f, 1.35f, 0.0f);
    glVertex3f(0.28f, 1.25f, 0.0f);
    glVertex3f(0.0f, 1.30f, 0.0f);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0 );
    glVertex3f(0.0f, 1.30f, 0.0f);
    glVertex3f(-0.28f, 1.25f, 0.0f);
    glVertex3f(0.28f, 1.25f, 0.0f);
  glEnd();
  //---
  //Inside of mouth
  glBegin(GL_POLYGON);
    glColor3f(colorsRand[0],colorsRand[1],colorsRand[2]);
    glVertex3f(-0.40f, 1.65f, -0.05f);
    glVertex3f(-0.35f, 1.35f, 0.0f);
    glVertex3f(0.0f, 1.25f, 0.0f);
    glVertex3f(0.35f, 1.35f, 0.0f);
    glVertex3f(0.40f, 1.65f, -0.05f);
  glEnd();
}
