#ifndef MARIO_CHARACTER_FACTORY_H
#define MARIO_CHARACTER_FACTORY_H

#include "ICharacterFactory.h"
#include "MarioCharacter.h"

class MarioCharacterFactory : ICharacterFactory
{
public:
    ICharacter* CreateCharacter(unsigned int levelIndex, unsigned int screenWidth, unsigned int screenHeight);
};

#endif // !MARIO_CHARACTER_FACTORY_H
