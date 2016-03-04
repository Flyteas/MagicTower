#include "fightfalsemsg.h"
#include "ui_fightfalsemsg.h"
#include "ExternVar.h"

FightFalseMsg::FightFalseMsg(QWidget *parent,QString MonsterName,const int Monster_Hp, const int Monster_Attack,const int Monster_Defense) :
    QWidget(parent),
    ui(new Ui::FightFalseMsg)
{
    QPalette palette;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->Hero_Img_label->setPixmap(QPixmap(":/ImgRes/Hero_Down.bmp"));
    ui->Monster_Img_label->setPixmap(QPixmap(":/ImgRes/"+MonsterName+".bmp"));
    ui->Monster_Hp->setText(QString::number(Monster_Hp));
    ui->Monster_attack->setText(QString::number(Monster_Attack));
    ui->Monster__defense->setText(QString::number(Monster_Defense));
    ui->Hero_Hp->setText(QString::number(UserHero->UserHeroState.Hp));
    ui->Hero_attack->setText(QString::number(UserHero->UserHeroState.Attack));
    ui->Hero_defense->setText(QString::number(UserHero->UserHeroState.Defense));
    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    this->setPalette(palette);
    this->setGeometry(93,233,520,240);
    this->show();
}

FightFalseMsg::~FightFalseMsg()
{
    delete ui;
}
