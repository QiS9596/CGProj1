#ifndef GLFRAMEWORK_H
#define GLFRAMEWORK_H

#include <QOpenGLFunctions_1_1>
#include <QOpenGLWidget>
#include <QBasicTimer>
#include <coordinatecalculator.h>
class glframework : public QOpenGLWidget , protected QOpenGLFunctions_1_1
{
    Q_OBJECT
public:
    explicit glframework(QWidget *parent = 0);
    ~glframework();
    void initializeGL();
    void paintGL();
    void reasizeGL(int w,int h);
protected:
    void timerEvent(QTimerEvent *e);
private:
    CoordinateCalculator coordinates;
    QBasicTimer timer;
    void draw_robot();
    void draw_body();
signals:

public slots:
};

#endif // GLFRAMEWORK_H
