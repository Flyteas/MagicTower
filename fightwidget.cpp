#include "fightwidget.h"
#include "ui_fightwidget.h"
#include "ExternVar.h"

FightWidget::FightWidget(QWidget *parent,QString MonsterName) :
    QWidget(parent),
    ui(new Ui::FightWidget)
{
    QPalette palette;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->Hero_Img_label->setPixmap(QPixmap(":/ImgRes/Hero_Down.bmp"));
    ui->Monster_Img_label->setPixmap(QPixmap(":/ImgRes/"+MonsterName+".bmp"));
    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    this->setPalette(palette);
    this->setGeometry(93,233,520,240);
    this->show();
}

FightWidget::~FightWidget()
{
    delete ui;
}


bool FightWidget::FightWidgetStateChange(const int Monster_Hp, const int Monster_Attack,const int Monster_Defense,const int Exp)
{
    ui->Monster_Hp->setText(QString::number(Monster_Hp));
    ui->Monster_attack->setText(QString::number(Monster_Attack));
    ui->Monster__defense->setText(QString::number(Monster_Defense));
    ui->Hero_Hp->setText(QString::number(UserHero->UserHeroState.Hp));
    ui->Hero_attack->setText(QString::number(UserHero->UserHeroState.Attack));
    ui->Hero_defense->setText(QString::number(UserHero->UserHeroState.Defense));
    if(Monster_Hp==0)
    {
        ui->Win_label->setText("Hero Win!\nExp:+"+QString::number(Exp));
    }
    return true;
}
