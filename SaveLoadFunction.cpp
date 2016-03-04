#include <SaveLoadFunction.h>
#include <QFile>
#include <QTextStream>
#include <ExternVar.h>
#include <QMessageBox>
#include <QTextCodec>

bool LoadMap(QString DefaultFileDir,QString UserFileDir)
{
    QFile *File;
    QFile *UserFile=new QFile(UserFileDir);
    QFile *DefaultFile=new QFile(DefaultFileDir);
    if(!UserFile->exists()&&!DefaultFile->exists()) //如果两个文件都不存在，则返回false
    {
        for(int j=0;j<11;j++)
        {
            for(int i=0;i<11;i++)
            {
                MapData[0][j][i]=1; //全部填充地图为空地
                UserHero->UserHeroState.FloorNum=1;
            }
        }
        IsMapDataVaild=false; //标识地图数据无效
        delete UserFile;
        UserFile=0;
        delete DefaultFile;
        DefaultFile=0;
        return false;
    }
    if(UserFile->exists()) //存在用户数据文件则载入用户数据
    {
        File=new QFile(UserFileDir);
    }
    else
    {
        File=new QFile(DefaultFileDir); //不存在用户数据文件则载入初始数据
    }
    delete UserFile;
    UserFile=0;
    delete DefaultFile;
    DefaultFile=0;

    QString MapDataFromFile;
    bool IsMapDataEnd=false;
    int LoadStateData[11]; //九个英雄状态数据
    int i=0;//列数
    int j=0;//行数
    int k=0;//层数
    int StateDataNum=0; //第几个状态数据
    if(!(File->open(QIODevice::ReadOnly|QIODevice::Text)))
    {
        return false;
    }
    while(!File->atEnd()) //逐行读取文件数据
    {
        i=0;
        QByteArray line = File->readLine();
        QString LineStr(line);
        if(LineStr.indexOf("TotalFloor")!=-1) //判断是否是记录总层数行
        {
            TotalFloor=LineStr.mid(10,LineStr.indexOf(";")-10).toInt(); //获取地图总层数
        }
        if(LineStr.indexOf("MapDataEnd")!=-1) //判断是否到达地图数据末尾，此时英雄数据开始
        {
            IsMapDataEnd=true;
            continue;
        }

        if(LineStr.indexOf("f")!=-1&&!IsMapDataEnd) //判断当前行是否是层数记录行
        {
            k=LineStr.mid(1).toInt()-1;
            j=0;
            continue;
        }
        while (!IsMapDataEnd)
        {
            MapDataFromFile=LineStr.mid(0,LineStr.indexOf(","));
            MapData[k][j][i]=MapDataFromFile.toInt();
            i++;
            if(LineStr.indexOf(",")==-1)
            {
                break;
            }
            LineStr=LineStr.mid(LineStr.indexOf(",")+1);
        }
        j++;
        if(IsMapDataEnd) //载入英雄状态数据
        {
            LoadStateData[StateDataNum]=LineStr.mid(0,LineStr.indexOf(";")).toInt();
            StateDataNum++;
        }
    }
    UserHero->UserHeroState.FloorNum=LoadStateData[0]; //楼层数
    UserHero->UserHeroState.Hp=LoadStateData[1];        //血量
    UserHero->UserHeroState.Attack=LoadStateData[2]; //攻击
    UserHero->UserHeroState.Defense=LoadStateData[3]; //防御
    UserHero->UserHeroState.Exp=LoadStateData[4]; //经验
    UserHero->UserHeroState.Level=LoadStateData[5]; //等级
    UserHero->UserHeroState.BlueKeyNum=LoadStateData[6]; //蓝钥匙
    UserHero->UserHeroState.RedKeyNum=LoadStateData[7]; //红钥匙
    UserHero->UserHeroState.YellowKeyNum=LoadStateData[8]; //黄钥匙数量;
    UserHero->SetHeroPos(QPoint(LoadStateData[9],LoadStateData[10])); //初始位置坐标
    File->close();
    return true;
}

bool SaveGame(QString SaveFileDir) //保存游戏数据
{
    if(!IsMapDataVaild) //如果地图数据无效则不保存
    {
        return false;
    }
    QFile SaveFile(SaveFileDir);
    if(!SaveFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream OutStream(&SaveFile);
    OutStream<<"TotalFloor"<<QString::number(TotalFloor)<<";//Total Floor number"<<endl;
    for(int k=0;k<TotalFloor;k++)
    {
        OutStream<<"f"<<QString::number(k+1)<<endl;
        for(int j=0;j<11;j++)
        {
            for(int i=0;i<10;i++)
            {
                OutStream<<QString::number(MapData[k][j][i])<<",";
            }
            OutStream<<QString::number(MapData[k][j][10])<<endl;
        }
    }
    OutStream<<"MapDataEnd"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.FloorNum)<<"; //Floor"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.Hp)<<"; //HP"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.Attack)<<"; //Attack"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.Defense)<<"; //Defense"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.Exp)<<"; //Exp"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.Level)<<"; //Level"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.BlueKeyNum)<<"; //Blue Key Number"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.RedKeyNum)<<"; //Red Key Number"<<endl;
    OutStream<<QString::number(UserHero->UserHeroState.YellowKeyNum)<<"; //Yellow Key Number"<<endl;
    OutStream<<QString::number(UserHero->GetHeroPos().x())<<"; //Hero's X postion"<<endl;
    OutStream<<QString::number(UserHero->GetHeroPos().y())<<"; //Hero's Y postion";
    SaveFile.close();
    return true;

}
