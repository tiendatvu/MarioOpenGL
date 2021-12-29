#include "JumpCommand.h"
#include "Util.h"

void JumpCommand::Execute(ICharacter *character)
{
    character->Velocity.y += character->Velocity.y > 0 ? -GRAVITY : GRAVITY;
    character->Position.y -= character->Velocity.y;
    velocity.x = character->IsRightToLeft ? -character->Velocity.x : character->Velocity.x;

    character->Position += velocity;
}