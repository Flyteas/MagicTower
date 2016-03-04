#include <Hero.h>
#include <ExternVar.h>
#include <fightfalsemsg.h>
#include <aboutwidget.h>
#include <conversationwidget.h>
#include <SaveLoadFunction.h>
#include <QTime>
#include <QCoreApplication>
#include <QMessageBox>
HeroState HeroState::operator = (const HeroState &data)
{
    Hp=data.Hp;
    Attack=data.Attack;
    Defense=data.Defense;
    YellowKeyNum=data.YellowKeyNum;
    RedKeyNum=data.RedKeyNum;
    BlueKeyNum=data.BlueKeyNum;
    Exp=data.Exp;
    Level=data.Level;
    FloorNum=data.FloorNum;
    return *this;
}

Hero::Hero()
{
}

Hero::~Hero()
{
    HeroDisplay->deleteLater();
    delete HeroDisplay;
    HeroDisplay=0;
}
bool Hero::SetHeroPos(QPoint NewPos)
{
    if(NewPos.x()<0||NewPos.x()>10||NewPos.y()<0||NewPos.y()>10)
    {
        return false;
    }
    else
    {
        HeroPos=NewPos;
        return true;
    }
}

bool Hero::SetHeroDisplay(QWidget *parent)
{
    HeroDisplay=new QLabel(parent);
    LabelParent=parent;
    return true;
}

QPoint Hero::GetHeroPos()
{
    return HeroPos;
}

bool Hero::UpdateDisplayPos()
{
    HeroDisplay->setGeometry(HeroPos.x()*64,HeroPos.y()*64,64,64);
    HeroDisplay->raise();
    return true;
}

bool Hero::SetLogo(int direction) //1，2，3，4 分别代表上下左右
{
    QPixmap Logo;
    switch (direction)
    {
    case 1:
        Logo=QPixmap(":/ImgRes/Hero_Up.bmp");
        break;
    case 2:
        Logo=QPixmap(":/ImgRes/Hero_Down.bmp");
        break;
    case 3:
        Logo=QPixmap(":/ImgRes/Hero_Left.bmp");
        break;
    case 4:
        Logo=QPixmap(":/ImgRes/Hero_Right.bmp");
        break;
    }
    HeroDisplay->setPixmap(Logo);
    return true;
}
bool Hero::ChangeHeroState(HeroState NewData)
{
    UserHeroState=NewData;
    emit SendHeroStateChanged(UserHeroState);
    return true;
}

bool Hero::HeroMove(int direction) //1，2，3，4分别代表上下左右
{
    switch (direction)
    {
    case 1: //上
        SetHeroPos(QPoint(GetHeroPos().x(),GetHeroPos().y()-1));
        break;
    case 2: //下
        SetHeroPos(QPoint(GetHeroPos().x(),GetHeroPos().y()+1));
        break;
    case 3: //左
        SetHeroPos(QPoint(GetHeroPos().x()-1,GetHeroPos().y()));
        break;
    case 4: //右
        SetHeroPos(QPoint(GetHeroPos().x()+1,GetHeroPos().y()));
        break;
    }
    UpdateDisplayPos();
    return true;
}

bool Hero::HeroNext(int direction)
{
    QPoint HeroNextPos; //下一步的位置
    int NextPosBlockType; //下一步位置上物品的类型
    switch(direction)
    {
    case 1: //上
        HeroNextPos=QPoint(HeroPos.x(),HeroPos.y()-1);
        break;
    case 2: //下
        HeroNextPos=QPoint(HeroPos.x(),HeroPos.y()+1);
        break;
    case 3: //左
        HeroNextPos=QPoint(HeroPos.x()-1,HeroPos.y());
        break;
    case 4: //右
        HeroNextPos=QPoint(HeroPos.x()+1,HeroPos.y());
        break;
    }
    if(HeroNextPos.x()<0||HeroNextPos.x()>10||HeroNextPos.y()<0||HeroNextPos.y()>10) //判断下一位置是否已经越出地图范围
    {
        return false;
    }

    NextPosBlockType=MapBlockData[HeroNextPos.y()][HeroNextPos.x()]->Block_Type;
    HeroState NewState=UserHeroState;
    switch(NextPosBlockType)
    {
    case 1: //空地
        HeroPos=HeroNextPos; //直接更新位置
        break;
    case 2: //墙
        break; //位置不变
    case 3: //绿色宝石,防御+20
        NewState.Defense+=20;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的绿色宝石
        break;
    case 4: //蓝色宝石,防御+3
        NewState.Defense+=3;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的蓝色宝石
        break;
    case 5: //黄色钥匙
        NewState.YellowKeyNum+=1;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的黄色钥匙
        break;
    case 6: //蓝色钥匙
        NewState.BlueKeyNum+=1;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的蓝色钥匙
        break;
    case 7: //红色钥匙
        NewState.RedKeyNum+=1;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的红色钥匙
        break;
    case 8: //红色药水 +200 Hp
        NewState.Hp+=200;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos); //删除当前英雄位置的红色药水
        break;
    case 9: //蓝色药水 +800 Hp
       NewState.Hp+=800; //加100血量
       HeroPos=HeroNextPos; //更新英雄位置数据
       DeleteMapBlock(HeroPos); //删除当前英雄位置的蓝药水
       break;
    case 10: //初级剑 +20攻击
        NewState.Attack+=20;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos);
        break;
    case 11: //初级盾 +50防御
        NewState.Defense+=50;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos);
        break;
    case 12: //羽毛 等级+1
        NewState.Level+=1;
        HeroPos=HeroNextPos; //更新英雄位置数据
        DeleteMapBlock(HeroPos);
        break;
    case 13: //中级剑 +100攻击
        NewState.Attack+=100;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 14: //中级盾 +100防御
        NewState.Defense+=100;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 15: // 超级羽毛 等级+3
        NewState.Level+=3;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 16: // 神仙水 Hp翻倍
        NewState.Hp=NewState.Hp*2;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 17: // 高级剑 +200攻击
        NewState.Attack+=200;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 18: // 高级盾 +200防御
        NewState.Defense+=200;
        HeroPos=HeroNextPos;
        DeleteMapBlock(HeroPos);
        break;
    case 19: //黄色的门
        if(UserHeroState.YellowKeyNum>0) //如果有黄色钥匙
        {
            NewState.YellowKeyNum-=1; //黄色钥匙数量减一
            HeroPos=HeroNextPos; //更新英雄位置数据
            DeleteMapBlock(HeroPos); //删除当前英雄位置的黄钥匙
            break;
        }
        break; //如果没有黄色钥匙则不动
    case 20: //蓝色的门
        if(UserHeroState.BlueKeyNum>0) //如果有蓝色钥匙
        {
            NewState.BlueKeyNum-=1; //蓝色钥匙数量减一
            HeroPos=HeroNextPos; //更新英雄位置数据
            DeleteMapBlock(HeroPos); //删除当前英雄位置的蓝色钥匙
            break;
        }
        break; //如果没有蓝色钥匙则不动
    case 21: //红色的门
        if(UserHeroState.RedKeyNum>0) //如果有红色钥匙
        {
            NewState.RedKeyNum-=1; //红色钥匙数量减一
            HeroPos=HeroNextPos; //更新英雄位置数据
            DeleteMapBlock(HeroPos); //删除当前英雄位置的红色钥匙
            break;
        }
        break; //如果没有红色钥匙则不动
    case 22: //上楼楼梯
      {
        bool IsFind=false; //是否已经遍历到下楼楼梯位置
        FloorChange(++NewState.FloorNum);//更新地图
        for(int j=0;j<11;j++) //遍历当前楼层下楼楼梯的位置，并设定英雄位置为下楼楼梯位置
        {
            for(int i=0;i<11;i++)
            {
                if(MapBlockData[j][i]->Block_Type==23)
                {
                    SetHeroPos(QPoint(i,j));
                    IsFind=true;
                    break;
                }
            }
            if(IsFind)
            {
                break;
            }
        }
        break;
      }
    case 23: //下楼楼梯
      {
        bool IsFind=false; //是否已经遍历到上楼楼梯位置
        FloorChange(--NewState.FloorNum);//更新地图
        for(int j=0;j<11;j++) //遍历当前楼层上楼楼梯的位置，并设定英雄位置为上楼楼梯位置
        {
            for(int i=0;i<11;i++)
            {
                if(MapBlockData[j][i]->Block_Type==22)
                {
                    SetHeroPos(QPoint(i,j));
                    IsFind=true;
                    break;
                }
            }
            if(IsFind)
            {
                break;
            }
        }
        break;
      }
    case 24: //公主
    {
        IsHeroFighting=true;
        ConversationWidget *Npc=new ConversationWidget(LabelParent,QString::number(NextPosBlockType));
        Npc->SetConversationText("勇士,是你吗? ",true);
        Npc->SetConversationText("公主，你还好吗? ",false);
        Npc->SetConversationText("嗯，还好还好\n魔王呢? ",true);
        Npc->SetConversationText("魔王已经被我打败了\n我现在带你出去\n你害怕吗？",false);
        Npc->SetConversationText("有你在，我不会害怕! ",true);
        Npc->SetConversationText("公主,出去的时候记得要躲在我的身后\n我会一直保护你的。 ",false);
        Npc->SetConversationText("谢谢你,人家知道了。 ",true);
        Npc->SetConversationText("...... ",false);
        Npc->SetConversationText("...... ",true);
        UserHero->sleep(2000);
        delete Npc;
        DeleteMapBlock(HeroNextPos);
        Npc=new ConversationWidget(LabelParent,"26");
        Npc->SetConversationText("恭喜你！\n游戏通关! ",true);
        Npc->SetConversationText("制作团队\nCQU CS Grade 2013 Class 5\nFlyshit@cqu.edu.cn ",true);
        UserHero->sleep(5000);
        delete Npc;
        Npc=0;
        IsHeroFighting=false;
        int result=QMessageBox::information(0,QObject::tr("游戏通关"),"游戏通关完毕！",QObject::tr("重新开始"),QObject::tr("退出游戏"));
        if(result==QObject::tr("重新开始").toInt())
        {
            if(!LoadMap("./DefaultData.dat","./DefaultData.dat")) //载入数据，并判断是否载入成功
            {
                QMessageBox::information(0,"错误","找不到地图数据文件!");
            }
            else
            {
                QMessageBox::information(0,"成功","游戏即将重新开始");
            }
            UserHero->FloorChange(UserHero->UserHeroState.FloorNum); //载入当前层 的地图
            UserHero->UpdateDisplayPos();
            UserHero->SetLogo(2);
        }
        else
        {
            IsGameOver=true;
            emit SendCloseMainWindow(); //退出程序信号
        }
    }
        break;
    case 25: //守护者NPC
    {
        IsHeroFighting=true;
        ConversationWidget *Npc=new ConversationWidget(LabelParent,"25");
        Npc->SetConversationText("勇士~~,勇士~~,快醒醒! ",true);
        Npc->SetConversationText("唔......头好痛 ...... ",false);
        Npc->SetConversationText("勇士你终于醒啦!O(∩_∩)O~ ",true);
        Npc->SetConversationText("......\n你是谁,我在哪里？ ",false);
        Npc->SetConversationText("我是这里的守护者\n你是来救公主的吗! ",true);
        Npc->SetConversationText("是啊!\n你知道公主被抓去哪里吗？",false);
        Npc->SetConversationText("公主被魔王抓到塔里去了..... ",true);
        Npc->SetConversationText("魔王是谁? ",false);
        Npc->SetConversationText("魔王是燃烧军团的先锋\n他从遥远的艾泽拉斯而来 ",true);
        Npc->SetConversationText("啊,那公主不是有危险吗,我要进去救公主\n...唔...! ",false);
        Npc->SetConversationText("你这样进去是打不过那些怪物的! ",true);
        Npc->SetConversationText("可是我答应国王要救公主回去的!\n我不能半途而废! ",false);
        Npc->SetConversationText("既然你如此坚定，那我就赠与你一些力量吧! ",true);
        Npc->SetConversationText("谢谢!\n我该怎么进塔呢？",false);
        Npc->SetConversationText("塔里面有很多不同颜色的门\n需要对应钥匙才能打开 ",true);
        Npc->SetConversationText("那我怎么才能得到钥匙呢？ ",false);
        Npc->SetConversationText("我这里有三把钥匙给你\n里面还有很多这样的钥匙\n勇士你要合理利用好才行! ",true);
        Npc->SetConversationText("嗯，我知道了,那我进塔了! ",false);
        Npc->SetConversationText("勇士一定要小心\n敌人太强就先撤退，不要硬打 ",true);
        Npc->SetConversationText("魔王未绝之前,我慕容氏绝不可死! ",false);
        Npc->SetConversationText("等你回来！",true);
        delete Npc;
        Npc=0;
        DeleteMapBlock(HeroNextPos);
        DeleteMapBlock(QPoint(4,7));
        MapData[0][7][4]=27;
        MapBlockData[7][4]=new Map_Block(27,QPoint(4,7),LabelParent);
        NewState.YellowKeyNum+=1;
        NewState.RedKeyNum+=1;
        NewState.BlueKeyNum+=1;
        IsHeroFighting=false;
    }
        break;
    case 26: //制作团队NPC
    {
        AboutWidget *AboutUs=new AboutWidget;
    }
        break;
    case 27: //守护者NPC对话后
    {
        IsHeroFighting=true;
        ConversationWidget *Npc=new ConversationWidget(LabelParent,"27");
        Npc->SetConversationText("等你回来！",true);
        delete Npc;
        Npc=0;
        IsHeroFighting=false;
    }
        break;
    case 101: //绿色史莱姆
    case 102: //红色史莱姆
    case 103: //青头怪
    case 104: //史莱姆王
    case 105: //小蝙蝠
    case 106: //大蝙蝠
    case 107: //红蝙蝠
    case 108: //冥灵魔王
    case 109: //初级法师
    case 110: //高级法师
    case 111: //初级巫师
    case 112: //高级巫师
    case 113: //骷髅人
    case 114: //骷髅士兵
    case 115: //骷髅队长
    case 116: //冥队长
    case 117: //兽人
    case 118: //兽面武士
    case 119: //石头人
    case 120: //影子战士
    case 121: //初级卫兵
    case 122: //中级士兵
    case 123: //高级卫兵
    case 124: //双手剑士
    case 125: //冥战士
    case 126: //初级骑士
    case 127: //高级骑士
    case 128: //灵武士
    case 129: //红衣魔王
    case 130: //魔法警卫
    case 131: //灵法师
    case 136: //冥队长
    case 148: //灵武士
    case 149: //红衣魔王
        if(HeroFight(HeroNextPos,NewState,QString::number(NextPosBlockType))) //如果战斗胜利
            {
                HeroPos=HeroNextPos; //更新英雄位置数据
                DeleteMapBlock(HeroPos); //删除当前位置的怪物
            }
            break;

    case 138: //冥灵魔王,终极Boss
    {
        IsHeroFighting=true;
        ConversationWidget *Npc=new ConversationWidget(LabelParent,"138");
        Npc->SetConversationText("勇士？ ",true);
        Npc->SetConversationText("魔王？ ",false);
        Npc->SetConversationText("你来了。 ",true);
        Npc->SetConversationText("我来了。 ",false);
        Npc->SetConversationText("你不该来。 ",true);
        Npc->SetConversationText("我已经来了。 ",false);
        Npc->SetConversationText("你毕竟还是来了。 ",true);
        Npc->SetConversationText("我毕竟还是来了。 ",false);
        Npc->SetConversationText("没有人见过我出手。\n见过的，都死了。 ",true);
        Npc->SetConversationText("也许以后真的再也没有人能见你出手了。 ",false);
        Npc->SetConversationText("...... ",true);
        Npc->SetConversationText("...... ",false);
        Npc->SetConversationText("动手吧！ ",true);
        UserHero->sleep(2000);
        delete Npc;
        Npc=0;
        if(HeroFight(HeroNextPos,NewState,QString::number(NextPosBlockType))) //如果战斗胜利
        {
            IsHeroFighting=true;
            Npc=new ConversationWidget(LabelParent,QString::number(NextPosBlockType));
            Npc->SetConversationText("我败了？ ",true);
            Npc->SetConversationText("你败了。 ",false);
            Npc->SetConversationText("我拥有极限反杀...竟然...\n...竟然败了？！ ",true);
            Npc->SetConversationText("你的剑再快一点\n或许败的就是我了。 ",false);
            Npc->SetConversationText("想我一生求败，最终还是败在了剑下。\n尘归尘，土归土\n艾泽拉斯才是我的归宿。 ",true);
            Npc->SetConversationText("唉...... ",false);
            UserHero->sleep(2000);
            delete Npc;
            Npc=0;
            HeroPos=HeroNextPos; //更新英雄位置数据
            DeleteMapBlock(HeroPos); //删除当前位置的怪物
            IsHeroFighting=false;
        }

    }
        break;
    }
    if(!IsGameOver) //判断是否已通关并选择退出程序
    {
    UpdateDisplayPos(); //更新地图显示
    ChangeHeroState(NewState); //更新英雄状态数据
    }
}

bool Hero::DeleteMapBlock(const QPoint& DeletePos)
{
    delete MapBlockData[DeletePos.y()][DeletePos.x()]; //删除当前英雄位置的物品
    MapBlockData[DeletePos.y()][DeletePos.x()]=new Map_Block(1,DeletePos,0); //重置为空地
    MapData[UserHeroState.FloorNum-1][DeletePos.y()][DeletePos.x()]=1; //更新地图数据为空地
    return true;
}

bool Hero::HeroFight(const QPoint& pos,HeroState& NewState,QString MonsterName)
{
    int Monster_Hp; //怪物血量
    int Monster_Hurt; //怪物一次攻击对英雄造成的伤害
    int Hero_Hp; //英雄血量
    int Hero_Hurt; //英雄一次攻击对怪物造成的伤害
    bool IsHeroWin=false; // 标识英雄能否打赢怪兽
    IsHeroFighting=true; //表示英雄处于战斗状态
    Monster_Hp=MapBlockData[pos.y()][pos.x()]->Hp;
    Hero_Hp=NewState.Hp;
    Monster_Hurt=MapBlockData[pos.y()][pos.x()]->Attack-NewState.Defense*(1+NewState.Level*0.1); // 怪物伤害算法: 伤害=怪物攻击值-英雄防御值*(1+等级*0.1)  取整数
    Hero_Hurt=NewState.Attack*(1+NewState.Level*0.1)-MapBlockData[pos.y()][pos.x()]->Defense; // 英雄伤害算法: 伤害=英雄攻击值*(1+等级*0.1)-怪物防御值  取整数
    if (!(Hero_Hurt>0)) //如果英雄伤害不大于零，则一定打不过怪物，返回false
    {
        FightFalseMsg *FalseMsg=new FightFalseMsg(LabelParent,MonsterName,MapBlockData[pos.y()][pos.x()]->Hp,MapBlockData[pos.y()][pos.x()]->Attack,MapBlockData[pos.y()][pos.x()]->Defense);
        sleep(3500);
        delete FalseMsg;
        FalseMsg=0;
        IsHeroFighting=false;
        return false;
    }
    if (Monster_Hurt<0) //防止怪物攻击值小于英雄防御值时出现负伤害(加血)
    {
        Monster_Hurt=0;
    }
    while(Hero_Hp>0) //模拟战斗，当英雄血量大于零时，进行下一轮战斗
    {
        Monster_Hp-=Hero_Hurt;
        if(!(Monster_Hp>0)) //当怪兽血量小于等于零时，英雄胜利
        {
            IsHeroWin=true;
            break;
        }
        Hero_Hp-=Monster_Hurt;
        if(!(Hero_Hp>0))  //从这个出口结束循环，说明怪兽血量大于零，而英雄血量小于等于零，即英雄战败
        {
            IsHeroWin=false;
            break;
        }
    }

    if(!IsHeroWin) //打不过怪物
    {
        FightFalseMsg *FalseMsg=new FightFalseMsg(LabelParent,MonsterName,MapBlockData[pos.y()][pos.x()]->Hp,MapBlockData[pos.y()][pos.x()]->Attack,MapBlockData[pos.y()][pos.x()]->Defense);
        sleep(3500);
        delete FalseMsg;
        FalseMsg=0;
        IsHeroFighting=false;
        return false;
    }
    HeroFightWidget = new FightWidget(LabelParent,MonsterName);
    connect(this,SIGNAL(SendFightWidgetStateChanged(const int,const int,const int,const int)),HeroFightWidget,SLOT(FightWidgetStateChange(const int,const int,const int,const int)));
    while(true)
    {
        emit SendFightWidgetStateChanged(MapBlockData[pos.y()][pos.x()]->Hp,MapBlockData[pos.y()][pos.x()]->Attack,MapBlockData[pos.y()][pos.x()]->Defense,MapBlockData[pos.y()][pos.x()]->Exp); //发出血量变化信号，实时更新战斗窗口数据
        ChangeHeroState(NewState);  //实时更新状态栏数据
        sleep(300); //等待0.5秒
        MapBlockData[pos.y()][pos.x()]->Hp-=Hero_Hurt;
        if(!(MapBlockData[pos.y()][pos.x()]->Hp>0)) //怪物血量小于等于零，战斗完毕
        {
            MapBlockData[pos.y()][pos.x()]->Hp=0;
            NewState.Exp+=MapBlockData[pos.y()][pos.x()]->Exp;
            emit SendFightWidgetStateChanged(MapBlockData[pos.y()][pos.x()]->Hp,MapBlockData[pos.y()][pos.x()]->Attack,MapBlockData[pos.y()][pos.x()]->Defense,MapBlockData[pos.y()][pos.x()]->Exp); //发出血量变化信号，实时更新战斗窗口数据
            if(!(NewState.Exp<(200+200*NewState.Level))) // 等级升级算法 升级经验=当前等级*200+200
            {
                NewState.Exp-=(200+200*NewState.Level);
                NewState.Level++;
            }
            ChangeHeroState(NewState);  //实时更新状态栏数据
            sleep(2000); //等待1.5秒
            break;
        }
        NewState.Hp-=Monster_Hurt;
        sleep(300); //等待0.5秒
    }
    delete HeroFightWidget;
    HeroFightWidget=0;
    IsHeroFighting=false;
    return true;
}

void Hero::sleep(int SleepTime) //等待
{
    QTime *QSleep= new QTime;
    QSleep->start();
    while(QSleep->elapsed()<SleepTime)
    {
        QCoreApplication::processEvents(); //处理进程消息，实时更新状态显示
    }
    delete QSleep;
    QSleep=0;
}

bool Hero::LoadCurrentFloorMap()
{
    for(int j=0;j<11;j++)
    {
        for(int i=0;i<11;i++)
        {
            delete MapBlockData[j][i];
            MapBlockData[j][i]=new Map_Block(MapData[UserHero->UserHeroState.FloorNum-1][j][i],QPoint(i,j),LabelParent);
        }
    }
    return true;
}

bool Hero::FloorChange(const int NewFloor) //改变层数
{
    UserHeroState.FloorNum=NewFloor;
    emit SendHeroStateChanged(UserHeroState);
    LoadCurrentFloorMap();
    return true;
}
