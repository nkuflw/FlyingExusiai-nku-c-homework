#ifndef BOSS_H
#define BOSS_H

#include<QPixmap>
class Boss
{
public:
    Boss();

    //更新坐标
    void updatePosition();

    //Boss资源对象
    QPixmap m_boss;

    //位置
    int m_X;
    int m_Y;

    //Boss的矩形边框（碰撞检测）
    QRect m_Rect;

    //状态
    bool m_Free;

    //生命

    int m_life;

    //速度
    int m_Speed;
};

#endif // BOSS_H
