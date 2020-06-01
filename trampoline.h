#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#include "inert.h"

class Trampoline : public Inert
{
private:
    bool bigTrampoline; // If not big, trampoline is medium sized
    QPixmap textures[3];

    QElapsedTimer animationTimer;
    QPixmap bigTrampolineSequence[4];
    QPixmap medTrampolineSequence[2];
    int animationDelay; // in ms
    int textureNumber;

    QPointF spawnPos;

    void fromSmallToMed();
    void fromMedToBig();
    void fromBigToMed();
    void fromMedToSmall();

public:
    Trampoline(bool big);

    bool isTrampolineBig(){ return bigTrampoline; }

    void collisionOnTopHandler(ObjectModel *o) override;

    virtual void animate() override;

    void moveTo(QPointF newPosition) override;
    void moveTo(float x, float y) override;
};

#endif // TRAMPOLINE_H
