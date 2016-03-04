#ifndef FIGHTFALSEMSG_H
#define FIGHTFALSEMSG_H

#include <QWidget>

namespace Ui {
class FightFalseMsg;
}

class FightFalseMsg : public QWidget
{
    Q_OBJECT

public:
    explicit FightFalseMsg(QWidget *parent = 0,QString MonsterName="",const int Monster_Hp=0, const int Monster_Attack=0,const int Monster_Defense=0);
    ~FightFalseMsg();

private:
    Ui::FightFalseMsg *ui;
};

#endif // FIGHTFALSEMSG_H
