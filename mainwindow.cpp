#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QKeyEvent>
#include <QEvent>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include "conversationwidget.h"
#include "aboutwidget.h"
#include "SaveLoadFunction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!LoadMap("./DefaultData.dat","./UserData.dat")) //载入数据，并判断是否载入成功
    {
        QMessageBox::information(0,"错误","找不到地图数据文件!");
    }
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/ImgRes/Background.bmp")));
    ui->setupUi(this);
    ui->centralWidget->setPalette(palette);
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/ImgRes/Key_Yellow_32.bmp")));
    ui->YellowKey_widget->setPalette(palette);
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/ImgRes/Key_Red_32.bmp")));
    ui->RedKey_widget->setPalette(palette);
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/ImgRes/Key_Blue_32.bmp")));
    ui->BlueKey_widget->setPalette(palette);
    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    ui->Devide->setPalette(palette);
    connect(UserHero,SIGNAL(SendHeroStateChanged(const HeroState&)),this,SLOT(HeroStateLabelDisplayChange(const HeroState&)));
    connect(UserHero,SIGNAL(SendCloseMainWindow()),this,SLOT(close()));
    UserHero->SetHeroDisplay(this->centralWidget());
    UserHero->FloorChange(UserHero->UserHeroState.FloorNum); //载入当前层 的地图
    UserHero->UpdateDisplayPos();
    UserHero->SetLogo(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::keyPressEvent(QKeyEvent* event)
{
     if(UserHero->IsHeroFighting) //判断是否正处于战斗状态中
     {
         return;
     }
    if (event->key()==Qt::Key_Up) //按上键
    {
        UserHero->SetLogo(1);
        UserHero->HeroNext(1);
    }
    if (event->key()==Qt::Key_Down) //按下键
    {
        UserHero->SetLogo(2);
        UserHero->HeroNext(2);
    }
    if (event->key()==Qt::Key_Left) //按左键
    {     
        UserHero->SetLogo(3);
        UserHero->HeroNext(3);
    }
    if (event->key()==Qt::Key_Right) //按右键
    {
        UserHero->SetLogo(4);
        UserHero->HeroNext(4);
    }
}

 bool MainWindow::HeroStateLabelDisplayChange(const HeroState& Newdata)
 {
     ui->Hp_label->setText(QString::number(Newdata.Hp));
     ui->Attack_label->setText(QString::number(Newdata.Attack));
     ui->BlueKey_label->setText(QString::number(Newdata.BlueKeyNum));
     ui->Defense_label->setText(QString::number(Newdata.Defense));
     ui->Exp_label->setText(QString::number(Newdata.Exp));
     ui->Floor_label->setText(QString::number(Newdata.FloorNum));
     ui->Level_label->setText(QString::number(Newdata.Level));
     ui->RedKye_label->setText(QString::number(Newdata.RedKeyNum));
     ui->YellowKey_label->setText(QString::number(Newdata.YellowKeyNum));
     return true;
 }

void MainWindow::on_SaveButton_clicked()
{
    if(SaveGame("./UserData.dat")) //保存游戏数据
    {
        QMessageBox::information(0,"保存成功","游戏进度保存成功!");
    }
    else
    {
        QMessageBox::information(0,"保存失败","游戏进度保存失败!");
    }
}

void MainWindow::on_ResetButton_clicked()
{
    QMessageBox ResetMsg(QMessageBox::Question,"提示","重新开始游戏？\n原游戏进度将会被覆盖!",QMessageBox::Yes|QMessageBox::No);
    if(ResetMsg.exec()==QMessageBox::No)
    {
        return;
    }
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


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(IsGameOver)
    {
        return;
    }
    QMessageBox SaveMsg(QMessageBox::Question,"关闭程序","是否保存游戏进度?",QMessageBox::Yes|QMessageBox::No);
    if(SaveMsg.exec()==QMessageBox::Yes)
    {
        if(SaveGame("./UserData.dat"))
        {
            QMessageBox::information(0,"成功","保存游戏进度成功！");
        }
        else
        {
            QMessageBox::information(0,"失败","保存游戏进度失败！");
        }
    }
}
