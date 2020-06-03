#include "score.h"
#include <QDebug>

int Score::score;
int Score::coins;


void Score::reset(){
    score = 0;
    coins = 0;
}

void Score::add(int value){
    score += value;
}

void Score::addCoin(){
    coins++;
}
