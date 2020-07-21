#include "widget.h"
#include "ui_widget.h"

#include<QPixmap>
#include<QPainter>
#include<QImage>
#include<QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    // Pixmap绘图设备,专门为平台做了显示优化
//    QPixmap pix(300,300);

//    // 填充背景色
//    pix.fill(Qt::white);

//    // 声明画家
//    QPainter painter(&pix);
//    painter.setPen(QPen(Qt::green));
//    painter.drawEllipse(QPoint(150,150),100,100);

//    // 保存绘制的图片
//    pix.save("E:\\project\\QTPro\\PaintImage\\pix.png");

//    // QImage 绘图设备 可以对像素进行访问
//    QImage img(300,300,QImage::Format_RGB32);
//    // 填充背景色
//    img.fill(Qt::blue);

//    // 声明画家
//    QPainter painter(&img);
//    painter.setPen(QPen(Qt::red));
//    painter.drawEllipse(QPoint(150,150),100,100);

//    // 保存绘制的图片
//    img.save("E:\\project\\QTPro\\PaintImage\\img.png");

    // QPicture 绘图设备 可以记录和重现绘图指令
    QPicture pic;
    QPainter painter;
    painter.begin(&pic);  // 开始绘制

    painter.setPen(QPen(Qt::cyan));
    painter.drawEllipse(QPoint(150,150),100,100);

    painter.end(); // 绘制完成

    // 保存到磁盘 任意后缀名，像是被加密的文件
    pic.save("E:\\project\\QTPro\\PaintImage\\pic.wx");

}

 void Widget::paintEvent(QPaintEvent *event)
 {
//     QPainter painter(this);
//     // 利用QImage对像素进行修改
//     QImage img;
//     img.load(":/Image/Luffy.png");

//     // 修改像素点
//     for(int i =50 ; i < 100 ; i++)
//     {
//         for (int j = 50;j<100;j++)
//         {
//            QRgb value = qRgb(255,0,0);
//            img.setPixel(i,j,value);
//         }
//     }

//     painter.drawImage(0,0,img);


     QPainter painter(this);
     // 重现QPicture的绘图指令
     QPicture pic;
     pic.load("E:\\project\\QTPro\\PaintImage\\pic.wx");
     painter.drawPicture(0,0,pic);
 }

Widget::~Widget()
{
    delete ui;
}

