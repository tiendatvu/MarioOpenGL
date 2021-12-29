#ifndef JUMP_COMMAND_H
#define JUMP_COMMAND_H

#include "ICommand.h"
#include "ICharacter.h"

const static float GRAVITY = 0.2f;

class JumpCommand : public ICommand
{
private:
    glm::vec2 velocity;

public:
    void Execute(ICharacter *character);
};

#endif // !JUMP_COMMAND_H
