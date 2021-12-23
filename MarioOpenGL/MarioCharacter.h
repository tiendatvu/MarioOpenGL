#ifndef MARIO_CHARACTER_H
#define MARIO_CHARACTER_H

#include "ICharacter.h"

class MarioCharacter : ICharacter
{
public:
    MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject);
    void CreateRegionOfInterestList(int levelIndex);
    void SetCurrentVisual();
};

#endif // !MARIO_CHARACTER_H