#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>


class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);

    // 鼠标进入事件
    void enterEvent(QEvent *event);

    // 鼠标离开事件
    void leaveEvent(QEvent *);

    // 其他鼠标事件
    // 鼠标移动
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    // 鼠标按下
    virtual void mousePressEvent(QMouseEvent *ev) override;
    // 鼠标松开
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;

    // 通过event事件分发器 拦截鼠标按下事件
    bool event(QEvent *e) override;

signals:

};

#endif // MYLABEL_H
