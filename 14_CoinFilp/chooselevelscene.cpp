#include "chooselevelscene.h"
#include "mypushbotton.h"

#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    // 配置选择关卡场景
    this->setFixedSize(450,640);

    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("Choose Level");

    // 创建菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    // 创建开始菜单
    QMenu* startMenu =  bar->addMenu("Start");

    // 创建退出的菜单项
    QAction* quitAction = startMenu->addAction("Quit");

    // 点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });

    // 选择关卡音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    // 返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);

    // 返回按钮
    MyPushBotton* backBtn = new MyPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-10,this->height()-backBtn->height()-10);

    // 点击返回
    connect(backBtn,&MyPushBotton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        // 告诉主场景 我返回了，主场景需要监听选择关卡场景的状态（ChooseLevelScene的按钮状态）
        // this->hide();
        // 播放返回音效
        backSound->play();
        // 延时返回
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    // 选择关卡的按钮
    for(int i = 0;i<20;i++)
    {
        MyPushBotton* menuBtn = new MyPushBotton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(100 + i%4 * 70,170 + i/4 * 70);

        // 监听每个按钮的点击事件
        connect(menuBtn,&MyPushBotton::clicked,[=](){
            QString str = QString("您选择的是第 %1 关").arg(i+1);
            qDebug()<<str;

            // 播放选择关卡的音效
            chooseSound->play();

            // 进入游戏场景
            // 将选关场景隐藏掉
            this->hide();
            play = new PlayScene(i+1); // 创建游戏场景
            // 设置窗口的位置
            play->setGeometry(this->geometry());
            play->show(); // 显示游戏场景

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });


        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(100 + i%4 * 70,170 + i/4 * 70);
        // 设置label上的文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // 此时Label盖上了按钮，需要穿透进去,设置穿透事件 51号QWidget的属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载背景
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width()*1.2)*0.5,30,pix.width()*1.2,pix.height()*1.2,pix);
}
