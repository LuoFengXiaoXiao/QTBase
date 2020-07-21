#include "widget.h"
#include "ui_widget.h"

#include<QPainter> // 画家类

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 点击按钮移动的事件
    connect(ui->btn,&QPushButton::clicked,[=](){
        // 手动调用绘图事件，用update更新
        posx+=20;
        if(posx>this->width()){
            posx = 20;
        }
        update();
    });
}

void Widget::paintEvent(QPaintEvent*)
{
    // 不用去调用，系统会自动调用
    // 实例化画家对象  this指定的是绘图的设备
    QPainter painter(this);

    // 设置画笔
    QPen pen(QColor(255,0,0));
    // 设置画笔宽度
    pen.setWidth(3);
    // 设置画笔的风格
    pen.setStyle(Qt::DotLine);
    // 让画家使用这个画笔
    painter.setPen(pen);

    // 设置画刷，为封闭图形填充颜色
    QBrush brush(Qt::cyan);
    // 设置画刷风格
    brush.setStyle(Qt::Dense7Pattern);
    painter.setBrush(brush);


    // 绘制一条直线
    painter.drawLine(QPoint(0,0),QPoint(100,100));
    // 绘制一个圆
    painter.drawEllipse(QPoint(100,100),50,50);
    // 绘制一个矩形
    painter.drawRect(QRect(QPoint(100,100),QSize(50,50)));
    // 绘制文字
    painter.drawText(QPoint(150,150),QString("你竟然想上天"));

//    ///////////////////////////高级设置////////////////////////
//    QPainter painter(this);
//    painter.drawEllipse(QPoint(100,50),50,50);
//    // 设置抗锯齿的能力 效率较低
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawEllipse(QPoint(200,50),50,50);

//    // 绘制矩形
//    painter.drawRect(QRect(20,150,50,50));
//    // 设置画家位移参数
//    painter.translate(20,20);
//    // 保存画家状态
//    painter.save();
//    painter.drawRect(QRect(20,150,50,50));
//    // 设置画家位移参数
//    painter.translate(20,20);
//    // 还原画家保存状态
//    painter.restore();
//    painter.drawRect(QRect(20,150,50,50));

//    //////////////////////利用画家 画资源图片///////////////////
//    QPainter painter(this);
//    painter.drawPixmap(posx,20,QPixmap(":/Image/Luffy.png"));
}

Widget::~Widget()
{
    delete ui;
}

