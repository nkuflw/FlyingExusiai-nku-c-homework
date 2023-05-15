#ifndef EXUSIAI_H
#define EXUSIAI_H
#include<QPixmap>
#include<QRect>
#include"bullet.h"
class Exusiai
{
public:
    Exusiai();

    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x,int y);
    //飞机资源 对象
    QPixmap m_Plane;

    //飞机坐标
    int m_X;
    int m_Y;

    //飞机的矩形边框
    QRect m_Rect;

    //弹匣
    Bullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;

};

#endif // EXUSIAI_H
