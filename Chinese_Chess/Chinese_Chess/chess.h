#ifndef CHESS_H
#define CHESS_H

#ifndef PLAYSCENE_SIZE
#define PLAYSCENE_SIZE

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

    Chess chess[ROW][COL];
};

#endif // CHESS_H
