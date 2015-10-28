#include "glframework.h"
#include <GL/glut.h>
#include <Qtimer>
GLfloat rotate=0.0;
glframework::glframework(QWidget *parent) : QOpenGLWidget(parent)
{
}

glframework::~glframework()
{

}

void glframework::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    GLfloat light_position[] = {-5.0f, 5.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    timer.start(0.2, this);
}
void glframework::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f(1,0,0);
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    GLfloat light_position[] = {-5.0f, 5.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    draw_robot();
    glPopMatrix();




    glEnd();
    this->update();
}
void glframework::reasizeGL(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)w/h,0.01,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

}
void glframework::timerEvent(QTimerEvent *)
{
    this->update();
}

void glframework::draw_robot(){
    glPushMatrix();
    glTranslatef(coordinates.body_dynamic_translate[0]
                ,coordinates.body_dynamic_translate[1]
                ,coordinates.body_dynamic_translate[2]);
    glRotatef(coordinates.body_dynamic_rotate[0]
             ,coordinates.body_dynamic_rotate[1]
             ,coordinates.body_dynamic_rotate[2]
             ,coordinates.body_dynamic_rotate[3]);
    draw_body();
    glPopMatrix();
}

//TO-DO
void glframework::draw_body(){
    glPushMatrix();
//    glTranslatef();

    glPopMatrix();
}
