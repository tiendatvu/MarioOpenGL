#include "WalkCommand.h"

void WalkCommand::Execute(ICharacter *character)
{
    character->GameObject->Position.x += character->GameObject->Velocity.x;
}