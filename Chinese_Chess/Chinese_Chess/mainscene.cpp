#include "mainscene.h"
#include "ui_mainscene.h"

#include <QDebug>
#include <iostream>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    iniUI();

    saveChessMap();

    infoChessMap();

    debugChessMap();
}

void MainScene::debugChessMap()
{
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            std::cout << chessMap.chess[i][j].type << " ";
        }
        std::cout << std::endl;
    }

    qDebug() << debug;// << std::endl;
}

void MainScene::saveChessMap()
{
//    QFile* File_ChessMap = new QFile(QApplication::applicationDirPath() + "/ChessMap.txt");
//    File_ChessMap->open(QIODevice::WriteOnly);

//    File_ChessMap->write("hello", sizeof(ChessMap));

//    File_ChessMap->close();

    QFile file("ChessMap.txt");
    if(!file.open(QFile::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);
    out << "hello world";

    file.close();
}

void MainScene::infoChessMap()
{
    QFile file("ChessMap.txt");
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream in(&file);
    in >> debug;

    file.close();
}

void MainScene::iniUI()
{
    this->setWindowIcon(QIcon(":/res/WindowIcon.png"));

    this->setFixedSize(500, 725);
    QLabel* mainImage = new QLabel(this);
    mainImage->setGeometry(0, 25, 500, 700);
    mainImage->setPixmap(QPixmap(":/res/MainScene.jpg").scaled(500, 730));

    MyPushButton* btn_GoPlayScene = new MyPushButton(":/res/Start1.jpg", 100, 85, ":/res/Start2.jpg");
    MyPushButton* btn_ExitGame = new MyPushButton(":/res/MainExit.png", 100, 85);

    btn_GoPlayScene->setParent(this);
    btn_GoPlayScene->move(200, 475);

    btn_ExitGame->setParent(this);
    btn_ExitGame->move(200, 555);

    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* startMenu = bar->addMenu("开始");

    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    PlayScene* playscene = new PlayScene;
    connect(btn_GoPlayScene, MyPushButton::clicked, [=](){
        btn_GoPlayScene->zoom1();
        btn_GoPlayScene->zoom2();

        QTimer::singleShot(500, this, [=](){
            this->hide();
            playscene->show();
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

