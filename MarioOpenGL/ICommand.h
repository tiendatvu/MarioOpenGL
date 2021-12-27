#ifndef I_COMMAND_H
#define I_COMMAND_H

#include "ICharacter.h"

class ICommand
{
private:


public:
    virtual void Execute(ICharacter *character) = 0;
};

#endif // !I_COMMAND_H
