/* 全局变量定义 */
#include <ExternVar.h>

Hero *UserHero=new Hero;
Map_Block *MapBlockData[11][11];
int MapData[22][11][11];
int TotalFloor;
bool IsMapDataVaild=true; //表示地图数据是否有效
bool IsGameOver=false; //是否已通关
