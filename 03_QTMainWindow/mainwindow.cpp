#include "mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // 重置窗口大小
    resize(600,400);

    // 菜单栏创建，菜单栏只能有一个
    QMenuBar* Mbar = menuBar();
    // 将菜单栏放入窗口中
    setMenuBar(Mbar);
    // 设置菜单栏的颜色
    //Mbar{background-color:transparent;};
    // 创建菜单
    QMenu* fileMenu =  Mbar->addMenu("文件(F)");
    QMenu* editMenu =  Mbar->addMenu("编辑(E)");
    // 创建菜单项
    fileMenu->addAction("新建（N）");
    // 添加分割符/线
    fileMenu->addSeparator();
    QAction* openAction = fileMenu->addAction("打开（O）");

    // 工具栏创建，可以有多个
    QToolBar* toolBar = new QToolBar(this);
    // 将toolBar添加到窗口中
    addToolBar(Qt::LeftToolBarArea,toolBar);
    // 后期设置只允许左右停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    // 设置是否浮动
    toolBar->setFloatable(false);
    // 设置移动
    toolBar->setMovable(false);
    // 创建工具项
    toolBar->addAction("新建（N）");
    // 添加分割线
    toolBar->addSeparator();
    toolBar->addAction(openAction);
    // 添加控件（按钮）
    QPushButton* btn = new QPushButton("aa",this);
    toolBar->addWidget(btn);

    // 状态栏，最多有一个
    QStatusBar* stBar = statusBar();
    // 设置到窗口中
    setStatusBar(stBar);
    // 放标签控件
    QLabel* lable = new QLabel("提示信息",this);
    stBar->addWidget(lable);

    // 将标签放在右侧，需要技巧
    QLabel* lable2 = new QLabel("右侧提示信息",this);
    stBar->addPermanentWidget(lable2);

    // 铆接部件（浮动窗口），可以有多个
    QDockWidget* dockWidget = new QDockWidget("浮动窗口",this);
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget);
    // 设置后期停靠区域，只允许上下
    dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);

    // 设置核心部件（中心部件）,只能有一个
    QTextEdit* edit = new QTextEdit(this);
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{
}

