#include "mainscene.h"
#include "ui_mainscene.h"

#include "mypushbotton.h"

#include<QPainter>
#include<QPushButton>
#include<QDebug>
#include<QTimer>
#include <QSound>


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 配置主场景
    // 设置固定大小
    setFixedSize(450,640);

    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    setWindowTitle(QString("CoinFilp"));

    // 退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
       this->close();
    });

    // 准备开始按钮的音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);


    // 开始按钮
    MyPushBotton* startBtn = new MyPushBotton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5- startBtn->width()*0.5,this->height()*0.75);

    // 实例化选择关卡的场景
    chooseScene = new ChooseLevelScene;

    // 监听选择关卡的返回按钮信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){

        // 设置自身场景的位置
        this->setGeometry(chooseScene->geometry());
        // 其中的this可以省略
        chooseScene->hide();  // 隐藏选择场景
        this->show(); // 显示主场景
    });

    // 开始按钮控制的事件
    connect(startBtn,&QPushButton::clicked,[=](){

        // 播放开始音效资源
        startSound->play();

        // 弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        // 延时进入到选择关卡场景
        QTimer::singleShot(500,this,[=](){

            // 设置chooseScene的场景位置
            chooseScene->setGeometry(this->geometry());
            // 自身隐藏
            // 显示选择关卡的场景
            this->hide();
            chooseScene->show();

        });

    });
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 画背景上的图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

