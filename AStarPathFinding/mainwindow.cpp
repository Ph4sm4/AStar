#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "custombutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

const int rows = 6;
const int columns = 12;

QPushButton* buttonGrid[rows][columns];
CustomButton grid[rows][columns];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout* layouts[rows];
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < columns; j++){
            CustomButton *customButton = new CustomButton();
            customButton->setFixedSize(25, 25);
            customButton->setStyleSheet("background-color: #707070;");
            layouts[i]->addItem(dynamic_cast<QLayoutItem*>(customButton));
        }
    }
    for(const auto hLayout : layouts){
        ui->verticalLayout->addItem(hLayout);
    }

    ButtonsGridChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonsGridChanged()
{
    QList<CustomButton *> buttons = this->findChildren<CustomButton*>();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){

        }
    }
}

