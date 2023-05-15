#include "bomb.h"
#include"config.h"
Bomb::Bomb()
{
    //将所有爆炸pixmap放入数组中
    for(int i=1;i<=BOMB_MAX;i++)
    {
        //str类似于":/res/bomb-%1.png"
        QString str =QString(BOMB_PATH).arg(i);
        m_pixArr.push_back(QPixmap(str));
    }
    //坐标
    m_X=0;
    m_Y=0;

    //空闲状态
    m_Free=true;

    //当前图片下标
    m_index=0;

    //播放爆炸间隔记录
    m_Recorder=0;
}

void Bomb::updateInfo()
{
    //空闲状态下的 爆炸效果 直接return
    if(m_Free){
        return;
    }

    m_Recorder++;
    //如果记录爆炸的实际未到达爆炸间隔，不需要切图，直接return
    if(m_Recorder<BOMB_INTERVAL){
        return;
    }

    //重置记录
    m_Recorder=0;

    //切换爆炸播放的图片的下标
    m_index++;

    //数组中下标从0开始计算，最后一个图片的下标为BOMB_MAX-1
    if(m_index>BOMB_MAX-1){
        m_index=0;
        m_Free=true;
    }
}
