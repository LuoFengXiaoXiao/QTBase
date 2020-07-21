#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QPushButton>

class MyPushBotton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushBotton(QWidget *parent = nullptr);

    // 构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    MyPushBotton(QString normalImg,QString pressImg = "");

    // 成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    // 弹跳特效
    void zoom1(); // 向上弹跳
    void zoom2(); // 向下弹跳

    // 重写按钮的按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBOTTON_H
