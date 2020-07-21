#include "mycoin.h"

#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnimg)
{
    QPixmap pix;
    bool ret = pix.load(btnimg);
    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(btnimg);
        qDebug()<<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    // 初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    // 信号槽连接,监听信号 正面翻反面
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);


        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        // 判断是否翻完，翻完之后将min重置为1
        if(this->min>this->max)
        {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }

    });

    // 监听反面翻正面
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);


        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        // 判断是否翻完，翻完之后将min重置为1
        if(this->min>this->max)
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }

    });

    // 胜利标志
    isWin = false;
}

// 反转金币的方法
void MyCoin::changeFlag()
{
    // 如果是正面，翻成反面
    if(this->flag)
    {
        // 开启正面翻反面的定时器
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else // 如果是正面，翻转成反面
    {
        // 开启反面翻正面的定时器
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}

// 按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
