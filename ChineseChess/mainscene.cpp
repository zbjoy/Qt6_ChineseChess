#include "mainscene.h"
#include "ui_mainwidget.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    iniUI();
}

void MainScene::iniUI()
{
    this->setWindowIcon(QIcon(":/res/MainScene.jpg"));

    this->setFixedSize(500, 700);
    QLabel* mainImage = new QLabel(this);
    mainImage->setGeometry(0, 0, 500, 700);
    mainImage->setPixmap(QPixmap(":/res/MainScene.jpg").scaled(500, 700));

    MyPushButton* btn_GoPlayScene = new MyPushButton(":/res/Start1.jpg", 100, 60, ":/res/Start2.jpg");
    MyPushButton* btn_ExitGame = new MyPushButton(":/res/MainExit.png", 100, 60);

    btn_GoPlayScene->setParent(this);
    btn_GoPlayScene->move(200, 450);

    btn_ExitGame->setParent(this);
    btn_ExitGame->move(200, 530);

    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    QMenu* startMenu = bar->addMenu("开始");

    QAction* quitAction = startMenu->addAction("退出");

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

