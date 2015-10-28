#include "glframework.h"
#include <GL/glut.h>
#include <Qtimer>
GLfloat rotate=0.0;
glframework::glframework(QWidget *parent) : QOpenGLWidget(parent)
{
    coordinates = new CoordinateCalculator();
}

glframework::~glframework()
{
    delete coordinates;
}

void glframework::initializeGL()
{


    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0, 1);
    glEnable(GL_DEPTH_TEST);
    GLfloat light_position[] = {-5.0f, 5.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    timer.start(0.2, this);
}
void glframework::paintGL()
{
//    glViewport(0,0,512,512);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.0f,0.01,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    gluLookAt(-5,6,15,0,0,0,0,1,0);
    if(true){
        gluLookAt(eyex, eyey, eyez,
                 centerx, centery, centerz,
                  0,1,0);
      std::cout << "eye: " << eyex <<", " << eyey << ", "<< eyez
             <<std::endl
               <<"center: " << centerx << ", " << centery <<", " << centerz
           <<std::endl;
    }
//===========================================
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f(1,0,0);
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f,0.0f,0.0f);
    GLfloat light_position[] = {-8.0f, 7.0f, -3.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    draw_robot();
    glPopMatrix();




    glEnd();
    this->update();
}
void glframework::resizeGL(int w,int h)
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
    coordinates->rightarm_dynamic_rotate[0] += 0.08;
    coordinates->rightarm_dynamic_rotate[1] = 1;
    this->update();
}

void glframework::draw_robot(){
    glPushMatrix();
    glTranslatef(coordinates->body_dynamic_translate[0]
                ,coordinates->body_dynamic_translate[1]
                ,coordinates->body_dynamic_translate[2]);
    glRotatef(coordinates->body_dynamic_rotate[0]
             ,coordinates->body_dynamic_rotate[1]
             ,coordinates->body_dynamic_rotate[2]
             ,coordinates->body_dynamic_rotate[3]);
    draw_body();
    /* draw five things that connect to the body
     * in the following part
     */
    //============================================
        /*head*/
        glPushMatrix();
        glTranslatef(coordinates->neck_dynamic_translate[0]
                    ,coordinates->neck_dynamic_translate[1]
                    ,coordinates->neck_dynamic_translate[2]);
        glRotatef(coordinates->neck_dynamic_rotate[0]
                 ,coordinates->neck_dynamic_rotate[1]
                 ,coordinates->neck_dynamic_rotate[2]
                 ,coordinates->neck_dynamic_rotate[3]);
        draw_head();
        glPopMatrix();
    //============================================
        /*left arm and it's children*/
        glPushMatrix();
        glTranslatef(coordinates->leftarm_dynamic_translate[0]
                    ,coordinates->leftarm_dynamic_translate[1]
                    ,coordinates->leftarm_dynamic_translate[2]);
        glRotatef(coordinates->leftarm_dynamic_rotate[0]
                 ,coordinates->leftarm_dynamic_rotate[1]
                 ,coordinates->leftarm_dynamic_rotate[2]
                 ,coordinates->leftarm_dynamic_rotate[3]);
        draw_leftarm(); //Note we finish drawing children in this function
        glPopMatrix();
    //============================================
        /*left arm and it's children*/
        glPushMatrix();
        glTranslatef(coordinates->rightarm_dynamic_translate[0]
                    ,coordinates->rightarm_dynamic_translate[1]
                    ,coordinates->rightarm_dynamic_translate[2]);
        glRotatef(coordinates->rightarm_dynamic_rotate[0]
                 ,coordinates->rightarm_dynamic_rotate[1]
                 ,coordinates->rightarm_dynamic_rotate[2]
                 ,coordinates->rightarm_dynamic_rotate[3]);
        draw_rightarm(); //Note we finish drawing children in this function
        glPopMatrix();
    //============================================
    glPopMatrix();
}

//TO-DO
void glframework::draw_body(){

    glTranslatef(coordinates->BODY_STATIC_POSITION[0],
                 coordinates->BODY_STATIC_POSITION[1],
                 coordinates->BODY_STATIC_POSITION[2]);
    glRotatef(coordinates->BODY_STATIC_ROTATION[0],
              coordinates->BODY_STATIC_ROTATION[1],
              coordinates->BODY_STATIC_ROTATION[2],
              coordinates->BODY_STATIC_ROTATION[3]);
    glPushMatrix();
    glScalef(coordinates->BODY_STATIC_SCALING[0],
             coordinates->BODY_STATIC_SCALING[1],
             coordinates->BODY_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();

}

void glframework::draw_head(){

    glTranslatef(coordinates->NECK_STATIC_POSITION[0],
                 coordinates->NECK_STATIC_POSITION[1],
                 coordinates->NECK_STATIC_POSITION[2]);
    glRotatef(coordinates->NECK_STATIC_ROTATION[0],
              coordinates->NECK_STATIC_ROTATION[1],
              coordinates->NECK_STATIC_ROTATION[2],
              coordinates->NECK_STATIC_ROTATION[3]);
    glPushMatrix();
    glScalef(coordinates->NECK_STATIC_SCALING[0],
             coordinates->NECK_STATIC_SCALING[1],
             coordinates->NECK_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();

}

void glframework::draw_leftarm(){

    glTranslatef(coordinates->LEFTARM_STATIC_POSITION[0],
                 coordinates->LEFTARM_STATIC_POSITION[1],
                 coordinates->LEFTARM_STATIC_POSITION[2]);
    glRotatef(coordinates->LEFTARM_STATIC_ROTATION[0],
              coordinates->LEFTARM_STATIC_ROTATION[1],
              coordinates->LEFTARM_STATIC_ROTATION[2],
              coordinates->LEFTARM_STATIC_ROTATION[3]);
    glPushMatrix();
    glScalef(coordinates->LEFTARM_STATIC_SCALING[0],
             coordinates->LEFTARM_STATIC_SCALING[1],
             coordinates->LEFTARM_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    //TO-DO draw fore arm/hand/fingers/fingerknuckles here

}

void glframework::draw_rightarm(){
    glPushMatrix();
    glTranslatef(coordinates->RIGHTARM_STATIC_POSITION[0],
                 coordinates->RIGHTARM_STATIC_POSITION[1],
                 coordinates->RIGHTARM_STATIC_POSITION[2]);
    glRotatef(coordinates->RIGHTARM_STATIC_ROTATION[0],
              coordinates->RIGHTARM_STATIC_ROTATION[1],
              coordinates->RIGHTARM_STATIC_ROTATION[2],
              coordinates->RIGHTARM_STATIC_ROTATION[3]);
    glPushMatrix();
    glScalef(coordinates->RIGHTARM_STATIC_SCALING[0],
             coordinates->RIGHTARM_STATIC_SCALING[1],
             coordinates->RIGHTARM_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    //TO-DO draw fore arm/hand/fingers/fingerknuckles here
    glPopMatrix();
}
