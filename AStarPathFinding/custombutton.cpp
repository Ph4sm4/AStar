#include "custombutton.h"
#include <QKeyEvent>

CustomButton::CustomButton(QWidget *parent)
    : QPushButton{parent}
{

}

void CustomButton::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::LeftButton){
        qDebug()<<"left pressed";
    }
    else if(e->key() == Qt::RightButton){
        qDebug()<<"right pressed";
    }
}
