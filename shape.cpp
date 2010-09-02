#include "shape.h"

int getTextureHandle(const char *name, GLuint *texture) {
    // Help for this section credited to GPwiki		
    SDL_Surface *surface;
    GLenum texture_format;
    GLint  nOfColors;

    if ( (surface = IMG_Load(name)) ) {
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }

        //glBindTexture( GL_TEXTURE_2D, *texture ); 

        // Get the PNGs properties from SDL and apply them to the image
        glBindTexture( GL_TEXTURE_2D, *texture );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
    } else {
        printf("Could not load image.\n");
        return -1;
    }
    if (surface)
        SDL_FreeSurface(surface);

    printf("Loaded image.\n");
    return 0;
}

void drawPlaneTex(float x, float y, GLuint *texture) {
    if (x<1)
        x=1;
    if (y<1)
        y=1;
    glBindTexture( GL_TEXTURE_2D, *texture );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-x/2, 0, -y/2);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-x/2, 0, y/2);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x/2, 0, y/2);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x/2, 0, -y/2);
    glEnd();
}

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
