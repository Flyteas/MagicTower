#ifndef EXTERNVAR_H
#define EXTERNVAR_H
#include <Hero.h>
#include <Tower_Map.h>
/*  全局变量声明  */
extern Hero *UserHero;
extern Map_Block *MapBlockData[11][11];
extern int MapData[22][11][11];
extern int TotalFloor;
extern bool IsMapDataVaild; //标识地图数据是否有效
extern bool IsGameOver; //标识是否已经通关完毕
#endif // EXTERNVAR_H
