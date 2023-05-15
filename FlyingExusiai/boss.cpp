#include "boss.h"
#include"config.h"
Boss::Boss()
{
    //Boss资源加载
    m_boss.load(BOSS_PATH);

    //Boss位置
    m_X=0;
    m_Y=0;

    //Boss状态
    m_Free=true;

    //Boss生命
    m_life=BOSS_LIFE;

    //Boss速度
    m_Speed=BOSS_SPEED;

    //Boss矩形框（碰撞检测）
    m_Rect.setWidth(m_boss.width());
    m_Rect.setHeight(m_boss.height());
    m_Rect.moveTo (m_X,m_Y);

}

void Boss::updatePosition()
{
    //空闲状态Boss不计算坐标
    if(m_Free){
        return;
    }

    m_Y+=m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    //如果超出屏幕，重置空闲状态
    if(m_Y>=GAME_HEIGHT+m_Rect.height()){
        m_Free=true;
    }
}
