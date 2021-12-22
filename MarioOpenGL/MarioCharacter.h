#ifndef MARIO_CHARACTER
#define MARIO_CHARACTER

#include "ICharacter.h"

class MarioCharacter : ICharacter
{
public:
    MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject);
};

#endif // !MARIO_CHARACTER