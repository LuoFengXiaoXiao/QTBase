#include "widget.h"
#include "./ui_widget.h"

#include <QPushButton>
#include <QDebug>

// Teacher类 老师类
// Student类 学生类
// 下课后，老师触发一个信号，饿了，学生响应信号，请客吃饭

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 创建一个老师对象
    this->myTeacher = new Teacher(this);
    // 创建一个学生对象
    this->st = new Student(this);

    // 将两者进行连接,老师饿了，学生请客
    void(Teacher::*teacherSignal_1)() = &Teacher::hungry;
    void(Student::*studentSlot_1)() = &Student::treat;
    //connect(myTeacher,teacherSignal_1,st,studentSlot_1);

    // 调用下课函数
    //ClassIsOver();

    // 连接带参数的信号和槽
    // 指针->地址
    // 函数指针->函数地址
    void(Teacher::*teacherSignal)(QString) = &Teacher::hungry;
    void(Student::*studentSlots)(QString) = &Student::treat;
    connect(myTeacher,teacherSignal,st,studentSlots);

    // 调用下课函数
    //ClassIsOver();

    // 点击下课的按钮，再触发下课
    QPushButton* btn = new QPushButton("下课",this);
    btn->resize(200,30);
    connect(btn,&QPushButton::clicked,this,&Widget::ClassIsOver);


    QPushButton* btn_1 = new QPushButton("下课吃饭",this);
    btn_1->resize(200,30);
    btn_1->move(0,30);
    connect(btn_1,&QPushButton::clicked,this,&Widget::ClassIsOver_1);
    // 信号连接信号
    //connect(btn_1,&QPushButton::clicked,myTeacher,teacherSignal);

    // qt4连接无参版本
    // 优点是直观，缺点是类型不做检测
    connect(myTeacher,SIGNAL(hungry()),st,SLOT(treat()));

//    [=](){
//        btn->setText("滚蛋");
//    }();

//    [btn](){
//        btn->setText("滚蛋");
//    }();

//    QPushButton* myBtn = new QPushButton(this);
//    QPushButton* myBtn2 = new QPushButton(this);
//    myBtn2->move(100,100);
//    int m = 10;

//    connect(myBtn,&QPushButton::clicked,this,[m]()mutable{m = 100+10;qDebug()<<m});
//    connect(myBtn2,&QPushButton::clicked,this,[=](){qDebug()<<m});
//    int ret = []()->int{return 1000;}();
//    qDebug()<<ret;
    QPushButton* btn2 = new QPushButton(this);
    btn2->setText("关闭");
    btn2->move(200,60);
    btn2->resize(60,30);
    connect(btn2,&QPushButton::clicked,this,[=](){
        emit myTeacher->hungry("宫保鸡丁");
        this->close();
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::ClassIsOver()
{
    // 下课函数触发老师饿了
    emit myTeacher->hungry();
    //emit myTeacher->hungry("宫爆鸡丁");
}

void Widget::ClassIsOver_1()
{
    // 下课函数触发老师饿了
    //emit myTeacher->hungry();
    emit myTeacher->hungry("宫爆鸡丁");
}
