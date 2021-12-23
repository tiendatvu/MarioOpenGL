#include "MarioCharacter.h"


MarioCharacter::MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject)
{
    this->TeamNo = teamNo;
    this->Status = status;
    this->Stage = stage;
    this->GameObject = gameObject;
}
