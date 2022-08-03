#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QWidget>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = nullptr);

    int x, y;
    int G; // distance from start
    int H; // distance to end
    int F; // g + h
    CustomButton* parent;

protected:
    virtual void keyPressEvent(class QKeyEvent *e) override;

signals:

};

#endif // CUSTOMBUTTON_H
