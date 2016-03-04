#ifndef MAP_H
#define MAP_H
#include <QLabel>
#include <QPoint>
#include <QWidget>
#include <QPixmap>
#include <vector>
using namespace std;

class Map_Block //地图块元素类
{
public:
    Map_Block(int,QPoint,QWidget*);
    ~Map_Block();
    bool SetLabelDisplay(QWidget*,const QString);
    int Block_Type; //块元素种类
    int Hp; //血量
    int Attack; //攻击
    int Defense;    //防御
    int Exp; //击杀获得的经验
    int Buff; //增益效果
    QPoint Block_Pos;
    QLabel *Display; //显示控件
};

#endif // MAP_H
