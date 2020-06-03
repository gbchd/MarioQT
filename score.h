#ifndef SCORE_H
#define SCORE_H

#include <QPixmap>

class Score
{
private:
    static int score;
    static int coins;

public:
    static void init(){
        score=0;
        coins=0;
    }
    static void reset();
    static void add(int value);
    static void addCoin();

    static int getScore(){return score;}
    static int getCoins(){return coins;}

private:
    Score(){}
};

#endif // SCORE_H
