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

    QList<CustomButton *> buttons = this->findChildren<CustomButton*>();
    int i = 0;
    int j = 0;
    while(i < rows){
        grid[i][j%columns] = buttons[j];
        j++;
        if(j % columns == 0) i++;
        if(j == buttons.size()) break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PerfomAStar()
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            qDebug() << grid[i][j]->y << " " << grid[i][j]->x;
        }
    }

    QSet<CustomButton* > open;
    QList<CustomButton* > closed;

    StartButton->G = 0;
    open.insert(StartButton);

    while(!open.isEmpty()){
        CustomButton* current = *open.begin();
        open.remove(current);
        closed.append(current);

        QList<CustomButton*> neighbours = getNeighbours(current);
        qDebug() << neighbours.size();
        for(auto neighbour : neighbours){
            neighbour->setStyleSheet("background-color: green;");
            qDebug() << neighbour->y << " " << neighbour->x;
        }
    }
}

QList<CustomButton *> MainWindow::getNeighbours(CustomButton *current)
{
    int currentX = current->x;
    int currentY = current->y;

    QList<CustomButton* > output;
    CustomButton* neighbour;

    if(currentX - 1 >= 0){
        neighbour = grid[currentY][currentX - 1];
        neighbour->H = getHeuristic(neighbour);
        neighbour->G = current->G + 1;
        neighbour->F = neighbour->H + neighbour->G;
        output.append(neighbour);
    }
    if(currentX + 1 < columns){
        neighbour = grid[currentY][currentX + 1];
        neighbour->H = getHeuristic(neighbour);
        neighbour->G = current->G + 1;
        neighbour->F = neighbour->H + neighbour->G;
        output.append(neighbour);
    }
    if(currentY - 1 >= 0){
        neighbour = grid[currentY - 1][currentX];
        neighbour->H = getHeuristic(neighbour);
        neighbour->G = current->G + 1;
        neighbour->F = neighbour->H + neighbour->G;
        output.append(neighbour);
    }
    if(currentY + 1 < rows){
        neighbour = grid[currentY + 1][currentX];
        neighbour->H = getHeuristic(neighbour);
        neighbour->G = current->G + 1;
        neighbour->F = neighbour->H + neighbour->G;
        output.append(neighbour);
    }

    return output;
}

int MainWindow::getHeuristic(CustomButton *current)
{
    int endX = EndButton->x;
    int endY = EndButton->y;
    int currentX = current->x;
    int currentY = current->y;

    int h = qSqrt((endY - currentY) * (endY - currentY) + (endX - currentX) * (endX - currentX)) * 10;

    return h;
}

void MainWindow::ButtonsGridChanged(CustomButton* changedButton)
{
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
            button->bIsStart = false;
            button->bIsEnd = false;
            button->bIsObstacle = false;
        }
    }

    if(StartButton == nullptr || EndButton == nullptr) return;

    PerfomAStar();
}

