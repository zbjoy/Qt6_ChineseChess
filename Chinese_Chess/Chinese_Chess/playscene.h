#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPainter>
#include <QMouseEvent>
#include <QStack>
#include <QMediaPlayer>
#include <QLabel>

#include "mypushbutton.h"
#include "chess.h"
#include "Move.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(ChessMap& tmepChessMap); //加载MainScene中的数据

    void iniUI();

    void paintEvent(QPaintEvent* e);

    void GameDraw(QPainter& painter);

    void ChessCheck();

    int isGameOver();

    void mousePressEvent(QMouseEvent *e);

    bool ChessMove(int i, int j);

    bool isCheckMate();

    void ChessReturn(); //悔棋

    bool isDeadlyStrike();

    QLabel* winLabel; //胜利图片

    QStack<ChessMap> chessBack;

    QRadioButton* btn_Complex;

    QMediaPlayer* checkmateSound; //将军的声音

    QMediaPlayer* moveSound; //移动声音

    QMediaPlayer* eatSound; //吃子声音

    QMediaPlayer* deadlyStrikeSound; //绝杀的声音

    int dead;

    ChessMap chessMap;

    int Checked_Row;
    int Checked_Col;

    int Jiang_Row;
    int Jiang_Col;

    int Shuai_Row;
    int Shuai_Col;

signals:

    void PlaySceneBack(); //发送返回信号给MainWidget中的MainScene_Exit

};

#endif // PLAYSCENE_H
