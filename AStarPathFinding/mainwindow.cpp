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
    const int INF = INT_MAX;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            CustomButton *customButton = new CustomButton(this);
            customButton->setFixedSize(60, 60);
            customButton->setStyleSheet("background-color: #707070;");
            customButton->x = j;
            customButton->y = i;
            customButton->G = INF;
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
    QList<CustomButton*> open;
    QList<CustomButton* > closed;

    StartButton->G = 0;
    StartButton->F = 0;
    EndButton->F = 0;
    EndButton->G = INT_MAX;

    open.append(StartButton);
    bool pathFound = false;

    while(!open.isEmpty()){
        CustomButton* current = open.first();
        open.removeOne(current);
        closed.append(current);

        if(current == EndButton){
            pathFound = true;
            break;
        }

        QList<CustomButton*> neighbours = getNeighbours(current);
        for(auto neighbour : neighbours){
            if(neighbour->bIsObstacle || closed.contains(neighbour)) continue;

            if(neighbour != EndButton)
                neighbour->setStyleSheet("background-color: lightblue;");

            if(neighbour->G > current->G + 10 || !open.contains(neighbour)){
                neighbour->G = current->G + 10;
                neighbour->F = neighbour->G + neighbour->H;
                neighbour->parent = current;
                /*
                    this will execute only if the node has not yet been considered
                    or when new shortest path to that node from starting point has been found 
                    (distance from currently considered neighbour + 10 is smaller than the previous one)
                */
                if(!open.contains(neighbour)){
                    open.append(neighbour);
                }
                
            }
//            if(neighbour != EndButton){
//                QString F = QString::number(neighbour->F);
//                QString G = QString::number(neighbour->G);
//                QString H = QString::number(neighbour->H);
//                neighbour->setText(F + ":" + G + ":" + H);
//            }
        }

        std::sort(open.begin(), open.end(), [](const CustomButton* a, const CustomButton* b)->bool {
            if(a->F != b->F) return a->F < b->F;

            return a->G < b->G;
        });
    }
    if(pathFound){
        CustomButton* parent = EndButton->parent;

        while(parent){
            if(parent == StartButton) break;

            parent->setStyleSheet("background-color: red;");
            auto temp = parent->parent;
            parent = temp;
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
        output.append(neighbour);
    }
    if(currentX + 1 < columns){
        neighbour = grid[currentY][currentX + 1];
        neighbour->H = getHeuristic(neighbour);
        output.append(neighbour);
    }
    if(currentY - 1 >= 0){
        neighbour = grid[currentY - 1][currentX];
        neighbour->H = getHeuristic(neighbour);
        output.append(neighbour);
    }
    if(currentY + 1 < rows){
        neighbour = grid[currentY + 1][currentX];
        neighbour->H = getHeuristic(neighbour);
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

    int h = ceil(qSqrt((endY - currentY) * (endY - currentY) + (endX - currentX) * (endX - currentX)) * 10); 
    // we multiply by 10 in order to ensure having integer values as distances between the nodes (between 2 neighbouring nodes distance will be 10 across and 14 diagonally)

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

