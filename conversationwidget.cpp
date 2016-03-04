#include "conversationwidget.h"
#include "ui_conversationwidget.h"
#include "ExternVar.h"
/* NPC人物对话窗口 */
ConversationWidget::ConversationWidget(QWidget *parent,QString NpcType) :
    QWidget(parent),
    ui(new Ui::ConversationWidget)
{
    QPalette palette;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->Down_Img_label->setPixmap(QPixmap(":/ImgRes/Hero_Down.bmp"));
    ui->Up_Img_label->setPixmap(QPixmap(":/ImgRes/"+NpcType+".bmp"));
    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    this->setPalette(palette);
    this->setGeometry(93,233,520,240);
    this->show();
}

ConversationWidget::~ConversationWidget()
{
    delete ui;
}

bool ConversationWidget::SetConversationText(QString Data, bool IsNpc)  //显示对话内容 IsUp为true表示是NPC说的话,false表示是Hero说的话
{
    QLabel *DisplayLabel; //指向显示内容的Label
    if(IsNpc)
    {
        DisplayLabel=ui->Up_label;
    }
    else
    {
        DisplayLabel=ui->Down_label;
    }
    for(int i=1;i<=Data.length();i++) //逐字显示，实现对话效果
    {
        DisplayLabel->setText(Data.mid(0,i++));
        UserHero->sleep(200); //等待0.2秒
    }
    UserHero->sleep(2000); //等待2秒
    return true;

}
