#include "widget.h"
#include "ui_widget.h"

#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 栈控件的修改
    // 设置默认的界面
    ui->stackedWidget->setCurrentIndex(0);
    // 关联按键进行切换
    connect(ui->Btn_Page1,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->Btn_Page2,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->Btn_Page3,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    // 下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("特斯拉");

    // 通过按钮设置下拉框选中的Item
    connect(ui->btn_Baoma,&QPushButton::clicked,[=](){
        ui->comboBox->setCurrentIndex(1);
    });
    connect(ui->btn_Benchi,&QPushButton::clicked,[=](){
        ui->comboBox->setCurrentIndex(0);
    });
    connect(ui->btn_Tesila,&QPushButton::clicked,[=](){
        ui->comboBox->setCurrentText("特斯拉");
    });

    // 利用QLabel显示图片
    ui->lbl_Image->setPixmap(QPixmap(":/Icon/New.jpg"));

    // 利用QLabel显示动图,只支持git格式
    QMovie* movie = new QMovie(":/Icon/Mario.gif");
    ui->lbl_movie->setMovie(movie);
    // 播放动图
    movie->start();

}

Widget::~Widget()
{
    delete ui;
}

