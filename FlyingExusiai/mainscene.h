#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include<QLabel>
#include "map.h"
#include"exusiai.h"
#include"bullet.h"
#include"enemyplane.h"
#include"bomb.h"
#include"boss.h"
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化场景
    void initScene();

    //启动游戏
    void playGame();

    //更新所有游戏中元素坐标
    void updatePosition();

    //绘制到屏幕中  函数名称不可改
    void paintEvent(QPaintEvent*);

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent*);

    //敌机出场
    void enemyToScene();

    //boss出场
    void bossToScene();

    //碰撞检测
    void collisionDetection();

    //碰撞检测（boss）
    void bossCollisionDetection();

    //音乐名称
    QString SOUND;

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //Boss数组
    Boss m_bosses[BOSS_NUM];

    //敌机出场间隔记录
    int m_recorder;

    //Boss出场间隔记录
    int m_boss_recorder;

    //地图对象
    Map m_map;

    //飞机对象
    Exusiai m_exusiai;

    //定时器
    QTimer m_Timer;

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    //得分
    QLabel*score;

    int Score=0;
    //生命
    QLabel*life;

    //测试子弹对象
    //Bullet temp_Bullet;

};
#endif // MAINSCENE_H
