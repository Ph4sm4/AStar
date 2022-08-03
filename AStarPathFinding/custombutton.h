#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QWidget>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QPushButton *parent = nullptr);
    CustomButton(class QMainWindow* w);

    int x, y;
    int G; // distance from start
    int H; // distance to end
    int F; // g + h
    bool bIsStart = false;
    bool bIsEnd = false;
    bool bIsObstacle = false;
    CustomButton* parent = nullptr;

protected:
    virtual void mousePressEvent(QMouseEvent *e) override;

signals:
    void buttonPressed(class CustomButton* changedButton);
};

#endif // CUSTOMBUTTON_H
