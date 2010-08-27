#include "shape.h"

void drawPlane(int x, int y) {
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

/*void drawFace() {
  glPushMatrix();
  glBegin(GL_TRIANGLES);
    glColor3f(1,1,1 );
    glVertex3f(0, 2.5, 0);
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(0.15, 2.15, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(-0.30, 2.5, -0.2);
    glVertex3f(-0.15, 2.15, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3f(0, 2.5, 0);
    glVertex3f(0.30, 2.5, -0.2);
    glVertex3f(0.15, 2.15, 0);
  glEnd();
  //---
  glPopMatrix();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1);
    glVertex3f(-0.30, 2.5, -0.2);
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(-0.45, 2.15, -0.25);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1);
    glVertex3f(0.30, 2.5, -0.2);
    glVertex3f(0.15, 2.15, 0);
    glVertex3f(0.45, 2.15, -0.25);
  glEnd();
  //---
  // Start Nose:
  glBegin(GL_TRIANGLES);
    glColor3f(0,1,0 );
    glVertex3f(0, 1.85, 0.15);
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(0.15, 2.15, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1 );
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(0, 1.85, 0.15);
    glVertex3f(-0.15, 1.75, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,1 );
    glVertex3f(0.15, 2.15, 0);
    glVertex3f(0, 1.85, 0.15);
    glVertex3f(0.15, 1.75, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0 );
    glVertex3f(0, 1.85, 0.15);
    glVertex3f(-0.15, 1.75, 0);
    glVertex3f(0.15, 1.75, 0);
  glEnd();
  //End nose
  //---
  //Begin eyes
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,0.75 );
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(-0.30, 1.95, -0.15);
    glVertex3f(-0.15, 1.75, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0,0.75 );
    glVertex3f(0.15, 2.15, 0);
    glVertex3f(0.30, 1.95, -0.15);
    glVertex3f(0.15, 1.75, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0,0.75,0 );
    glVertex3f(-0.15, 2.15, 0);
    glVertex3f(-0.30, 1.95, -0.15);
    glVertex3f(-0.45, 2.15, -0.25);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0,0.75,0 );
    glVertex3f(0.15, 2.15, 0);
    glVertex3f(0.30, 1.95, -0.15);
    glVertex3f(0.45, 2.15, -0.25);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.75,0,0 );
    glVertex3f(-0.45, 2.15, -0.25);
    glVertex3f(-0.30, 1.95, -0.15);
    glVertex3f(-0.45, 1.75, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.75,0,0 );
    glVertex3f(0.45, 2.15, -0.25);
    glVertex3f(0.30, 1.95, -0.15);
    glVertex3f(0.45, 1.75, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.5,0 );
    glVertex3f(-0.30, 1.95, -0.15);
    glVertex3f(-0.15, 1.75, 0);
    glVertex3f(-0.45, 1.75, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.5,0 );
    glVertex3f(0.30, 1.95, -0.15);
    glVertex3f(0.15, 1.75, 0);
    glVertex3f(0.45, 1.75, 0);
  glEnd();
  //---
  float colorsRand[3] = { 1/(rand() % 10 + 1),
                       1/(rand() % 10 + 1),
                       1/(rand() % 10 + 1) };
  glColor3f(colorsRand[0],colorsRand[1],colorsRand[2]);
  glPushMatrix();
  glTranslatef(-0.3, 1.95, -0.15);
  drawCube(0.05, 0.05, 0.05);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.3, 1.95, -0.15);
  drawCube(0.05, 0.05, 0.05);
  glPopMatrix();
  //---
  //Begin Jaw
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0 );
    glVertex3f(0, 1.75, 0);
    glVertex3f(-0.40, 1.65, -0.05);
    glVertex3f(0.40, 1.65, -0.05);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,1 );
    glVertex3f(0, 1.75, 0);
    glVertex3f(0.45, 1.75, 0);
    glVertex3f(0.40, 1.65, -0.05);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,1 );
    glVertex3f(0, 1.75, 0);
    glVertex3f(-0.45, 1.75, 0);
    glVertex3f(-0.40, 1.65, -0.05);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0,0.5 );
    glVertex3f(-0.45, 1.75, 0);
    glVertex3f(-0.35, 1.35, 0);
    glVertex3f(-0.40, 1.65, -0.05);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0,0.5 );
    glVertex3f(0.45, 1.75, 0);
    glVertex3f(0.35, 1.35, 0);
    glVertex3f(0.40, 1.65, -0.05);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.5,0.5 );
    glVertex3f(-0.45, 1.75, 0);
    glVertex3f(-0.35, 1.35, 0);
    glVertex3f(-0.40, 1.25, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.5,0.5 );
    glVertex3f(0.45, 1.75, 0);
    glVertex3f(0.35, 1.35, 0);
    glVertex3f(0.40, 1.25, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(0.25,0.25,0.25 );
    glVertex3f(-0.35, 1.35, 0);
    glVertex3f(-0.28, 1.25, 0);
    glVertex3f(-0.40, 1.25, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(0.25,0.25,0.25 );
    glVertex3f(0.35, 1.35, 0);
    glVertex3f(0.28, 1.25, 0);
    glVertex3f(0.40, 1.25, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.25,0.25 );
    glVertex3f(-0.35, 1.35, 0);
    glVertex3f(-0.28, 1.25, 0);
    glVertex3f(0, 1.30, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glColor3f(1,0.25,0.25 );
    glVertex3f(0.35, 1.35, 0);
    glVertex3f(0.28, 1.25, 0);
    glVertex3f(0, 1.30, 0);
  glEnd();
  //---
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0 );
    glVertex3f(0, 1.30, 0);
    glVertex3f(-0.28, 1.25, 0);
    glVertex3f(0.28, 1.25, 0);
  glEnd();
  //---
  //Inside of mouth
  glBegin(GL_POLYGON);
    glColor3f(colorsRand[0],colorsRand[1],colorsRand[2]);
    glVertex3f(-0.40, 1.65, -0.05);
    glVertex3f(-0.35, 1.35, 0);
    glVertex3f(0, 1.25, 0);
    glVertex3f(0.35, 1.35, 0);
    glVertex3f(0.40, 1.65, -0.05);
  glEnd();
  }*/
