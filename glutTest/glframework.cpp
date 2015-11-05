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

    /*load textures*/
    leftwing = LoadGLTextures("./wing.png");

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
      /*std::cout << "eye: " << eyex <<", " << eyey << ", "<< eyez
             <<std::endl
               <<"center: " << centerx << ", " << centery <<", " << centerz
           <<std::endl;*/
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
    coordinates->updateDynamicCoordinate();

//    cout
    this->update();
}

QOpenGLTexture* glframework::LoadGLTextures( const char * name )
{
    QImage img;
    bool flag = img.load(name);
    if (flag)
    {
        QOpenGLTexture* texture = new QOpenGLTexture(img.mirrored());
        texture->setMinificationFilter (QOpenGLTexture::Linear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::ClampToEdge);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        return texture;
    }else{
        std::cout<<"Load \""<<name<<"\" Failed"<<std::endl;
        return NULL;
    }
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
        /*waist and legs*/
        glPushMatrix();
        draw_waist();
            glPushMatrix();
            draw_leftthigh();
            glPopMatrix();
            glPushMatrix();
            draw_rightthigh();
            glPopMatrix();
        glPopMatrix();
    //============================================
        /*shoulders*/
        glPushMatrix();
        draw_leftShoulder();
        glPopMatrix();
        glPushMatrix();
        draw_rightShoulder();
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

void glframework::draw_leftwing(){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    leftwing -> bind();
    glTranslatef(coordinates->LEFTWING_STATIC_POSITION[0],
                 coordinates->LEFTWING_STATIC_POSITION[1],
                 coordinates->LEFTWING_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftwing_dynamic_translate[0]
                ,coordinates->leftwing_dynamic_translate[1]
                ,coordinates->leftwing_dynamic_translate[2]);
    glRotatef(coordinates->LEFTWING_STATIC_ROTATION[0],
              coordinates->LEFTWING_STATIC_ROTATION[1],
              coordinates->LEFTWING_STATIC_ROTATION[2],
              coordinates->LEFTWING_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftwing_dynamic_rotate[0]
             ,coordinates->leftwing_dynamic_rotate[1]
             ,coordinates->leftwing_dynamic_rotate[2]
             ,coordinates->leftwing_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTWING_STATIC_ORIGINPOS[0],
                 coordinates->LEFTWING_STATIC_ORIGINPOS[1],
                 coordinates->LEFTWING_STATIC_ORIGINPOS[2]);
    glScalef(coordinates->LEFTWING_STATIC_SCALING[0],
             coordinates->LEFTWING_STATIC_SCALING[1],
             coordinates->LEFTWING_STATIC_SCALING[2]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);glVertex3d(0,0,0);
    glTexCoord2d(1,0);glVertex3d(5,0,0);
    glTexCoord2d(1,1);glVertex3d(5,5,0);
    glTexCoord2d(0,1);glVertex3d(0,5,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void glframework::draw_rightwing(){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    leftwing -> bind();
    glTranslatef(coordinates->RIGHTWING_STATIC_POSITION[0],
                 coordinates->RIGHTWING_STATIC_POSITION[1],
                 coordinates->RIGHTWING_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightwing_dynamic_translate[0]
                ,coordinates->rightwing_dynamic_translate[1]
                ,coordinates->rightwing_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTWING_STATIC_ROTATION[0],
              coordinates->RIGHTWING_STATIC_ROTATION[1],
              coordinates->RIGHTWING_STATIC_ROTATION[2],
              coordinates->RIGHTWING_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightwing_dynamic_rotate[0]
             ,coordinates->rightwing_dynamic_rotate[1]
             ,coordinates->rightwing_dynamic_rotate[2]
             ,coordinates->rightwing_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTWING_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTWING_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTWING_STATIC_ORIGINPOS[2]);
    glScalef(coordinates->RIGHTWING_STATIC_SCALING[0],
             coordinates->RIGHTWING_STATIC_SCALING[1],
             coordinates->RIGHTWING_STATIC_SCALING[2]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);glVertex3d(0,0,0);
    glTexCoord2d(1,0);glVertex3d(5,0,0);
    glTexCoord2d(1,1);glVertex3d(5,5,0);
    glTexCoord2d(0,1);glVertex3d(0,5,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
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
void glframework::draw_leftShoulder(){
    glTranslatef(coordinates->LEFTSHOULDER_STATIC_POSITION[0],
                 coordinates->LEFTSHOULDER_STATIC_POSITION[1],
                 coordinates->LEFTSHOULDER_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftshoulder_dynamic_translate[0]
                ,coordinates->leftshoulder_dynamic_translate[1]
                ,coordinates->leftshoulder_dynamic_translate[2]);
    glRotatef(coordinates->LEFTSHOULDER_STATIC_ROTATION[0],
              coordinates->LEFTSHOULDER_STATIC_ROTATION[1],
              coordinates->LEFTSHOULDER_STATIC_ROTATION[2],
              coordinates->LEFTSHOULDER_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftshoulder_dynamic_rotate[0]
             ,coordinates->leftshoulder_dynamic_rotate[1]
             ,coordinates->leftshoulder_dynamic_rotate[2]
             ,coordinates->leftshoulder_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTSHOULDER_STATIC_ORIGINPOS[0],
                 coordinates->LEFTSHOULDER_STATIC_ORIGINPOS[1],
                 coordinates->LEFTSHOULDER_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTSHOULDER_STATIC_SCALING[0],
             coordinates->LEFTSHOULDER_STATIC_SCALING[1],
             coordinates->LEFTSHOULDER_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_leftwing();
}
void glframework::draw_rightShoulder(){
    glTranslatef(coordinates->RIGHTSHOULDER_STATIC_POSITION[0],
                 coordinates->RIGHTSHOULDER_STATIC_POSITION[1],
                 coordinates->RIGHTSHOULDER_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightshoulder_dynamic_translate[0]
                ,coordinates->rightshoulder_dynamic_translate[1]
                ,coordinates->rightshoulder_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTSHOULDER_STATIC_ROTATION[0],
              coordinates->RIGHTSHOULDER_STATIC_ROTATION[1],
              coordinates->RIGHTSHOULDER_STATIC_ROTATION[2],
              coordinates->RIGHTSHOULDER_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightshoulder_dynamic_rotate[0]
             ,coordinates->rightshoulder_dynamic_rotate[1]
             ,coordinates->rightshoulder_dynamic_rotate[2]
             ,coordinates->rightshoulder_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTSHOULDER_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTSHOULDER_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTSHOULDER_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTSHOULDER_STATIC_SCALING[0],
             coordinates->RIGHTSHOULDER_STATIC_SCALING[1],
             coordinates->RIGHTSHOULDER_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_rightwing();
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

    draw_leftfingers();
}

void glframework::draw_leftfingers(){
    //===========================================================
    for(int index = 0; index < 3; index ++){
        glPushMatrix();
        glPushMatrix();//draw joint
        glTranslatef(coordinates->LEFTFINGERS_STATIC_POSITION[index][0],
                coordinates->LEFTFINGERS_STATIC_POSITION[index][1]-0.02,
                coordinates->LEFTFINGERS_STATIC_POSITION[index][2]);
        glutSolidSphere(0.12,30,30);
        glPopMatrix();

        glTranslatef(coordinates->LEFTFINGERS_STATIC_POSITION[index][0],
                     coordinates->LEFTFINGERS_STATIC_POSITION[index][1],
                     coordinates->LEFTFINGERS_STATIC_POSITION[index][2]);
        glTranslatef(coordinates->leftfingers_dynamic_translate[index][0]
                    ,coordinates->leftfingers_dynamic_translate[index][1]
                    ,coordinates->leftfingers_dynamic_translate[index][2]);
        glRotatef(coordinates->LEFTFINGERS_STATIC_ROTATION[index][0],
                  coordinates->LEFTFINGERS_STATIC_ROTATION[index][1],
                  coordinates->LEFTFINGERS_STATIC_ROTATION[index][2],
                  coordinates->LEFTFINGERS_STATIC_ROTATION[index][3]);
        glRotatef(coordinates->leftfingers_dynamic_rotate[index][0]
                 ,coordinates->leftfingers_dynamic_rotate[index][1]
                 ,coordinates->leftfingers_dynamic_rotate[index][2]
                 ,coordinates->leftfingers_dynamic_rotate[index][3]);
        glTranslatef(coordinates->LEFTFINGERS_STATIC_ORIGINPOS[index][0],
                     coordinates->LEFTFINGERS_STATIC_ORIGINPOS[index][1],
                     coordinates->LEFTFINGERS_STATIC_ORIGINPOS[index][2]);
        glPushMatrix();
        glScalef(coordinates->LEFTFINGERS_STATIC_SCALING[index][0],
                 coordinates->LEFTFINGERS_STATIC_SCALING[index][1],
                 coordinates->LEFTFINGERS_STATIC_SCALING[index][2]);
        glColor3f(0.0f,1.0f,0.0f);
        glutSolidCube(1.0);
        glPopMatrix();
        //TO-DO draw finger-knuckles here
        draw_leftfingerknuckles(index);
        glPopMatrix();
    }
}

void glframework::draw_leftfingerknuckles(int index){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][0],
            coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][1]-0.02,
            coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][2]);
    glutSolidSphere(0.12,30,30);
    glPopMatrix();

    glTranslatef(coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][0],
                 coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][1],
                 coordinates->LEFTFINGERKNUCKLES_STATIC_POSITION[index][2]);
    glTranslatef(coordinates->leftfingerknuckles_dynamic_translate[index][0]
                ,coordinates->leftfingerknuckles_dynamic_translate[index][1]
                ,coordinates->leftfingerknuckles_dynamic_translate[index][2]);
    glRotatef(coordinates->LEFTFINGERKNUCKLES_STATIC_ROTATION[index][0],
              coordinates->LEFTFINGERKNUCKLES_STATIC_ROTATION[index][1],
              coordinates->LEFTFINGERKNUCKLES_STATIC_ROTATION[index][2],
              coordinates->LEFTFINGERKNUCKLES_STATIC_ROTATION[index][3]);
    glRotatef(coordinates->leftfingerknuckles_dynamic_rotate[index][0]
             ,coordinates->leftfingerknuckles_dynamic_rotate[index][1]
             ,coordinates->leftfingerknuckles_dynamic_rotate[index][2]
             ,coordinates->leftfingerknuckles_dynamic_rotate[index][3]);
    glTranslatef(coordinates->LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][0],
                 coordinates->LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][1],
                 coordinates->LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][2]);
    glPushMatrix();
    glScalef(coordinates->LEFTFINGERKNUCKLES_STATIC_SCALING[index][0],
             coordinates->LEFTFINGERKNUCKLES_STATIC_SCALING[index][1],
             coordinates->LEFTFINGERKNUCKLES_STATIC_SCALING[index][2]);
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
    draw_righthand();
}

void glframework::draw_righthand(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTHAND_STATIC_POSITION[0],
            coordinates->RIGHTHAND_STATIC_POSITION[1]-0.05,
            coordinates->RIGHTHAND_STATIC_POSITION[2]);
    glutSolidSphere(0.35,30,30);
    glPopMatrix();

    glTranslatef(coordinates->RIGHTHAND_STATIC_POSITION[0],
                 coordinates->RIGHTHAND_STATIC_POSITION[1],
                 coordinates->RIGHTHAND_STATIC_POSITION[2]);
    glTranslatef(coordinates->righthand_dynamic_translate[0]
                ,coordinates->righthand_dynamic_translate[1]
                ,coordinates->righthand_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTHAND_STATIC_ROTATION[0],
              coordinates->RIGHTHAND_STATIC_ROTATION[1],
              coordinates->RIGHTHAND_STATIC_ROTATION[2],
              coordinates->RIGHTHAND_STATIC_ROTATION[3]);
    glRotatef(coordinates->righthand_dynamic_rotate[0]
             ,coordinates->righthand_dynamic_rotate[1]
             ,coordinates->righthand_dynamic_rotate[2]
             ,coordinates->righthand_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTHAND_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTHAND_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTHAND_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTHAND_STATIC_SCALING[0],
             coordinates->RIGHTHAND_STATIC_SCALING[1],
             coordinates->RIGHTHAND_STATIC_SCALING[2]);
    glColor3f(0.0f,1.0f,0.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    draw_rightfingers();
}

void glframework::draw_rightfingers(){
    //===========================================================
    for(int index = 0; index < 3; index ++){
        glPushMatrix();
        glPushMatrix();//draw joint
        glTranslatef(coordinates->RIGHTFINGERS_STATIC_POSITION[index][0],
                coordinates->RIGHTFINGERS_STATIC_POSITION[index][1]-0.02,
                coordinates->RIGHTFINGERS_STATIC_POSITION[index][2]);
        glutSolidSphere(0.12,30,30);
        glPopMatrix();

        glTranslatef(coordinates->RIGHTFINGERS_STATIC_POSITION[index][0],
                     coordinates->RIGHTFINGERS_STATIC_POSITION[index][1],
                     coordinates->RIGHTFINGERS_STATIC_POSITION[index][2]);
        glTranslatef(coordinates->rightfingers_dynamic_translate[index][0]
                    ,coordinates->rightfingers_dynamic_translate[index][1]
                    ,coordinates->rightfingers_dynamic_translate[index][2]);
        glRotatef(coordinates->RIGHTFINGERS_STATIC_ROTATION[index][0],
                  coordinates->RIGHTFINGERS_STATIC_ROTATION[index][1],
                  coordinates->RIGHTFINGERS_STATIC_ROTATION[index][2],
                  coordinates->RIGHTFINGERS_STATIC_ROTATION[index][3]);
        glRotatef(coordinates->rightfingers_dynamic_rotate[index][0]
                 ,coordinates->rightfingers_dynamic_rotate[index][1]
                 ,coordinates->rightfingers_dynamic_rotate[index][2]
                 ,coordinates->rightfingers_dynamic_rotate[index][3]);
        glTranslatef(coordinates->RIGHTFINGERS_STATIC_ORIGINPOS[index][0],
                     coordinates->RIGHTFINGERS_STATIC_ORIGINPOS[index][1],
                     coordinates->RIGHTFINGERS_STATIC_ORIGINPOS[index][2]);
        glPushMatrix();
        glScalef(coordinates->RIGHTFINGERS_STATIC_SCALING[index][0],
                 coordinates->RIGHTFINGERS_STATIC_SCALING[index][1],
                 coordinates->RIGHTFINGERS_STATIC_SCALING[index][2]);
        glColor3f(0.0f,1.0f,0.0f);
        glutSolidCube(1.0);
        glPopMatrix();
        //TO-DO draw finger-knuckles here
        draw_rightfingerknuckles(index);
        glPopMatrix();
    }
}

void glframework::draw_rightfingerknuckles(int index){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][0],
            coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][1]-0.02,
            coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][2]);
    glutSolidSphere(0.12,30,30);
    glPopMatrix();

    glTranslatef(coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][0],
                 coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][1],
                 coordinates->RIGHTFINGERKNUCKLES_STATIC_POSITION[index][2]);
    glTranslatef(coordinates->rightfingerknuckles_dynamic_translate[index][0]
                ,coordinates->rightfingerknuckles_dynamic_translate[index][1]
                ,coordinates->rightfingerknuckles_dynamic_translate[index][2]);
    glRotatef(coordinates->RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][0],
              coordinates->RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][1],
              coordinates->RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][2],
              coordinates->RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][3]);
    glRotatef(coordinates->rightfingerknuckles_dynamic_rotate[index][0]
             ,coordinates->rightfingerknuckles_dynamic_rotate[index][1]
             ,coordinates->rightfingerknuckles_dynamic_rotate[index][2]
             ,coordinates->rightfingerknuckles_dynamic_rotate[index][3]);
    glTranslatef(coordinates->RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][0],
                 coordinates->RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][1],
                 coordinates->RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTFINGERKNUCKLES_STATIC_SCALING[index][0],
             coordinates->RIGHTFINGERKNUCKLES_STATIC_SCALING[index][1],
             coordinates->RIGHTFINGERKNUCKLES_STATIC_SCALING[index][2]);
    glColor3f(0.0f,1.0f,0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void glframework::draw_waist(){
    glTranslatef(coordinates->WAIST_STATIC_POSITION[0],
                 coordinates->WAIST_STATIC_POSITION[1],
                 coordinates->WAIST_STATIC_POSITION[2]);
    glRotatef(coordinates->WAIST_STATIC_ROTATION[0],
              coordinates->WAIST_STATIC_ROTATION[1],
              coordinates->WAIST_STATIC_ROTATION[2],
              coordinates->WAIST_STATIC_ROTATION[3]);
    glRotatef(coordinates->waist_dynamic_rotate[0]
             ,coordinates->waist_dynamic_rotate[1]
             ,coordinates->waist_dynamic_rotate[2]
             ,coordinates->waist_dynamic_rotate[3]);
    glTranslatef(coordinates->WAIST_STATIC_ORIGINPOS[0],
                 coordinates->WAIST_STATIC_ORIGINPOS[1],
                 coordinates->WAIST_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->WAIST_STATIC_SCALING[0],
             coordinates->WAIST_STATIC_SCALING[1],
             coordinates->WAIST_STATIC_SCALING[2]);
    glutSolidCube(1.0f);
    glPopMatrix();

}

void glframework::draw_leftthigh(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTTHIGH_STATIC_POSITION[0],
            coordinates->LEFTTHIGH_STATIC_POSITION[1],
            coordinates->LEFTTHIGH_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->LEFTTHIGH_STATIC_POSITION[0],
                 coordinates->LEFTTHIGH_STATIC_POSITION[1],
                 coordinates->LEFTTHIGH_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftthigh_dynamic_translate[0]
                ,coordinates->leftthigh_dynamic_translate[1]
                ,coordinates->leftthigh_dynamic_translate[2]);
    glRotatef(coordinates->LEFTTHIGH_STATIC_ROTATION[0],
              coordinates->LEFTTHIGH_STATIC_ROTATION[1],
              coordinates->LEFTTHIGH_STATIC_ROTATION[2],
              coordinates->LEFTTHIGH_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftthigh_dynamic_rotate[0]
             ,coordinates->leftthigh_dynamic_rotate[1]
             ,coordinates->leftthigh_dynamic_rotate[2]
             ,coordinates->leftthigh_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTTHIGH_STATIC_ORIGINPOS[0],
                 coordinates->LEFTTHIGH_STATIC_ORIGINPOS[1],
                 coordinates->LEFTTHIGH_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTTHIGH_STATIC_SCALING[0],
             coordinates->LEFTTHIGH_STATIC_SCALING[1],
             coordinates->LEFTTHIGH_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_leftshank();

}

void glframework::draw_leftshank(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTSHANK_STATIC_POSITION[0],
            coordinates->LEFTSHANK_STATIC_POSITION[1],
            coordinates->LEFTSHANK_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->LEFTSHANK_STATIC_POSITION[0],
                 coordinates->LEFTSHANK_STATIC_POSITION[1],
                 coordinates->LEFTSHANK_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftshank_dynamic_translate[0]
                ,coordinates->leftshank_dynamic_translate[1]
                ,coordinates->leftshank_dynamic_translate[2]);
    glRotatef(coordinates->LEFTSHANK_STATIC_ROTATION[0],
              coordinates->LEFTSHANK_STATIC_ROTATION[1],
              coordinates->LEFTSHANK_STATIC_ROTATION[2],
              coordinates->LEFTSHANK_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftshank_dynamic_rotate[0]
             ,coordinates->leftshank_dynamic_rotate[1]
             ,coordinates->leftshank_dynamic_rotate[2]
             ,coordinates->leftshank_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTSHANK_STATIC_ORIGINPOS[0],
                 coordinates->LEFTSHANK_STATIC_ORIGINPOS[1],
                 coordinates->LEFTSHANK_STATIC_ORIGINPOS[2]);

    glPushMatrix();
    glScalef(coordinates->LEFTSHANK_STATIC_SCALING[0],
             coordinates->LEFTSHANK_STATIC_SCALING[1],
             coordinates->LEFTSHANK_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_leftfeet();
}

void glframework::draw_leftfeet(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->LEFTFEET_STATIC_POSITION[0],
            coordinates->LEFTFEET_STATIC_POSITION[1],
            coordinates->LEFTFEET_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->LEFTFEET_STATIC_POSITION[0],
                 coordinates->LEFTFEET_STATIC_POSITION[1],
                 coordinates->LEFTFEET_STATIC_POSITION[2]);
    glTranslatef(coordinates->leftfeet_dynamic_translate[0]
                ,coordinates->leftfeet_dynamic_translate[1]
                ,coordinates->leftfeet_dynamic_translate[2]);
    glRotatef(coordinates->LEFTFEET_STATIC_ROTATION[0],
              coordinates->LEFTFEET_STATIC_ROTATION[1],
              coordinates->LEFTFEET_STATIC_ROTATION[2],
              coordinates->LEFTFEET_STATIC_ROTATION[3]);
    glRotatef(coordinates->leftfeet_dynamic_rotate[0]
             ,coordinates->leftfeet_dynamic_rotate[1]
             ,coordinates->leftfeet_dynamic_rotate[2]
             ,coordinates->leftfeet_dynamic_rotate[3]);
    glTranslatef(coordinates->LEFTFEET_STATIC_ORIGINPOS[0],
                 coordinates->LEFTFEET_STATIC_ORIGINPOS[1],
                 coordinates->LEFTFEET_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->LEFTFEET_STATIC_SCALING[0],
             coordinates->LEFTFEET_STATIC_SCALING[1],
             coordinates->LEFTFEET_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
}

void glframework::draw_rightthigh(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTTHIGH_STATIC_POSITION[0],
            coordinates->RIGHTTHIGH_STATIC_POSITION[1],
            coordinates->RIGHTTHIGH_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->RIGHTTHIGH_STATIC_POSITION[0],
                 coordinates->RIGHTTHIGH_STATIC_POSITION[1],
                 coordinates->RIGHTTHIGH_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightthigh_dynamic_translate[0]
                ,coordinates->rightthigh_dynamic_translate[1]
                ,coordinates->rightthigh_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTTHIGH_STATIC_ROTATION[0],
              coordinates->RIGHTTHIGH_STATIC_ROTATION[1],
              coordinates->RIGHTTHIGH_STATIC_ROTATION[2],
              coordinates->RIGHTTHIGH_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightthigh_dynamic_rotate[0]
             ,coordinates->rightthigh_dynamic_rotate[1]
             ,coordinates->rightthigh_dynamic_rotate[2]
             ,coordinates->rightthigh_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTTHIGH_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTTHIGH_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTTHIGH_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTTHIGH_STATIC_SCALING[0],
             coordinates->RIGHTTHIGH_STATIC_SCALING[1],
             coordinates->RIGHTTHIGH_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_rightshank();

}

void glframework::draw_rightshank(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTSHANK_STATIC_POSITION[0],
            coordinates->RIGHTSHANK_STATIC_POSITION[1],
            coordinates->RIGHTSHANK_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->RIGHTSHANK_STATIC_POSITION[0],
                 coordinates->RIGHTSHANK_STATIC_POSITION[1],
                 coordinates->RIGHTSHANK_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightshank_dynamic_translate[0]
                ,coordinates->rightshank_dynamic_translate[1]
                ,coordinates->rightshank_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTSHANK_STATIC_ROTATION[0],
              coordinates->RIGHTSHANK_STATIC_ROTATION[1],
              coordinates->RIGHTSHANK_STATIC_ROTATION[2],
              coordinates->RIGHTSHANK_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightshank_dynamic_rotate[0]
             ,coordinates->rightshank_dynamic_rotate[1]
             ,coordinates->rightshank_dynamic_rotate[2]
             ,coordinates->rightshank_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTSHANK_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTSHANK_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTSHANK_STATIC_ORIGINPOS[2]);

    glPushMatrix();
    glScalef(coordinates->RIGHTSHANK_STATIC_SCALING[0],
             coordinates->RIGHTSHANK_STATIC_SCALING[1],
             coordinates->RIGHTSHANK_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    draw_rightfeet();

}

void glframework::draw_rightfeet(){
    glPushMatrix();//draw joint
    glTranslatef(coordinates->RIGHTFEET_STATIC_POSITION[0],
            coordinates->RIGHTFEET_STATIC_POSITION[1],
            coordinates->RIGHTFEET_STATIC_POSITION[2]);
    glutSolidSphere(0.3,30,30);
    glPopMatrix();


    glTranslatef(coordinates->RIGHTFEET_STATIC_POSITION[0],
                 coordinates->RIGHTFEET_STATIC_POSITION[1],
                 coordinates->RIGHTFEET_STATIC_POSITION[2]);
    glTranslatef(coordinates->rightfeet_dynamic_translate[0]
                ,coordinates->rightfeet_dynamic_translate[1]
                ,coordinates->rightfeet_dynamic_translate[2]);
    glRotatef(coordinates->RIGHTFEET_STATIC_ROTATION[0],
              coordinates->RIGHTFEET_STATIC_ROTATION[1],
              coordinates->RIGHTFEET_STATIC_ROTATION[2],
              coordinates->RIGHTFEET_STATIC_ROTATION[3]);
    glRotatef(coordinates->rightfeet_dynamic_rotate[0]
             ,coordinates->rightfeet_dynamic_rotate[1]
             ,coordinates->rightfeet_dynamic_rotate[2]
             ,coordinates->rightfeet_dynamic_rotate[3]);
    glTranslatef(coordinates->RIGHTFEET_STATIC_ORIGINPOS[0],
                 coordinates->RIGHTFEET_STATIC_ORIGINPOS[1],
                 coordinates->RIGHTFEET_STATIC_ORIGINPOS[2]);
    glPushMatrix();
    glScalef(coordinates->RIGHTFEET_STATIC_SCALING[0],
             coordinates->RIGHTFEET_STATIC_SCALING[1],
             coordinates->RIGHTFEET_STATIC_SCALING[2]);
    glutSolidCube(1.0);
    glPopMatrix();

}
