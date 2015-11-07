#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_eyexAdd_clicked();

    void on_eyexMinus_clicked();

    void on_eyeyAdd_clicked();

    void on_eyeyMinus_clicked();

    void on_eyezAdd_clicked();

    void on_eyezMinus_clicked();

    void on_centerxAdd_clicked();

    void on_centerxMinus_clicked();

    void on_centeryAdd_clicked();

    void on_centeryMinus_clicked();

    void on_centerzAdd_clicked();

    void on_centerzMinus_clicked();

    void on_button_Standby_clicked();

    void on_button_Movehand_clicked();

    void on_drawFog_toggled(bool checked);

    void on_button_summonSword_clicked();

    void on_button_transfomation_clicked();


    void on_button_run_clicked();

    void on_button_walk_clicked();

    void on_button_yes_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
