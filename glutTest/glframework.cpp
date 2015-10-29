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
    coordinates->lefthand_dynamic_rotate[0] += 0.08;
    coordinates->lefthand_dynamic_rotate[1] = 1;
    this->update();
}

void glframework::draw_robot(){
    glPushMatrix();


    draw_body();
    /* draw five things that connect to the body
     * in the following part
     */
    //============================================
        /*head*/
        glPushMatrix();
        draw_head();
        glPopMatrix();
    //============================================
        /*left arm and it's children*/
        glPushMatrix();
        draw_leftarm(); //Note we finish drawing children in this function
        glPopMatrix();
    //============================================
        /*right arm and it's children*/
        glPushMatrix();
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
    glTranslatef(coordinates->body_dynamic_translate[0]
                ,coordinates->body_dynamic_translate[1]
                ,coordinates->body_dynamic_translate[2]);
    glRotatef(coordinates->BODY_STATIC_ROTATION[0],
              coordinates->BODY_STATIC_ROTATION[1],
              coordinates->BODY_STATIC_ROTATION[2],
              coordinates->BODY_STATIC_ROTATION[3]);
    glRotatef(coordinates->body_dynamic_rotate[0]
             ,coordinates->body_dynamic_rotate[1]
             ,coordinates->body_dynamic_rotate[2]
             ,coordinates->body_dynamic_rotate[3]);
    glTranslatef(coordinates->BODY_STATIC_ORIGINPOS[0],
                 coordinates->BODY_STATIC_ORIGINPOS[1],
                 coordinates->BODY_STATIC_ORIGINPOS[2]);
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
    glTranslatef(coordinates->neck_dynamic_translate[0]
                ,coordinates->neck_dynamic_translate[1]
                ,coordinates->neck_dynamic_translate[2]);
    glRotatef(coordinates->NECK_STATIC_ROTATION[0],
              coordinates->NECK_STATIC_ROTATION[1],
              coordinates->NECK_STATIC_ROTATION[2],
              coordinates->NECK_STATIC_ROTATION[3]);
    glRotatef(coordinates->neck_dynamic_rotate[0]
             ,coordinates->neck_dynamic_rotate[1]
             ,coordinates->neck_dynamic_rotate[2]
             ,coordinates->neck_dynamic_rotate[3]);
    glTranslatef(coordinates->NECK_STATIC_ORIGINPOS[0],
                 coordinates->NECK_STATIC_ORIGINPOS[1],
                 coordinates->NECK_STATIC_ORIGINPOS[2]);
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
    glTranslatef(coordinates->leftarm_dynamic_translate[0]
                ,coordinates->leftarm_dynamic_translate[1]
                ,coordinates->leftarm_dynamic_translate[2]);
    glRotatef(coordinates->LEFTARM_STATIC_ROTATION[0],
              coordinates->LEFTARM_STATIC_ROTATION[1],
              coordinates->LEFTARM_STATIC_ROTATION[2],
              coordinates->LEFTARM_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftarm_dynamic_rotate[0]
             ,coordinates->leftarm_dynamic_rotate[1]
             ,coordinates->leftarm_dynamic_rotate[2]
             ,coordinates->leftarm_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTARM_STATIC_ORIGINPOS[0],
                 coordinates->LEFTARM_STATIC_ORIGINPOS[1],
                 coordinates->LEFTARM_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTARM_STATIC_SCALING[0],
             coordinates->LEFTARM_STATIC_SCALING[1],
             coordinates->LEFTARM_STATIC_SCALING[2]);

    glutSolidCube(1.0);
    glPopMatrix();
    draw_leftforearm();
    //TO-DO draw fore arm/hand/fingers/fingerknuckles here

}

void glframework::draw_leftforearm(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTFOREARM_STATIC_POSITION[0],
            coordinates->LEFTFOREARM_STATIC_POSITION[1]-0.1,
            coordinates->LEFTFOREARM_STATIC_POSITION[2]);
    glutSolidSphere(0.5,30,30);
    glPopMatrix();

    glTranslatef(coordinates->LEFTFOREARM_STATIC_POSITION[0],
                 coordinates->LEFTFOREARM_STATIC_POSITION[1],
                 coordinates->LEFTFOREARM_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftforearm_dynamic_translate[0]
                ,coordinates->leftforearm_dynamic_translate[1]
                ,coordinates->leftforearm_dynamic_translate[2]);
    glRotatef(coordinates->LEFTFOREARM_STATIC_ROTATION[0],
              coordinates->LEFTFOREARM_STATIC_ROTATION[1],
              coordinates->LEFTFOREARM_STATIC_ROTATION[2],
              coordinates->LEFTFOREARM_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftforearm_dynamic_rotate[0]
             ,coordinates->leftforearm_dynamic_rotate[1]
             ,coordinates->leftforearm_dynamic_rotate[2]
             ,coordinates->leftforearm_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTFOREARM_STATIC_ORIGINPOS[0],
                 coordinates->LEFTFOREARM_STATIC_ORIGINPOS[1],
                 coordinates->LEFTFOREARM_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTFOREARM_STATIC_SCALING[0],
             coordinates->LEFTFOREARM_STATIC_SCALING[1],
             coordinates->LEFTFOREARM_STATIC_SCALING[2]);
    glColor3f(0.0f,1.0f,0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_lefthand();
}

void glframework::draw_lefthand(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTHAND_STATIC_POSITION[0],
            coordinates->LEFTHAND_STATIC_POSITION[1]-0.05,
            coordinates->LEFTHAND_STATIC_POSITION[2]);
    glutSolidSphere(0.35,30,30);
    glPopMatrix();

    glTranslatef(coordinates->LEFTHAND_STATIC_POSITION[0],
                 coordinates->LEFTHAND_STATIC_POSITION[1],
                 coordinates->LEFTHAND_STATIC_POSITION[2]);
    glTranslatef(coordinates->lefthand_dynamic_translate[0]
                ,coordinates->lefthand_dynamic_translate[1]
                ,coordinates->lefthand_dynamic_translate[2]);
    glRotatef(coordinates->LEFTHAND_STATIC_ROTATION[0],
              coordinates->LEFTHAND_STATIC_ROTATION[1],
              coordinates->LEFTHAND_STATIC_ROTATION[2],
              coordinates->LEFTHAND_STATIC_ROTATION[3]);
    glRotatef(coordinates->lefthand_dynamic_rotate[0]
             ,coordinates->lefthand_dynamic_rotate[1]
             ,coordinates->lefthand_dynamic_rotate[2]
             ,coordinates->lefthand_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTHAND_STATIC_ORIGINPOS[0],
                 coordinates->LEFTHAND_STATIC_ORIGINPOS[1],
                 coordinates->LEFTHAND_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTHAND_STATIC_SCALING[0],
             coordinates->LEFTHAND_STATIC_SCALING[1],
             coordinates->LEFTHAND_STATIC_SCALING[2]);
    glColor3f(0.0f,1.0f,0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void glframework::draw_rightarm(){

    glTranslatef(coordinates->RIGHTARM_STATIC_POSITION[0],
                 coordinates->RIGHTARM_STATIC_POSITION[1],
                 coordinates->RIGHTARM_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightarm_dynamic_translate[0]
                ,coordinates->rightarm_dynamic_translate[1]
                ,coordinates->rightarm_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTARM_STATIC_ROTATION[0],
              coordinates->RIGHTARM_STATIC_ROTATION[1],
              coordinates->RIGHTARM_STATIC_ROTATION[2],
              coordinates->RIGHTARM_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightarm_dynamic_rotate[0]
             ,coordinates->rightarm_dynamic_rotate[1]
             ,coordinates->rightarm_dynamic_rotate[2]
             ,coordinates->rightarm_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTARM_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTARM_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTARM_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTARM_STATIC_SCALING[0],
             coordinates->RIGHTARM_STATIC_SCALING[1],
             coordinates->RIGHTARM_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_rightforearm();
    //TO-DO draw fore arm/hand/fingers/fingerknuckles here

}

void glframework::draw_rightforearm(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTFOREARM_STATIC_POSITION[0],
            coordinates->RIGHTFOREARM_STATIC_POSITION[1]-0.1,
            coordinates->RIGHTFOREARM_STATIC_POSITION[2]);
    glutSolidSphere(0.5,30,30);
    glPopMatrix();

    glTranslatef(coordinates->RIGHTFOREARM_STATIC_POSITION[0],
                 coordinates->RIGHTFOREARM_STATIC_POSITION[1],
                 coordinates->RIGHTFOREARM_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightforearm_dynamic_translate[0]
                ,coordinates->rightforearm_dynamic_translate[1]
                ,coordinates->rightforearm_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTFOREARM_STATIC_ROTATION[0],
              coordinates->RIGHTFOREARM_STATIC_ROTATION[1],
              coordinates->RIGHTFOREARM_STATIC_ROTATION[2],
              coordinates->RIGHTFOREARM_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightforearm_dynamic_rotate[0]
             ,coordinates->rightforearm_dynamic_rotate[1]
             ,coordinates->rightforearm_dynamic_rotate[2]
             ,coordinates->rightforearm_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTFOREARM_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTFOREARM_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTFOREARM_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTFOREARM_STATIC_SCALING[0],
             coordinates->RIGHTFOREARM_STATIC_SCALING[1],
             coordinates->RIGHTFOREARM_STATIC_SCALING[2]);
    glColor3f(0.0f,1.0f,0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}
