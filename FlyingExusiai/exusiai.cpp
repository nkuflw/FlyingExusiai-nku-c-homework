#include "exusiai.h"
#include"config.h"
Exusiai::Exusiai()
{
    //初始化加载飞机图片资源
    m_Plane.load (EXUSIAI_PATH);
    //初始化飞机坐标
    m_X=(GAME_WIDTH-m_Plane.width())*0.5;
    m_Y=GAME_HEIGHT-m_Plane.height();

    //初始化矩形边框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Exusiai::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录数字未达到发射子弹时间间隔 直接return不发射
    if(m_recorder<BULLET_INTERVAL){
        return;
    }
    //达到发射时间
    m_recorder=0;

    //发射子弹
    for(int i=0;i<BULLET_NUM;i++){
        //如果是空闲子弹，进行发射
        if(m_bullets[i].m_Free){
            //将空闲状态改为假
            m_bullets[i].m_Free=false;
            //设置子弹坐标
            m_bullets[i].m_X=m_X+m_Rect.width()*0.25;
            m_bullets[i].m_Y=m_Y-25;
            break;
        }
    }
}

void Exusiai::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}
