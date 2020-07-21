#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:

public slots:
    // 5.14之后，槽函数可以写在该位置，也可以写为全局，也可以直接写在public下边（版本较早的必须写在此处）
    // 返回值也是 void
    // 需要声明和实现，可以有参数，可以发生重载
    void treat();
    void treat(QString foodName);
};

#endif // STUDENT_H
