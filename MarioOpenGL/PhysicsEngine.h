#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "GameLevel.h"
#include "ICharacter.h"

// Handles collisions between object on the screen
class PhysicsEngine
{
public:
    void Update(ICharacter *character, GameLevel *gameLevel);
};

#endif // !PHYSICS_ENGINE_H
