#include "WalkCommand.h"

void WalkCommand::Execute(ICharacter *character)
{
    character->Position.x += character->IsRightToLeft ? -character->Velocity.x : character->Velocity.x;
}