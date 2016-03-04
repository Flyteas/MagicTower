#ifndef HERO_H
#define HERO_H
#include <QLabel>
#include <QPoint>
#include <fightwidget.h>
class HeroState //英雄状态类
{
public:
    int Hp; //血量
    int Attack; //攻击
    int Defense; //防御
    int YellowKeyNum; //黄钥匙数量
    int RedKeyNum; //红钥匙数量
    int BlueKeyNum; //蓝钥匙数量
    int Exp; //经验值
    int Level; //等级
    int FloorNum;  //层数
    HeroState operator = (const HeroState&);
};


class Hero:public QObject //英雄类
{
    Q_OBJECT
public:
    Hero();
    ~Hero();
    bool SetHeroDisplay(QWidget*);
    bool SetHeroPos(QPoint);
    QPoint GetHeroPos();
    bool UpdateDisplayPos();
    bool SetLogo(int);
    bool ChangeHeroState(HeroState);
    bool HeroMove(int);
    bool HeroNext(int);
    bool DeleteMapBlock(const QPoint&);
    bool HeroFight(const QPoint&,HeroState&,QString);
    void sleep(int);
    QLabel *HeroDisplay;
    FightWidget *HeroFightWidget;
    HeroState UserHeroState; //英雄状态
    bool IsHeroFighting=false; //英雄是否处于战斗状态
    bool FloorChange(const int); //改变当前层数
    bool LoadCurrentFloorMap(); //载入当前层的地图
signals:
    void SendHeroStateChanged(const HeroState&);
    void SendFightWidgetStateChanged(const int,const int,const int,const int);
    void SendFloorChange(const int);
    void SendCloseMainWindow();

private:
    QPoint HeroPos;
    QWidget *LabelParent; //控件的父
};

#endif // HERO_H
