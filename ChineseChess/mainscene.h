#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include "MyPushButton.h"
#include "playscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWidget; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void iniUI();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
