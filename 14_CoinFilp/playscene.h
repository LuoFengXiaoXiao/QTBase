#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    // 重写paintEvent事件
    void paintEvent(QPaintEvent *event);

public:

    int levelIndex; // 内部的成员函数 记录所选的关卡

    int gameArray[4][4]; // 二维数组 维护每隔关卡的具体数据

    // 用来保存是否胜利的条件
    MyCoin* coinBtn[4][4];

    // 是否胜利的标志
    bool isWin;


signals:

    // 返回按钮信号
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
