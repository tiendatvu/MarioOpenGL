#ifndef MARIO_CHARACTER_H
#define MARIO_CHARACTER_H

#include "ICharacter.h"

class MarioCharacter : ICharacter
{
public:
    MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject);
    void CreateRegionOfInterestList(int levelIndex);
    void SetCurrentVisual();

protected:
    std::vector<RegionOfInterest*> GetStatusRois(glm::vec2 &offset, glm::vec2 &delta, const glm::vec2 &size, int numRois);

private:
};

#endif // !MARIO_CHARACTER_H