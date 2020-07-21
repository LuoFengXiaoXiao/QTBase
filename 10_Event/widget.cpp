#include "widget.h"
#include "ui_widget.h"

#include<QTimer>
#include<QDebug>
#include<QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 启动定时器
    // 参数1：间隔 单位是毫秒
    id1 = startTimer(1000);
    id2 = startTimer(2000);

    // 第二种实现定时器的方式
    QTimer* timer = new QTimer(this);
    // 启动定时器
    timer->start(500);
    connect(timer,&QTimer::timeout,[=](){
        static int num = 1;
        // Label4每隔一秒加一
        ui->label_4->setText(QString::number(num++));
    });

    // 点击暂停按钮，停止计时器
    connect(ui->btn,&QPushButton::clicked,[=](){
        timer->stop();
    });

    // 给label1安装事件过滤器
    // 步骤1： 安装事件过滤器
    ui->label->installEventFilter(this);



}

// 步骤2：重写eventfilter事件
bool Widget::eventFilter(QObject* Obj,QEvent* e)
{
    if(Obj == ui->label){
        // 如果是鼠标按下，在事件分发器中做拦截操作
        if(e->type() == QEvent::MouseButtonPress)
        {
            // 静态类型转换，父类转到子类
            QMouseEvent* ev = static_cast<QMouseEvent*>(e);
            QString str = QString("事件过滤器中：：鼠标已按下 x=%1  y =%2  globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
            qDebug()<<str;

            return true; // true代表用户自己处理这个事件，不向下分发
        }
        // 其他事件交给父类处理 默认处理
        return QWidget::eventFilter(Obj,e);
    }
}

void Widget::timerEvent(QTimerEvent* ev)
{
    if(ev->timerId() == id1){
    static int num = 1;
    // Label2每隔一秒加一
    ui->label_2->setText(QString::number(num++));
    }

    if(ev->timerId() == id2){
    // Label3每隔两秒加1
    static int num2 = 1;
     ui->label_3->setText(QString::number(num2++));
    }
}


Widget::~Widget()
{
    delete ui;
}

