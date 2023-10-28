#include "mainscene.h"
#include "ui_mainscene.h"

#include <QDebug>
#include <iostream>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    chessMap.infoChessMap();

    iniUI(); //初始化界面

    //saveChessMap();
    //chessMap.saveChessMap();

    //infoChessMap();

    //debugChessMap();
}

//void MainScene::debugChessMap()
//{
//    for(int i = 0; i < ROW; ++i)
//    {
//        for(int j = 0; j < COL; ++j)
//        {
//            std::cout << chessMap.chess[i][j].type << " ";
//        }
//        std::cout << std::endl;
//    }

//    qDebug() << debug;// << std::endl;
//}



void MainScene::iniUI()
{
    this->setWindowIcon(QIcon(":/res/WindowIcon.png"));

    this->setFixedSize(500, 725);
    QLabel* mainImage = new QLabel(this);
    mainImage->setGeometry(0, 25, 500, 700);
    mainImage->setPixmap(QPixmap(":/res/MainScene.jpg").scaled(500, 730));

    MyPushButton* btn_GoPlayScene = new MyPushButton(":/res/MainStart.png", 120, 85, ":/res/Start2.jpg");
    MyPushButton* btn_ExitGame = new MyPushButton(":/res/MainExit.png", 120, 85, ":/res/Exit2.jpg");

    btn_GoPlayScene->setParent(this);
    btn_GoPlayScene->move(185, 450);

    btn_ExitGame->setParent(this);
    btn_ExitGame->move(185, 530);

    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* startMenu = bar->addMenu("开始");

    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    PlayScene* playscene = new PlayScene(chessMap);
    connect(btn_GoPlayScene, MyPushButton::clicked, [=](){
        btn_GoPlayScene->zoom1();
        btn_GoPlayScene->zoom2();

        QTimer::singleShot(500, this, [=](){
            this->hide();
            playscene->show();
        });
    });

    connect(playscene, PlayScene::PlaySceneBack, [=](){
        QTimer::singleShot(500, this, [=](){
            playscene->hide();
            this->show();
        });
    });

    connect(btn_ExitGame, MyPushButton::clicked, [=](){
        btn_ExitGame->zoom1();
        btn_ExitGame->zoom2();

        QTimer::singleShot(500, this, [=](){
            this->close();
        });
    });


}

MainScene::~MainScene()
{
    delete ui;
}

