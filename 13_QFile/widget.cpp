#include "widget.h"
#include "ui_widget.h"

#include<QFileDialog>
#include<QFile>
#include<QTextCodec>
#include<QFileInfo>
#include<QDebug>
#include<QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 点击选取文件按钮，弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path = QFileDialog::getOpenFileName(this,"打开文件","E:\\project\\QTPro\\13_QFile");
        // 将路径放入lineedit
        ui->lineEdit->setText(path);
        // 读取内容，放入textEdit中
        // QFile默认支持的模式是utf-8
        // 编码格式类
        QTextCodec* codec = QTextCodec::codecForName("gbk");
        QFile file(path); // 参数就是读取文件的路径
        // 设置打开方式
        file.open(QIODevice::ReadOnly);
        // 按行读取数据
        QByteArray array;
        while(!file.atEnd())
        {
            array += file.readLine();
        }
        // 读取全部数据
        //QByteArray array = file.readAll();
        // 将读取的数据放入textEdit中
        ui->textEdit->setText(array);
        //ui->textEdit->setText(codec->toUnicode(array));

        // 操作完成后记得关闭
        file.close();

        // 进行写文件
//        file.open(QIODevice::Append); // 用追加的方式进行写
//        file.write("啊啊啊啊啊。。。。");
//        file.close();

        // QFileInfo 读取文档信息
        QFileInfo info(path);
        qDebug()<<"字节大小："<<info.size()<<" 后缀名："<<info.suffix()<<" 文件名称： "<< info.fileName() << " 文件路径： " << info.filePath();
        qDebug()<<"创建日期： "<< info.created().toString("yyyy/MM/dd hh:mm:ss");
        qDebug()<<"修改日期："<< info.lastModified().toString("yyyy/MM/dd hh:mm:ss");

    });
}

Widget::~Widget()
{
    delete ui;
}

