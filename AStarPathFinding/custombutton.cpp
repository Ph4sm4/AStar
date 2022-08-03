#include "custombutton.h"
#include <QKeyEvent>
#include "mainwindow.h"

CustomButton::CustomButton(QPushButton *parent)
    : QPushButton{parent}
{

}

CustomButton::CustomButton(QMainWindow *w)
{
    connect(this, SIGNAL(buttonPressed(CustomButton*)), w, SLOT(ButtonsGridChanged(CustomButton*)));
}

void CustomButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        bIsStart = true;
        bIsEnd = false;
        bIsObstacle = false;
        emit buttonPressed(this);
    }
    else if(e->button() == Qt::RightButton){
        bIsStart = false;
        bIsEnd = true;
        bIsObstacle = false;
        emit buttonPressed(this);
    }
    else if (e->button() == Qt::MiddleButton && bIsObstacle){
        bIsStart = false;
        bIsEnd = false;
        bIsObstacle = false;
        emit buttonPressed(this);
    }
    else if (e->button() == Qt::MiddleButton){
        bIsStart = false;
        bIsEnd = false;
        bIsObstacle = true;
        emit buttonPressed(this);
    }
}
