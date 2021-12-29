#include "JumpCommand.h"
#include "Util.h"


JumpCommand::~JumpCommand()
{

}

JumpCommand::JumpCommand()
{
    this->GravityVelocity = glm::vec2(0, INIT_JUMP_VELOCITY_Y);
}

void JumpCommand::Execute(ICharacter *character)
{
    character->Position.x += character->IsRightToLeft ? -character->Velocity.x : character->Velocity.x;
    character->Position.y += this->GravityVelocity.y;
    this->GravityVelocity.y = this->GravityVelocity.y + GRAVITY;
}

void JumpCommand::ResetParams()
{
    this->GravityVelocity = glm::vec2(0, INIT_JUMP_VELOCITY_Y);
}