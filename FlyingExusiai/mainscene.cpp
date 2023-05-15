#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include<QPainter>
#include<QMouseEvent>
#include<QEvent>
#include<ctime>
#include<QSound>
#include<QLabel>
#include<QPushButton>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{

            //调用初始化场景
            initScene();

            QPushButton*btn=new QPushButton;

            QPushButton*btn2=new QPushButton;

            QPushButton*btn3=new QPushButton;

            QPushButton*btn4=new QPushButton;

            btn->resize(100,100);
            btn->move(256,354);
            btn->setParent(this);
            btn->setText("开始游戏");

            btn2->resize(100,100);
            btn2->move(180,354);
            btn2->setParent(this);
            btn2->setText("大骑士领");
            btn2->hide();

            btn3->resize(100,100);
            btn3->move(332,354);
            btn3->setParent(this);
            btn3->setText("殉道之人");
            btn3->hide();

            btn4->resize(300,100);
            btn4->move(153,154);
            btn4->setParent(this);
            btn4->setText("请选择您想听的背景音乐");
            btn4->hide();

            connect(btn,&QPushButton::clicked,[=](){
                //启动游戏
                btn->hide();

                btn2->show();

                btn3->show();

                btn4->show();

                connect(btn2,&QPushButton::clicked,[=](){
                    btn2->hide();
                    btn3->hide();
                    btn4->hide();
                    SOUND=SOUND_BACKGROUND1;
                    playGame();
                });

                connect(btn3,&QPushButton::clicked,[=](){
                    btn2->hide();
                    btn3->hide();
                    btn4->hide();
                    SOUND=SOUND_BACKGROUND2;
                    playGame();
                });
            });
}

MainScene::~MainScene()
{
}
void MainScene::initScene(){

    //设置窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置标题
    setWindowTitle(GAME_TITLE);

    //加载图标
    setWindowIcon(QIcon(GAME_ICON));

    //定时器设置
    m_Timer.setInterval(GAME_RATE);

    //敌机出场时间间隔
    m_recorder=0;

    //boss出场时间间隔
    m_boss_recorder=0;

    //随机数种子
    srand((unsigned int)time(NULL));

    life = new QLabel("生命值：∞，因为阿能是无敌哒！！！",this);
    life->setFont(QFont("Algerian",16));
    life->move(0,500);
    score = new QLabel(QString(SCORE).arg(Score),this);
    score->setFont(QFont("Algerian",16));
    score->move(0,550);
}

void MainScene::playGame(){

    //启动背景音乐
    QSound::play(SOUND);

    //启动定时器
    m_Timer.start();
    //监听定时器发送的信号
    connect(&m_Timer,&QTimer::timeout,[=]{
        //敌机出场
        enemyToScene();
        //boss出场
        bossToScene();
        //更新游戏中元素的坐标
        updatePosition();
        //绘制到屏幕中
        update();
        //碰撞检测
        collisionDetection();
        //boss碰撞检测
        bossCollisionDetection();
    });
}

void MainScene::updatePosition(){
    //更新地图坐标
   // m_map.mapPosition();

    //测试子弹
    //temp_Bullet.m_Free=false;
    //temp_Bullet.updatePosition();

    //发射子弹
    m_exusiai.shoot();

    //计算所有非空闲子弹的当前坐标
    for(int i=0;i<BULLET_NUM;i++){
        //如果非空闲，计算发射位置
        if(m_exusiai.m_bullets[i].m_Free==false){
            m_exusiai.m_bullets[i].updatePosition();
        }
    }
    //敌机出场
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free==false){
            m_enemys[i].updatePosition();
        }
    }

    //boss出场
    for(int i=0;i<BOSS_NUM;i++){
        if(m_bosses[i].m_Free==false){
            m_bosses[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i=0;i<BOMB_NUM;i++){
        if(m_bombs[i].m_Free==false){
             m_bombs[i].updateInfo();
        }
    }
    score->setText(QString(SCORE).arg(Score));
}

void MainScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制阿能
    painter.drawPixmap(m_exusiai.m_X,m_exusiai.m_Y,m_exusiai.m_Plane);

    //测试子弹
    //painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);

    //绘制子弹
    for(int i=0;i<BULLET_NUM;i++){
        //如果非空闲，绘制
        if(m_exusiai.m_bullets[i].m_Free==false){
        painter.drawPixmap(m_exusiai.m_bullets[i].m_X,m_exusiai.m_bullets[i].m_Y,m_exusiai.m_bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free==false){
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

    //绘制boss
    for(int i=0;i<BOSS_NUM;i++){
        if(m_bosses[i].m_Free==false){
            painter.drawPixmap(m_bosses[i].m_X,m_bosses[i].m_Y,m_bosses[i].m_boss);
        }
    }

    //绘制爆炸
    for(int i=0;i<BOMB_NUM;i++){
        if(m_bombs[i].m_Free==false){
             painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->x()-m_exusiai.m_Rect.width()*0.5;
    int y=event->y()-m_exusiai.m_Rect.height()*0.5;

    //边界检测
    if(x<=0){
        x=0;
    }
    if(x>=GAME_WIDTH-m_exusiai.m_Rect.width()){
        x=GAME_WIDTH-m_exusiai.m_Rect.width();
    }
    if(y<=0){
        y=0;
    }
    if(y>=GAME_HEIGHT-m_exusiai.m_Rect.height()){
        y=GAME_HEIGHT-m_exusiai.m_Rect.height();
    }
    m_exusiai.setPosition(x,y);

}

void MainScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder<ENEMY_INTERVAL)//未达到出场间隔
    {
       return;
    }
    m_recorder=0;

    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free=false;

            //坐标
            m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::bossToScene()
{
    m_boss_recorder++;
    if(m_boss_recorder<BOSS_INTERVAL)//未达到出场间隔
    {
        return;
    }
    m_boss_recorder=0;
    for(int i=0;i<BOSS_NUM;i++){
        if(m_bosses[i].m_Free){
            m_bosses[i].m_Free=false;

            //坐标
            m_bosses[i].m_X=rand()%(GAME_WIDTH-m_bosses[i].m_Rect.width());
            m_bosses[i].m_Y=-m_bosses[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有非空闲敌机
    for(int i=0;i<ENEMY_NUM;i++){
        //若空闲，执行下一次循环
        if(m_enemys[i].m_Free)
        {
            continue;
        }

        //遍历所有非空闲子弹
        for(int j=0;j<BULLET_NUM;j++){
            if(m_exusiai.m_bullets[j].m_Free){
                continue;
            }

            //如果子弹和飞机相交，则发生碰撞，同时将飞机和子弹空闲状态设置为真
            if(m_enemys[i].m_Rect.intersects(m_exusiai.m_bullets[j].m_Rect)){
                m_enemys[i].m_Free=true;
                m_exusiai.m_bullets[j].m_Free=true;
                Score+=1;
                //播放爆炸效果
                for(int k=0;k<BOMB_NUM;k++){
                    if(m_bombs[k].m_Free)
                    {
                        //空闲的爆炸，可以播放了
                        m_bombs[k].m_Free=false;
                        //更新爆炸坐标
                        m_bombs[k].m_X=m_enemys[i].m_X;
                        m_bombs[k].m_Y=m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }

    }
}

void MainScene::bossCollisionDetection()
{
    //遍历所有非空闲boss
    for(int i=0;i<BOSS_NUM;i++){
        //若空闲，执行下一次循环
        if(m_bosses[i].m_Free)
        {
            continue;
        }

        //遍历所有非空闲子弹
        for(int j=0;j<BULLET_NUM;j++){
            if(m_exusiai.m_bullets[j].m_Free){
                continue;
            }

            //如果子弹和boss相交，则发生碰撞，同时将子弹空闲状态设置为真,将boss生命值减一
            if(m_bosses[i].m_Rect.intersects(m_exusiai.m_bullets[j].m_Rect)){
                m_bosses[i].m_life--;
                m_exusiai.m_bullets[j].m_Free=true;

                //若boss生命为0，播放爆炸效果同时将boss空闲状态设置为真
                if(m_bosses[i].m_life<=0){
                     m_bosses[i].m_Free=true;
                     Score+=10;
                for(int k=0;k<BOMB_NUM;k++){
                    if(m_bombs[k].m_Free)
                        {
                            //空闲的爆炸，可以播放了
                            m_bombs[k].m_Free=false;
                            //更新爆炸坐标
                            m_bombs[k].m_X=m_bosses[i].m_X;
                            m_bombs[k].m_Y=m_bosses[i].m_Y;
                        break;
                        }
                    }
                }
            }
        }
    }
}







