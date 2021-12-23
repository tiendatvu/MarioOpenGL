#include "MarioCharacter.h"


MarioCharacter::MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject)
{
    this->TeamNo = teamNo;
    this->Status = status;
    this->Stage = stage;
    this->GameObject = gameObject;
}

void MarioCharacter::CreateRegionOfInterestList(int levelIndex)
{
    glm::vec2 regionScale = glm::vec2(16.0f / this->GameObject->Sprite.Width, 16.0f / this->GameObject->Sprite.Height);
    RegionOfInterest* smallMarioRegion = new RegionOfInterest(regionScale, glm::vec2(0.0f / this->GameObject->Sprite.Width, 8.0f / this->GameObject->Sprite.Height), glm::vec2(16, 16));
    this->GameObject->Rois.push_back(smallMarioRegion);
}

void MarioCharacter::SetCurrentVisual()
{

}