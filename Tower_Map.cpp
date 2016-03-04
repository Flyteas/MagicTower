#include "Tower_Map.h"

Map_Block::Map_Block(int type,QPoint pos,QWidget *parent)
{
    QString BlockTypeName;
    Block_Type=type;
    Block_Pos=pos;
    if(type<2||type>149)
    {
        return;
    }
    switch (type)
    {
    case 101: //绿色史莱姆
        Hp=50;
        Attack=20;
        Defense=1;
        Exp=10;
        break;
    case 102: //红色史莱姆
        Hp=70;
        Attack=15;
        Defense=2;
        Exp=20;
        break;
    case 103: //青头怪
        Hp=200;
        Attack=35;
        Defense=10;
        Exp=5;
        break;
    case 104: //史莱姆王
        Hp=700;
        Attack=250;
        Defense=125;
        Exp=300;
        break;
    case 105: //小蝙蝠
        Hp=100;
        Attack=20;
        Defense=5;
        Exp=30;
        break;
    case 106: //大蝙蝠
        Hp=150;
        Attack=65;
        Defense=30;
        Exp=80;
        break;
    case 107: //红蝙蝠
        Hp=550;
        Attack=160;
        Defense=95;
        Exp=200;
        break;
    case 108: //冥灵魔王
        Hp=30000;
        Attack=1700;
        Defense=1500;
        Exp=2200;
        break;
    case 109: //初级法师
        Hp=125;
        Attack=50;
        Defense=25;
        Exp=70;
        break;
    case 110: //高级法师
        Hp=150;
        Attack=150;
        Defense=110;
        Exp=250;
        break;
    case 111: //初级巫师
        Hp=250;
        Attack=120;
        Defense=70;
        Exp=170;
        break;
    case 112: //高级巫师
        Hp=500;
        Attack=300;
        Defense=250;
        Exp=450;
        break;
    case 113: //骷髅人
        Hp=110;
        Attack=22;
        Defense=5;
        Exp=40;
        break;
    case 114: //骷髅士兵
        Hp=150;
        Attack=40;
        Defense=20;
        Exp=60;
        break;
    case 115: //骷髅队长
        Hp=400;
        Attack=80;
        Defense=50;
        Exp=120;
        break;
    case 116: //冥队长
        Hp=2500;
        Attack=850;
        Defense=800;
        Exp=750;
        break;
    case 117: //兽面人
        Hp=300;
        Attack=70;
        Defense=45;
        Exp=13;
        break;
    case 118: //兽面武士
        Hp=900;
        Attack=450;
        Defense=300;
        Exp=500;
        break;
    case 119: //石头人
        Hp=500;
        Attack=105;
        Defense=60;
        Exp=150;
        break;
    case 120: //影子战士
        Hp=3100;
        Attack=1100;
        Defense=1000;
        Exp=800;
        break;
    case 121: //初级士兵
        Hp=450;
        Attack=100;
        Defense=60;
        Exp=190;
        break;
    case 122: //中级士兵
        Hp=1250;
        Attack=380;
        Defense=300;
        Exp=550;
        break;
    case 123: //高级士兵
        Hp=1500;
        Attack=450;
        Defense=400;
        Exp=600;
        break;
    case 124: //双手剑士
        Hp=1200;
        Attack=600;
        Defense=500;
        Exp=750;
        break;
    case 125: //冥战士
        Hp=2000;
        Attack=650;
        Defense=550;
        Exp=650;
        break;
    case 126: //初级骑士
        Hp=850;
        Attack=330;
        Defense=200;
        Exp=400;
        break;
    case 127: //高级骑士
        Hp=900;
        Attack=700;
        Defense=600;
        Exp=700;
        break;
    case 128: //灵武士
        Hp=1200;
        Attack=980;
        Defense=500;
        Exp=750;
        break;
    case 129: //红衣魔王
        Hp=15000;
        Attack=1000;
        Defense=1000;
        Exp=3000;
        break;
    case 130: //魔法警卫
        Hp=1300;
        Attack=250;
        Defense=100;
        Exp=350;
        break;
    case 131: //灵法师
        Hp=1500;
        Attack=800;
        Defense=700;
        Exp=700;
        break;
    case 136: //冥队长
        Hp=3300;
        Attack=1000;
        Defense=1000;
        Exp=1500;
        break;
    case 138: //冥灵魔王
        Hp=45000;
        Attack=2500;
        Defense=2200;
        Exp=10000;
        break;
    case 148: //灵武士
        Hp=1600;
        Attack=1000;
        Defense=1000;
        Exp=1000;
        break;
    case 149: //红衣魔王
        Hp=20000;
        Attack=1200;
        Defense=1200;
        Exp=2600;
        break;

    }
    BlockTypeName=QString::number(type);
    SetLabelDisplay(parent,BlockTypeName);
}

Map_Block::~Map_Block()
{
    if(Block_Type!=1)
    {
        Display->deleteLater();
        delete Display;
        Display=0;
    }
}

bool Map_Block::SetLabelDisplay(QWidget *parent,const QString BmpFileName)
{
    QPixmap Logo;
    Display=new QLabel(parent);
    Logo=QPixmap(":/ImgRes/"+BmpFileName+".bmp");
    Display->setPixmap(Logo);
    Display->setGeometry(Block_Pos.x()*64,Block_Pos.y()*64,64,64);
    Display->show();
    return true;
}
