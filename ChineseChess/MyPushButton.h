#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:

    //构造函数
    MyPushButton(QString normalImg,int w,int h, QString pressImg="");

    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);

    //成员属性  保存用户传入的默认显示路径  以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    int w;
    int h;

};

#endif // MYPUSHBUTTON_H
