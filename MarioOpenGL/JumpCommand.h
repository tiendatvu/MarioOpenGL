#ifndef JUMP_COMMAND_H
#define JUMP_COMMAND_H

#include "ICommand.h"
#include "ICharacter.h"

const static float GRAVITY = 0.2f;
const static float INIT_JUMP_VELOCITY_Y = -9.0f;

class JumpCommand : public ICommand
{
private:
    glm::vec2 GravityVelocity;

public:
    ~JumpCommand();
    JumpCommand();
    void Execute(ICharacter *character);
    void ResetParams();
};

#endif // !JUMP_COMMAND_H
