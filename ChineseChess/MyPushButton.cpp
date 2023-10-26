#include "MyPushButton.h"

#include <QDebug>
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}


MyPushButton::MyPushButton(QString normalImg,int tempW, int tempH, QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    this->w = tempW;
    this->h = tempH;

    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    //设置图片固定大小
    //this->setFixedSize(pix.width(),pix.height());
    this->setFixedSize(w, h);

    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    //this->setIconSize(QSize(pix.width(),pix.height()));
    this->setIconSize(QSize(w, h));
}

void MyPushButton::zoom1()//向下跳
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}
void MyPushButton::zoom2()//向上跳
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent * e)
{
    if(this->pressImgPath!="")//传入的摁下图片不为空 说明有摁下状态  切换图片
    {
        QPixmap pix;
        //        bool ret = pix.load(":/res/BackButtonSelected.png");
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"pressEvent图片加载失败";
            return;
        }

        //设置图片固定大小
        //this->setFixedSize(pix.width(),pix.height());
        this->setFixedSize(w, h);

        //设置图片不规则样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        //this->setIconSize(QSize(pix.width(),pix.height()));
        this->setIconSize(QSize(w, h));
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * e)
{
    if(this->pressImgPath!="")//传入的摁下图片不为空 说明有摁下状态  切换图片
    {
        QPixmap pix;
        //        bool ret = pix.load(":/res/BackButton.png");
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"releaseEvent图片加载失败";
            return;
        }

        //设置图片固定大小
        //this->setFixedSize(pix.width(),pix.height());
        this->setFixedSize(w, h);

        //设置图片不规则样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        //this->setIconSize(QSize(pix.width(),pix.height()));
        this->setIconSize(QSize(w, h));
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
