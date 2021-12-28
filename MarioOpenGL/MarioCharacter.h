#ifndef MARIO_CHARACTER_H
#define MARIO_CHARACTER_H

#include "ICharacter.h"

class MarioCharacter : ICharacter
{
public:
    MarioCharacter(int teamNo, int status, int stage, glm::vec2 pos, glm::vec2 size, std::string spriteName, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    void CreateRegionOfInterestList(int levelIndex);
    void SetCurrentVisual();

protected:
    std::vector<RegionOfInterest*> GetStatusRois(glm::vec2 &offset, glm::vec2 &delta, const glm::vec2 &size, int numRois);

private:
};

#endif // !MARIO_CHARACTER_H