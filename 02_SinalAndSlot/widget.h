#ifndef WIDGET_H
#define WIDGET_H

#include "teacher.h"
#include "student.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Teacher* myTeacher;
    Student* st;

private:
    void ClassIsOver();
    void ClassIsOver_1();

};
#endif // WIDGET_H
