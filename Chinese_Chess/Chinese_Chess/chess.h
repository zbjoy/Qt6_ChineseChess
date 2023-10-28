#ifndef CHESS_H
#define CHESS_H

#ifndef PLAYSCENE_SIZE
#define PLAYSCENE_SIZE

#include <QObject>
#include <QFile>
#include <QTextStream>

#define INTERVAL 50 //间隔
#define CHESS_GRID_SIZE 70  //格子宽度
#define ROW 10
#define COL 9
#define SIZE 60
#define BUTTON_SIZE 20
#define PLAYSCENEBUTTON_LEFT_EXIT 650
#define PLAYSCENEBUTTON_RIGHT_EXIT 750
#define PLAYSCENEBUTTON_TOP_EXIT 300
#define PLAYSCENEBUTTON_BOTTOM_EXIT 360

#endif

class Chess
{
public:
    Chess();

    int type;

    bool Select;
};

class ChessMap
{
public:

    ChessMap();

    void iniChessMap();

    void saveChessMap();

    void infoChessMap();

    bool Player; //true为红走

    int isWin; //0 继续    1 红赢     2 黑赢

    Chess chess[ROW][COL];

    QString debug[ROW * COL];
};

#endif // CHESS_H
