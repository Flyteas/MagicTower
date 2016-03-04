#include "aboutwidget.h"
#include "ui_aboutwidget.h"
#include "ExternVar.h"
#include <QDesktopWidget>

/* About Us 窗口 */
AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    QPalette palette;
    ui->setupUi(this);
    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    this->setPalette(palette);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2-99,(desktop->height()-this->height())/2-5); //显示在地图中部
    this->show();
}

AboutWidget::~AboutWidget()
{
    ui->label->deleteLater();
    ui->pushButton->deleteLater();
    delete ui;
}

void AboutWidget::on_pushButton_clicked()
{
    this->close();
}

