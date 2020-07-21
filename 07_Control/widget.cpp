#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置单选按钮男的默认值
    ui->rBtnMan->setChecked(true);

    // 选中女后，打印信息
    connect(ui->rBtnWoman,&QRadioButton::clicked,[=](){
       qDebug()<<"选中女人框";
    });

    // checkbox设置  stateChanged：参数 0是未选中，2是选中，1是半选
    connect(ui->cBBeijing,&QCheckBox::stateChanged,[=](int state){
        qDebug()<<"我是否选中了北京"<<state;
    });

    // 利用listWidget写诗
    QListWidgetItem* item = new QListWidgetItem("锄禾日当午");
    // 将一行诗放入到listWidget
    ui->listWidget->addItem(item);
    item->setTextAlignment(Qt::AlignHCenter);

    // QStringList 相当于 QList<QString>
    QStringList list;
    list<<"汗滴禾下土"<<"谁知盘中餐"<<"粒粒皆辛苦";
    // 该种方式无法设置居中
    ui->listWidget->addItems(list);

    // treeWidget树控件的使用
    // 设置水平头
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍"<<"难度系数");

    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem* minItem = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem* zhiItem = new QTreeWidgetItem(QStringList()<<"智力");
    // 加载顶层的节点
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhiItem);

    // 追加子节点
    QStringList heroL1;
    heroL1 << "刚被猪" << "前排坦克，能在吸收伤害的同时造成可观的范围输出"<<"一星";
    QTreeWidgetItem* l1 = new QTreeWidgetItem(heroL1);
    liItem->addChild(l1);

    // TableWTableWidget
    // 设置列数
    ui->tableWidget->setColumnCount(3);
    // 设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"年龄");
    // 设置行数
    ui->tableWidget->setRowCount(5);
    // 设置正文
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
    QStringList nameList;
    nameList<<"亚瑟"<<"妲己"<<"刘备"<<"赵云"<<"张飞";
    QList<QString> sexList;
    sexList<<"男"<<"女"<<"男"<<"男"<<"男";
    for (int i = 0;i<5;i++)
    {
        int col = 0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(sexList.at(i))); // at超限之后会抛出异常
        // int 转为 QString
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(i+18)));
    }

}

Widget::~Widget()
{
    delete ui;
}

