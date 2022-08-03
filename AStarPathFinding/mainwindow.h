#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custombutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const static int rows = 6;
    const static int columns = 12;

    CustomButton* grid[rows][columns];

    CustomButton* StartButton;
    CustomButton* EndButton;

    void PerfomAStar();

public slots:
     void ButtonsGridChanged(CustomButton* changedButton);
};
#endif // MAINWINDOW_H
