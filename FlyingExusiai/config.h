#ifndef CONFIG_H
#define CONFIG_H

/******** 游戏配置数据 *********/
#define GAME_WIDTH   612 //宽度
#define GAME_HEIGHT  835  //高度
#define GAME_TITLE "FlyingExusiai v8.0"  //标题
#define GAME_ICON ":/res/p2.jpg"//图标加载路径
#define GAME_RATE 10  //定时器刷新时间间隔  单位ms
#define SCORE "Score: %1              "
#define LIFE "∞，因为阿能是无敌哒！！！"

/******** 游戏配置数据 *********/
#define MAP_PATH ":/res/background3.jpg"
#define MAP_SCROLL_SPEED 2//地图滚动速度

/******** 飞机配置数据*********/
#define EXUSIAI_PATH ":/res/p3.png"

/******** 子弹配置数据*********/
#define BULLET_PATH ":/res/bullet.png"//子弹图片路径
#define BULLET_SPEED 5

#define BULLET_NUM 30//弹匣中子弹总数
#define BULLET_INTERVAL 20//发射子弹时间间隔

/******** 敌机配置数据**********/
#define ENEMY_PATH ":/res/enemy3.png" //敌机资源图片
#define ENEMY_SPEED 3 //敌机移动速度
#define ENEMY_NUM 20  //敌机总数量
#define ENEMY_INTERVAL  80  //敌机出场时间间隔

/********敌方boss配置数据*******/
#define BOSS_PATH ":/res/bossF.png"//boss资源图片
#define BOSS_SPEED 4//boss移动速度
#define BOSS_NUM 2 //boss总数量
#define BOSS_INTERVAL 3000 //BOSS出场时间间隔
#define BOSS_LIFE 10 //BOSS生命值

/******** 爆炸资源配置数据*************/
#define BOMB_PATH ":/res/bomb-%1.png"  //爆炸资源图片
#define BOMB_NUM  20  //爆炸数量
#define BOMB_MAX  2  //爆炸图片最大索引
#define BOMB_INTERVAL 20 //爆炸切图时间间隔

/******** 音效数据***********/
#define SOUND_BACKGROUND1 ":/res/Bgm(min).wav"//大骑士领
#define SOUND_BACKGROUND2 ":/res/bgm2(min).wav"//殉道之人
#define SOUND_BOMB ""

#endif // CONFIG_H
