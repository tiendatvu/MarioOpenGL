#ifndef I_CHARACTER_FACTORY
#define I_CHARACTER_FACTORY

#include "ICharacter.h"

class ICharacterFactory
{
public:
    virtual ICharacter* CreateCharacter(unsigned int levelIndex, unsigned int screenWidth, unsigned int screenHeight) = 0;
};

#endif // !I_CHARACTER_FACTORY
