#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <QString>

class StatsModel
{
private:
    int score;
    int coins;
    QString mapName;
    int time;

public:
    StatsModel();

    void inline incrementCoins(){ coins++; }
    void inline setCoins(int c){ coins = c; }
    int inline getCoins(){ return coins; }
    void inline setScore(int s){ score = s; }
    int inline getScore(){ return score; }
    void inline setMapName(QString m){ mapName = m; }
    QString inline getMapName(){ return mapName; }
};

#endif // STATSMODEL_H
