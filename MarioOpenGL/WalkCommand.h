#ifndef WALK_COMMAND_H
#define WALK_COMMAND_H

#include "ICommand.h"
#include "ICharacter.h"

class WalkCommand : public ICommand
{
private:


public:
    void Execute(ICharacter *character);

};


#endif // !WALK_COMMAND_H
