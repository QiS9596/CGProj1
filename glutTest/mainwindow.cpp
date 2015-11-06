#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_eyexAdd_clicked()
{
    ui->widget_2->eyex++;
    ui->widget_2->update();
}

void MainWindow::on_eyexMinus_clicked()
{
    ui->widget_2->eyex--;
    ui->widget_2->update();
}

void MainWindow::on_eyeyAdd_clicked()
{
    ui->widget_2->eyey++;
    ui->widget_2->update();
}

void MainWindow::on_eyeyMinus_clicked()
{
    ui->widget_2->eyey--;
    ui->widget_2->update();
}

void MainWindow::on_eyezAdd_clicked()
{
    ui->widget_2->eyez++;
    ui->widget_2->update();
}

void MainWindow::on_eyezMinus_clicked()
{
    ui->widget_2->eyez--;
    ui->widget_2->update();
}

void MainWindow::on_centerxAdd_clicked()
{
    ui->widget_2->centerx++;
    ui->widget_2->update();
}

void MainWindow::on_centerxMinus_clicked()
{
    ui->widget_2->centerx--;
    ui->widget_2->update();
}

void MainWindow::on_centeryAdd_clicked()
{
    ui->widget_2->centery++;
    ui->widget_2->update();
}

void MainWindow::on_centeryMinus_clicked()
{
    ui->widget_2->centery--;
    ui->widget_2->update();
}

void MainWindow::on_centerzAdd_clicked()
{
    ui->widget_2->centerz++;
    ui->widget_2->update();
}

void MainWindow::on_centerzMinus_clicked()
{
    ui->widget_2->centerz--;
    ui->widget_2->update();
}

void MainWindow::on_button_Standby_clicked()
{
    ui->widget_2->coordinates->state = 0;//standby state
    ui->widget_2->update();
}

void MainWindow::on_button_Movehand_clicked()
{
    ui->widget_2->coordinates->standby();
    ui->widget_2->coordinates->state = 1;// move hand state
    ui->widget_2->update();
}

void MainWindow::on_drawFog_toggled(bool checked)
{
    ui->widget_2->coordinates->drawFog = checked;
    ui->widget_2->update();
}

void MainWindow::on_button_summonSword_clicked()
{
    ui->widget_2->coordinates->subState = 0;
    ui->widget_2->coordinates->standby();
    ui->widget_2->coordinates->state = 1000;
    ui->widget_2->update();
}
