#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QHBoxLayout*> layouts = ui->verticalLayout->findChildren<QHBoxLayout*>();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            CustomButton *customButton = new CustomButton(this);
            customButton->setFixedSize(40, 40);
            customButton->setStyleSheet("background-color: #707070;");
            customButton->x = j;
            customButton->y = i;
            layouts[i]->addWidget(customButton);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PerfomAStar()
{

}

void MainWindow::ButtonsGridChanged(CustomButton* changedButton)
{
    if(StartButton == nullptr || EndButton == nullptr) return;

    qDebug()<<"grid changed";
    if(changedButton->bIsStart) StartButton = changedButton;
    else if(changedButton->bIsEnd) EndButton = changedButton;

    QList<CustomButton *> buttons = this->findChildren<CustomButton*>();

    for(const auto button : buttons){
        if(button == StartButton){
            button->setStyleSheet("background-color: gold;");
            button->setText("S");
        }
        else if(button == EndButton){
            button->setStyleSheet("background-color: gold;");
            button->setText("E");
        }
        else if(button->bIsObstacle){
            button->setStyleSheet("background-color: black;");
            button->setText("");
        }
        else {
            button->setStyleSheet("background-color: #707070;");
            button->setText("");
        }
    }
    for(int i = 1; i <= rows; i++){
        for(int j = 0; j < columns; j++){
            grid[i][j] = buttons[j * i];
        }
    }
}

