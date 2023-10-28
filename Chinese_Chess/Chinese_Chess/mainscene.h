#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <string>

#include "chess.h"
#include "mypushbutton.h"
#include "playscene.h"

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);

    void iniUI();

    //void debugChessMap();

    ChessMap chessMap;

    //Chess ChessMap[ROW][COL];
    //QString debug[ROW * COL];

    ~MainScene();

private:
    Ui::MainScene *ui;

};
#endif // MAINSCENE_H
