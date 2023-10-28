#include "playscene.h"

#include <iostream>
#include <QDebug>

//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}


PlayScene::PlayScene(ChessMap& tempChessMap)
{
    //chessMap.chess[9][0].type = 20;

    chessMap = tempChessMap;
    Checked_Row = -1;
    Checked_Col = -1;
    dead = 0;

    iniUI();
}

void PlayScene::iniUI()
{
    this->setWindowIcon(QIcon(":/res/WindowIcon.png"));
    this->setFixedSize(800, 800);

    winLabel = new QLabel(this);

    QPixmap tmpPix;
    tmpPix.load(":/res/RedWin.png");
    //winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setGeometry(600, 100, 100, 100);
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->hide();

    checkmateSound = new QMediaPlayer(this);
    moveSound = new QMediaPlayer(this);
    eatSound = new QMediaPlayer(this);
    deadlyStrikeSound = new QMediaPlayer(this);
    checkmateSound->setMedia(QMediaContent(QUrl("qrc:/res/checkmate.mp3")));
    moveSound->setMedia(QMediaContent(QUrl("qrc:/res/move.mp3")));
    eatSound->setMedia(QMediaContent(QUrl("qrc:/res/eat.mp3")));
    deadlyStrikeSound->setMedia(QMediaContent(QUrl("qrc:/res/deadlyStrike.mp3")));
    checkmateSound->setVolume(100);
    moveSound->setVolume(50);
    eatSound->setVolume(50);
    deadlyStrikeSound->setVolume(50);

    MyPushButton* btn_Exit = new MyPushButton(":/res/Exit1.jpg", 100, 60, ":/res/Exit2.jpg");
    btn_Exit->setParent(this);
    //btn_Exit->resize(100, 60);
    btn_Exit->move(650, 420);
    //btn_Exit->setText("退出");

    MyPushButton* btn_Again = new MyPushButton(":/res/Again1.jpg", 100, 60, ":/res/Again2.jpg");
    btn_Again->setParent(this);
    //btn_Again->resize(100, 60);
    btn_Again->move(650, 320);
    //btn_Again->setText("重新开始");

    MyPushButton* btn_Back = new MyPushButton(":/res/Back1.jpg", 100, 60, ":/res/Back2.jpg");
    btn_Back->setParent(this);
    //btn_Back->resize(100, 60);
    btn_Back->move(650, 220);
    //btn_Back->setText("悔棋");

    btn_Complex = new QRadioButton(this);
    btn_Complex->setChecked(false);
    //btn_Complex->resize(100, 60);
    btn_Complex->move(670, 30);
    btn_Complex->setText("更多特效");



    connect(btn_Exit, MyPushButton::clicked, [=](){

        btn_Exit->zoom1();
        btn_Exit->zoom2();

        emit PlaySceneBack();
    });

    connect(btn_Again, MyPushButton::clicked, [=](){
        if(Checked_Row != -1)
        chessMap.chess[Checked_Row][Checked_Col].Select = false;
        Checked_Row = -1;
        Checked_Col = -1;
        winLabel->hide();

        chessBack.clear();

        chessMap.iniChessMap();
        chessMap.saveChessMap();

        update();
    });

    connect(btn_Back, MyPushButton::clicked, [=](){
        winLabel->hide();
        ChessReturn();
    });
}

void PlayScene::ChessReturn()
{
    if(!chessBack.isEmpty())
    {
        // ChessHistory chesshistory1; //好像不能直接创建变量
        // chesshistory1 = ChessBack.top();
        chessMap = chessBack.top();
        chessBack.pop_back();

        update();
    }
}

void PlayScene::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    QColor color(252, 215, 162);
    painter.setBrush(color);
    painter.drawRect(0, 0, 800, 800);

    GameDraw(painter); //参考

    e->accept();
}
void PlayScene::GameDraw(QPainter& painter)   //参数和思路是借鉴b站视频
{
    QPen pen;
    pen.setColor(QColor(Qt::black));
    pen.setWidth(2);
    painter.setPen(pen);
    //画棋盘
    for (int i = 0; i < ROW; i++)
    {
        //画横线
        painter.drawLine(INTERVAL, i * CHESS_GRID_SIZE + INTERVAL
                         , CHESS_GRID_SIZE * (COL - 1) + INTERVAL, i * CHESS_GRID_SIZE + INTERVAL);

        if (i < COL)
        {
            //画竖线
            painter.drawLine(i * CHESS_GRID_SIZE + INTERVAL, INTERVAL
                             , i * CHESS_GRID_SIZE + INTERVAL, CHESS_GRID_SIZE * (ROW - 1) + INTERVAL);
        }
    }

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(3 * CHESS_GRID_SIZE + INTERVAL, INTERVAL, 5 * CHESS_GRID_SIZE + INTERVAL, 2 * CHESS_GRID_SIZE + INTERVAL);
    painter.drawLine(5 * CHESS_GRID_SIZE + INTERVAL, INTERVAL, 3 * CHESS_GRID_SIZE + INTERVAL, 2 * CHESS_GRID_SIZE + INTERVAL);

    painter.drawLine(3 * CHESS_GRID_SIZE + INTERVAL, 9 * CHESS_GRID_SIZE + INTERVAL, 5 * CHESS_GRID_SIZE + INTERVAL, 7 * CHESS_GRID_SIZE + INTERVAL);
    painter.drawLine(3 * CHESS_GRID_SIZE + INTERVAL, 7 * CHESS_GRID_SIZE + INTERVAL, 5 * CHESS_GRID_SIZE + INTERVAL, 9 * CHESS_GRID_SIZE + INTERVAL);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    //显示楚河, 汉界
    painter.drawRect(INTERVAL, (ROW / 2 - 1) * CHESS_GRID_SIZE + INTERVAL
                     , (COL - 1) * CHESS_GRID_SIZE, CHESS_GRID_SIZE);
    QPen penRiver;
    penRiver.setColor(Qt::black);
    penRiver.setWidth(5);
    painter.setPen(penRiver);
    QFont fontRiver;
    fontRiver.setPointSize(35);
    fontRiver.setFamily("Microsoft YaHei");
    painter.setFont(fontRiver);
    painter.drawText(INTERVAL, (ROW / 2 - 1) * CHESS_GRID_SIZE + INTERVAL - 5, (COL - 1) * CHESS_GRID_SIZE, CHESS_GRID_SIZE, 20,  "楚河   汉界");

    QFont fontPlayerTip;
    fontPlayerTip.setPointSize(23);
    painter.setFont(fontPlayerTip);

    if(chessMap.Player == true)
    {
        painter.setPen(Qt::red);
        painter.drawText(630, 200, "红方走棋");
    }
    else
    {
        painter.setPen(Qt::black);
        painter.drawText(630, 550, "黑方走棋");
    }

    ChessCheck();
}

void PlayScene::ChessCheck()
{
    //QPainter TipPainter(this);
    QPainter ChessPainter(this);

    if(chessMap.isWin == 0)
    {
        chessMap.isWin = isGameOver(); //判断是否胜利并记录两边将帅的坐标

        if(chessMap.isWin == 0)
        {
            chessMap.isWin = dead;
        }

        for(int i = 0; i < ROW; i++)
        {
            for(int j = 0; j < COL; j++)
            {
                if(chessMap.chess[i][j].type != 0 && chessMap.chess[i][j].Select == false)
                {
                    QPen ChessPen;
                    ChessPen.setColor(QColor(Qt::black));
                    ChessPen.setWidth(2);
                    ChessPainter.setPen(ChessPen);
                    ChessPainter.setBrush(QBrush(QColor(Qt::white)));
                    //Chess.setPen(Qt::NoPen);
                    ChessPainter.drawEllipse(QPoint(INTERVAL + j * CHESS_GRID_SIZE, INTERVAL + i * CHESS_GRID_SIZE), 25, 25);
                    QFont font;
                    font.setPointSize(23);
                    ChessPainter.setFont(font);
                    QString ChessName = "兵炮车马相士帅卒炮车马象士将";
                    if(chessMap.chess[i][j].type >= 1 && chessMap.chess[i][j].type <= 7)
                    {
                        ChessPainter.setPen(Qt::red);
                    }
                    else if(chessMap.chess[i][j].type >= 8 && chessMap.chess[i][j].type <= 14)
                    {
                        ChessPainter.setPen(Qt::black);
                    }

                    ChessPainter.drawText(QPoint(INTERVAL + j * CHESS_GRID_SIZE - 18, INTERVAL + i * CHESS_GRID_SIZE + 13), ChessName.mid(chessMap.chess[i][j].type - 1, 1));
                }
                else if(chessMap.chess[i][j].type != 0 && chessMap.chess[i][j].Select == true)
                {
                    QPen ChessPen;
                    ChessPen.setColor(QColor(Qt::black));
                    ChessPen.setWidth(2);
                    ChessPainter.setPen(ChessPen);
                    ChessPainter.setBrush(QBrush(QColor(Qt::white)));
                    //Chess.setPen(Qt::NoPen);
                    ChessPainter.drawEllipse(QPoint(INTERVAL + j * CHESS_GRID_SIZE, INTERVAL + i * CHESS_GRID_SIZE), 30, 30);
                    QFont font;
                    font.setPointSize(30);
                    ChessPainter.setFont(font);


//                    TipPainter.setPen(ChessPen);
//                    TipPainter.setFont(font);


                    QString ChessName = "兵炮车马相士帅卒炮车马象士将";
                    if(chessMap.chess[i][j].type >= 1 && chessMap.chess[i][j].type <= 7)
                    {
                        ChessPainter.setPen(Qt::red);
                    }
                    else if(chessMap.chess[i][j].type >= 8 && chessMap.chess[i][j].type <= 14)
                    {
                        ChessPainter.setPen(Qt::black);
                    }

                    ChessPainter.drawText(QPoint(INTERVAL + j * CHESS_GRID_SIZE - 25, INTERVAL + i * CHESS_GRID_SIZE + 16), ChessName.mid(chessMap.chess[i][j].type - 1, 1));
                    chessMap.chess[i][j].Select = false;

                    //添加提示
                    ChessPainter.setBrush(Qt::NoBrush);
                    for(int i1 = 0; i1 < ROW; i1++)
                    {
                        for(int j1 = 0; j1 < COL; j1++)
                        {
                            bool Judge = ChessMove(i1, j1);

                            if(Judge)
                            {
                                ChessPainter.setBrush(Qt::white);

                                if(chessMap.chess[i1][j1].type != 0)
                                {
                                    ChessPainter.setBrush(Qt::red);
                                    //ChessPainter.drawEllipse(QPoint(INTERVAL + j1 * CHESS_GRID_SIZE, INTERVAL + i1 * CHESS_GRID_SIZE), 5, 5);
                                    //std::cout << "chess[" << i1 << "][" << j1 << "] ";
                                    //qDebug() << "chess[" << i1 << "][" << j1 << "] ";
                                }
//                                std::cout << "chess[" << i1 << "][" << j1 << "] ";
                                ChessPainter.drawEllipse(QPoint(INTERVAL + j1 * CHESS_GRID_SIZE, INTERVAL + i1 * CHESS_GRID_SIZE), 5, 5);
                            }
                        }
                    }
                }
            }
        }
    }

    if(chessMap.isWin == 1) // 红胜利
    {
        winLabel->move(650, 100);
        winLabel->show();
        dead = 0;
        //chessBack.clear();
    }
    else if(chessMap.isWin == 2) //黑胜利
    {
        winLabel->move(650, 550);
        winLabel->show();
        dead = 0;
        //chessBack.clear();
    }
}

int PlayScene::isGameOver()
{
    int ret = 2;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 3; j < 6; j++)
        {
            if(chessMap.chess[i][j].type == 7)
            {
                ret = 1;
                Shuai_Row = i;
                Shuai_Col = j;
                break;
            }
        }
    }
    if(ret == 2)
    {
        return ret;
    }

    for(int i = 7; i < 10; ++i)
    {
        for(int j = 3; j < 6; ++j)
        {
            if(chessMap.chess[i][j].type == 14)
            {
                ret = 0;
                Jiang_Row = i;
                Jiang_Col = j;
                break;
            }
        }
    }
    return ret;
}

void PlayScene::mousePressEvent(QMouseEvent *e)
{
    if(chessMap.isWin == 0)
    {
        int i = (e->pos().y() + 35 - INTERVAL) / CHESS_GRID_SIZE;
        int j = (e->pos().x() + 35 - INTERVAL) / CHESS_GRID_SIZE;
        if(e->button() & Qt::LeftButton && (
            (Checked_Row == -1 && Checked_Col == -1)
         || ((chessMap.chess[Checked_Row][Checked_Col].type >= 1 && chessMap.chess[Checked_Row][Checked_Col].type <= 7) && (chessMap.chess[i][j].type >= 1 && chessMap.chess[i][j].type <= 7))
         || ((chessMap.chess[Checked_Row][Checked_Col].type >= 8 && chessMap.chess[Checked_Row][Checked_Col].type <= 14) && (chessMap.chess[i][j].type >= 8 && chessMap.chess[i][j].type <= 14))))
        {
            if(chessMap.Player == true && chessMap.chess[i][j].type >= 1 && chessMap.chess[i][j].type <= 7)
            {
                chessMap.chess[i][j].Select = true;
                this->Checked_Row = i;
                this->Checked_Col = j;
            }
            else if(chessMap.Player == false && chessMap.chess[i][j].type >= 8 && chessMap.chess[i][j].type <= 14)
            {
                chessMap.chess[i][j].Select = true;
                this->Checked_Row = i;
                this->Checked_Col = j;
            }

            update();
        }
        else if((e->button() & Qt::LeftButton) && Checked_Row != -1 && Checked_Col != -1)
        {
            bool Judge = ChessMove(i, j);

            //this->ChessMap[i][j] = 14;
            //                    ChessMap[i][j].Select = false;
            //                    this->Checked = false;
            //this->paintEvent(this);
            //this->ChessCheck(ChessMap);
            //ChessCheck_Big(ChessMap, i, j);
            //ChessMove(i, j, ChessMap, Checked_Row, Checked_Col);

            if( Judge == true)
            {
                //ChessHistory chesshistory;
//                for(int i = 0; i < ROW; i++)
//                {
//                    for(int j = 0; j < COL; j++)
//                    {
//                        chesshistory.ChessTemp[i][j].type = ChessMap[i][j].type;
//                    }
//                }
                chessBack.push_back(chessMap);

                bool isEat = false;
                if(chessMap.chess[i][j].type != 0)
                    isEat = true;

                chessMap.chess[i][j].type = chessMap.chess[Checked_Row][Checked_Col].type;

                chessMap.chess[Checked_Row][Checked_Col].type = 0;

                if(btn_Complex->isChecked()) //执行将军判断与绝杀判断
                {
                    Checked_Row = i;
                    Checked_Col = j;
                    //qDebug() << "绝杀";
                    bool isPlaySound = isCheckMate();


                    if(isDeadlyStrike())
                    {
                        deadlyStrikeSound->play();
                        if(chessMap.Player)
                            dead = 1;
                        else
                            dead = 2;
                    }
                    else
                    {
                        if(isPlaySound) //播放声音
                        {
                            checkmateSound->play();
                        }
                        else
                        {
                            if(isGameOver())
                            {
                                deadlyStrikeSound->play();
                            }
                            else
                            {
                                if(isEat)
                                {
                                    eatSound->play();
                                }
                                else
                                {
                                    moveSound->play();
                                }
                            }

                        }
                    }

                }
                else
                {
                    if(isEat)
                    {
                        eatSound->play();
                    }
                    else
                    {
                        moveSound->play();
                    }
                }


                //moveSound->play(); /////////////////////////////////////////
                //this->Player = !this->Player;
                chessMap.Player = !chessMap.Player;
                chessMap.saveChessMap();
            }


            update();

            Checked_Row = -1;
            Checked_Col = -1;
        }
    }
}


bool PlayScene::ChessMove(int i, int j)
{
    bool Judge = false;
    if (chessMap.chess[Checked_Row][Checked_Col].type == 1) //红兵
    {
        Judge = RedBin_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 2) //红炮
    {
        Judge = RedPao_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 3) //红车
    {
        Judge = RedChe_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 4) //红马
    {
        Judge = RedMa_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 5) //红相
    {
        Judge = RedXiang_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 6) //红士
    {
        Judge = RedShi_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 7) //帅
    {
        Judge = Shuai_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 8) //黑卒
    {
        Judge = BlackBin_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 9) //黑炮
    {
        Judge = BlackPao_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 10) //黑车
    {
        Judge = BlackChe_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 11) //黑马
    {
        Judge = BlackMa_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 12) //黑象
    {
        Judge = BlackXiang_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 13) //黑士
    {
        Judge = BlackShi_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    else if (chessMap.chess[Checked_Row][Checked_Col].type == 14) //将
    {
        Judge = Jiang_Move(j, i, chessMap, Checked_Row, Checked_Col);
    }
    return Judge;
}

bool PlayScene::isCheckMate()
{
//    if(chessMap.Player && ChessMove(Jiang_Row, Jiang_Col))
//    {
//        //qDebug() << "将Jiang";
//        return true;
//    }
//    else if(!chessMap.Player && ChessMove(Shuai_Row, Shuai_Col))
//    {
//        //qDebug() << "将Shuai";
//        return true;
//    }

    int tempChecked_Row = Checked_Row;
    int tempChecked_Col = Checked_Col;

    Checked_Row = 0;
    Checked_Col = 0;

    if(chessMap.Player)
    {
        for(Checked_Row = 0; Checked_Row < ROW; ++Checked_Row)
        {
            for(Checked_Col = 0; Checked_Col < COL; ++Checked_Col)
            {
                if(ChessMove(Jiang_Row, Jiang_Col))
                {
                    qDebug() << "将Jiang";
                    Checked_Row = tempChecked_Row;
                    Checked_Col = tempChecked_Col;
                    return true;
                }

            }
        }
    }
    else
    {
        for(Checked_Row = 0; Checked_Row < ROW; ++Checked_Row)
        {
            for(Checked_Col = 0; Checked_Col < COL; ++Checked_Col)
            {
                if(ChessMove(Shuai_Row, Shuai_Col))
                {
                    qDebug() << "将Shuai";
                    Checked_Row = tempChecked_Row;
                    Checked_Col = tempChecked_Col;
                    return true;
                }

            }
        }
    }



    Checked_Row = tempChecked_Row;
    Checked_Col = tempChecked_Col;

    return false;
}

bool PlayScene::isDeadlyStrike()
{
    if(isCheckMate())
    {
        int tempChecked_Row = Checked_Row;
        int tempChecked_Col = Checked_Col;
        if(chessMap.Player)
        {
            for(Checked_Row = 0; Checked_Row < ROW; ++Checked_Row)
            {
                for(Checked_Col = 0; Checked_Col < COL; ++Checked_Col)
                {
                    if(chessMap.chess[Checked_Row][Checked_Col].type >= 8 && chessMap.chess[Checked_Row][Checked_Col].type <= 14)
                    {
                        for(int i = 0; i < ROW; ++i)
                        {
                            for(int j = 0; j < COL; ++j)
                            {
                                if(ChessMove(i, j))
                                {
                                    int tempIJ = chessMap.chess[i][j].type;
                                    int tempCheckedRC = chessMap.chess[Checked_Row][Checked_Col].type;
                                    int tempRow = Checked_Row;
                                    int tempCol = Checked_Col;
                                    chessMap.chess[i][j].type = chessMap.chess[Checked_Row][Checked_Col].type;
                                    chessMap.chess[Checked_Row][Checked_Col].type = 0;


                                    Checked_Row = tempChecked_Row;
                                    Checked_Col = tempChecked_Col;

                                    if(!isCheckMate())
                                    {
                                        Checked_Row = tempRow;
                                        Checked_Col = tempCol;
                                        chessMap.chess[i][j].type = tempIJ;
                                        chessMap.chess[Checked_Row][Checked_Col].type = tempCheckedRC;
                                        return false;
                                    }

                                    Checked_Row = tempRow;
                                    Checked_Col = tempCol;
                                    chessMap.chess[i][j].type = tempIJ;
                                    chessMap.chess[Checked_Row][Checked_Col].type = tempCheckedRC;
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for(Checked_Row = 0; Checked_Row < ROW; ++Checked_Row)
            {
                for(Checked_Col = 0; Checked_Col < COL; ++Checked_Col)
                {
                    if(chessMap.chess[Checked_Row][Checked_Col].type >= 0 && chessMap.chess[Checked_Row][Checked_Col].type <= 7)
                    {
                        for(int i = 0; i < ROW; ++i)
                        {
                            for(int j = 0; j < COL; ++j)
                            {
                                if(ChessMove(i, j))
                                {
                                    int tempIJ = chessMap.chess[i][j].type;
                                    int tempCheckedRC = chessMap.chess[Checked_Row][Checked_Col].type;
                                    int tempRow = Checked_Row;
                                    int tempCol = Checked_Col;
                                    chessMap.chess[i][j].type = chessMap.chess[Checked_Row][Checked_Col].type;
                                    chessMap.chess[Checked_Row][Checked_Col].type = 0;


                                    Checked_Row = tempChecked_Row;
                                    Checked_Col = tempChecked_Col;

                                    if(!isCheckMate())
                                    {
                                        Checked_Row = tempRow;
                                        Checked_Col = tempCol;
                                        chessMap.chess[i][j].type = tempIJ;
                                        chessMap.chess[Checked_Row][Checked_Col].type = tempCheckedRC;
                                        return false;
                                    }

                                    Checked_Row = tempRow;
                                    Checked_Col = tempCol;
                                    chessMap.chess[i][j].type = tempIJ;
                                    chessMap.chess[Checked_Row][Checked_Col].type = tempCheckedRC;
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    return false;
}












