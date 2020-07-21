#include "playscene.h"
#include "mypushbotton.h"
#include "mycoin.h"
#include "dataconfig.h"


#include <QDebug>
#include <QString>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    // 初始化游戏场景
    // 设置固定大小
    this->setFixedSize(450,640);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    QString strlevel = QString("Level_%1").arg(levelNum);
    this->setWindowTitle(strlevel);

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

    // 添加音效资源
    // 返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);
    // 翻金币的音效
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav",this);
    // 胜利按钮音效
    QSound* winSound = new QSound(":/res/LevelWinSound.wav",this);

    // 返回按钮
    MyPushBotton* backBtn = new MyPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-10,this->height()-backBtn->height()-10);

    // 点击返回
    connect(backBtn,&MyPushBotton::clicked,[=](){
        qDebug()<<"翻金币场景，点击了返回按钮";
        // 告诉主场景 我返回了，主场景需要监听选择关卡场景的状态（ChooseLevelScene的按钮状态）
        // this->hide();
        // 播放返回按钮音效
        backSound->play();
        // 延时返回
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    // 显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString strLevelShow = QString("level: %1").arg(this->levelIndex);
    label->setText(strLevelShow);
    // 将字体设置到标签控件中
    label->setFont(font);
    label->setGeometry(30,this->height()-50,120,50);


    dataConfig config;
    // 初始化每个关卡的二维数组
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    // 胜利图片显示,加载到了窗口上方
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());


    // 显示金币背景的图案
    for(int i = 0;i<4;i++){
        for (int j = 0; j < 4; ++j) {
            // 绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(125+i*50,200+j*50);

            // 创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                // 显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(127+i*50,204+j*50);

            // 给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];  // 1正面，2反面

            // 将金币放入金币的二维数组里，以便后期的维护
            coinBtn[i][j] = coin;

            // 点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){

                // 点击翻金币的音效
                flipSound->play();

                // 鼠标点击的瞬间，禁用所有按钮
                for(int i = 0;i<4;i++)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] ==  0 ? 1 : 0;

                // 翻转周围硬币,延时翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX + 1 <= 3) // 周围右侧金币翻转的条件
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posY + 1 <= 3) // 周围上侧金币翻转的条件
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    if(coin->posY - 1 >= 0) // 周围上侧金币翻转的条件
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    // 鼠标事件完成之后，解禁所有按钮
                    for(int i = 0;i<4;i++)
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    // 判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if(coinBtn[i][j]->flag == false) // 只要有一个是反面，就判断为不胜利
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        // 胜利了
                        qDebug()<<"游戏胜利";
                        // 添加胜利的音效
                        winSound->play();
                        // 将所有按钮的胜利的标志改为true
                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        // 将胜利的图片移动下来
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
                        // 设置动画的事件间隔
                        animation->setDuration(1000);
                        // 设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        // 设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+110,winLabel->width(),winLabel->height()));
                        // 设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        // 执行动画
                        animation->start();
                    }
                });

            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *event)
{
    // 创建背景
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
