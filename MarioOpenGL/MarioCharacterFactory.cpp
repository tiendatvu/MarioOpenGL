#include "ICharacterFactory.h"
#include "MarioCharacter.h"

class MarioCharacterFactory : public ICharacterFactory
{
public:
    ICharacter* CreateCharacter()
    {
        MarioCharacter *mario = new MarioCharacter();
        return mario;
    }
};