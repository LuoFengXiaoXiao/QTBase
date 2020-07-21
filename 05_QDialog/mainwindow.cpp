#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 点击新建按钮，弹出一个对话框
    connect(ui->actionNew,&QAction::triggered,[=](){
        // 对话框分为模态对话框和非模态对话框
        // 非模态对话框：创建之后可以对其他窗口进行操作
        // 模态对话框：创建之后不可以对其他窗口进行操作
        // 创建模态对话框,添加一个阻塞功能即可实现
//        QDialog dlg(this);
//        dlg.resize(200,100);
//        dlg.exec();
//        QDialog* dlg2 = new QDialog(this);
//        dlg2->resize(200,100);
//        dlg2->show();
//        // 因为指针不会自动释放，所以需要设置一个属性
//        dlg2->setAttribute(Qt::WA_DeleteOnClose);

//        //qDebug()<<"模态对话框弹出了";
//        qDebug()<<"非模态对话框弹出了";

        // 消息对话框
        // 错误对话框
        //QMessageBox::critical(this,"critical","错误");

        // 信息对话框
        //QMessageBox::information(this,"info","信息");

        // 提问对话框
        // 参数1:父亲 参数2：标题 参数3：提示内容 参数4：按键类型 参数5：默认的激活按键
        //QMessageBox::question(this,"question","问题");
        // 改变内置的按键
        //QMessageBox::question(this,"question","问题",QMessageBox::Save|QMessageBox::Cancel);
        // 设置默认的激活按键
        // 根据返回值做不同的操作
//        if(QMessageBox::Save == QMessageBox::question(this,"question","问题",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel))
//        {
//            qDebug()<<"老子点了保存";
//        }
//        else
//        {
//            qDebug()<<"老子点了取消";
//        }

        // 警告对话框
//        QMessageBox::warning(this,"warning","警告");

        // 其他标准对话框
        // 颜色对话框
//        QColor color = QColorDialog::getColor(QColor(255,0,0));
//        qDebug()<<"r = "<<color.red()<<"g = "<<color.green()<<"b = "<<color.blue();

        // 文件对话框
        // 参数1：父类 参数2：标题 参数3：默认打开的路径 参数4：读取的文档类型
//        QString str = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\zhens\\Desktop","(*.txt)");
//        qDebug()<<str;
        // 字体对话框
        bool flag;
        QFont font = QFontDialog::getFont(&flag,QFont("楷体",36));
        qDebug()<<"字体"<<font.family()<<"字号"<<font.pointSize()<<"是否加粗"<<font.bold()<<"是否倾斜"<<font.italic();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

