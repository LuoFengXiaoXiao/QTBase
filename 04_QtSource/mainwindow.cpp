#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 绝对路径很难保证存在
    //ui->actionNew_2->setIcon(QIcon("C:/Users/zhens/Desktop/Icon/New.jpg"));

    // 使用添加的Qt资源 “：+ 前缀名 + 文件名”
    ui->actionNew_2->setIcon(QIcon(":/Icon/New.jpg"));
    ui->actionOpen->setIcon(QIcon(":/Icon/Open.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

