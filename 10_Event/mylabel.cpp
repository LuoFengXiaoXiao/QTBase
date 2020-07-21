#include "mylabel.h"

#include<QDebug>
#include<QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    // 设置鼠标追踪状态
    setMouseTracking(true);
}

// 鼠标进入事件
void myLabel::enterEvent(QEvent *event)
{
    qDebug()<<"鼠标进入了";
}

// 鼠标离开事件
void myLabel::leaveEvent(QEvent *)
{
    qDebug()<<"鼠标已离开";
}

// 鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
    // 按下鼠标左键并移动，打印信息
    //if(ev->buttons() & Qt::LeftButton){
        QString str = QString("鼠标已移动 x=%1  y =%2  globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    //}
}
// 鼠标按下
void myLabel::mousePressEvent(QMouseEvent *ev)
{
    // 当鼠标左键按下，打印信息
    if(ev->button() == Qt::LeftButton)
    {
        QString str = QString("鼠标已按下 x=%1  y =%2  globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    }
}
// 鼠标松开
void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    // 鼠标左键松开，打印信息
    if(ev->button() == Qt::LeftButton){
        QString str = QString("鼠标已松开 x=%1  y =%2  globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    }
}

bool myLabel::event(QEvent *e)
{
    // 如果是鼠标按下，在事件分发器中做拦截操作
    if(e->type() == QEvent::MouseButtonPress)
    {
        // 静态类型转换，父类转到子类
        QMouseEvent* ev = static_cast<QMouseEvent*>(e);
        QString str = QString("Event函数中：：鼠标已按下 x=%1  y =%2  globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;

        return true; // true代表用户自己处理这个事件，不向下分发
    }
    // 其他事件交给父类处理 默认处理
    return QLabel::event(e);
}
