#ifndef FIGHTWIDGET_H
#define FIGHTWIDGET_H
/* 战斗界面类 */
#include <QWidget>

namespace Ui {
class FightWidget;
}

class FightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FightWidget(QWidget *parent = 0,QString MonsterName="");
    ~FightWidget();
public slots:
    bool FightWidgetStateChange(const int,const int,const int,const int);

private:
    Ui::FightWidget *ui;
};

#endif // FIGHTWIDGET_H
