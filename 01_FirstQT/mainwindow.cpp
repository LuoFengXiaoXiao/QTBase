#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"

#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建一个按钮
    QPushButton* btn = new QPushButton;
    //btn->show(); // show以顶层的fang方式弹出窗口控件
    btn->setParent(this);
    btn->setText(QString("牛逼"));
    btn->resize(50,30);
    btn->move(50,50);

    QPushButton* btn2 = new QPushButton("牛逼哄哄",this);

    // 创建一个自己按钮类的对象
    MyPushButton* myBtn = new MyPushButton;
    myBtn->setText("我自己的按钮");
    myBtn->move(200,200);
    myBtn->setParent(this);
    myBtn->resize(200,30);

    //需求 点击我的按钮，关闭窗口
    //参数1 信号的发送者 参数2 发送的信号（函数的地址） 参数3 信号的接收者 参数4 处理的槽函数
    connect(myBtn,&QPushButton::clicked,this,&QMainWindow::close);


}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"mainWindow的析构调用";
}

