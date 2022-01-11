#include "WalkCommand.h"
#include "Util.h"

void WalkCommand::Execute(ICharacter *character)
{
    character->Position.x += character->IsRightToLeft ? -character->Velocity.x : character->Velocity.x;
    character->Position.y += character->Velocity.y;
}