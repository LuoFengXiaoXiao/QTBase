#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

   // MyPushButton();
    ~MyPushButton();

signals:

};

#endif // MYPUSHBUTTON_H
