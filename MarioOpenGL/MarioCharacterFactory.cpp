#include "MarioCharacterFactory.h"
#include "ResourceManager.h"
#include "Util.h"

ICharacter* MarioCharacterFactory::CreateCharacter(unsigned int levelIndex, unsigned int screenWidth, unsigned int screenHeight)
{
    Texture2D playerSprite = ResourceManager::GetTexture("Player");
    glm::vec2 regionScale;
    switch (levelIndex)
    {
    default:
        regionScale = glm::vec2(16.0f / playerSprite.Width, 16.0f / playerSprite.Height);
        break;
    }
    RegionOfInterest* smallMarioRegion = new RegionOfInterest(regionScale, glm::vec2(0.0f / playerSprite.Width, 8.0f / playerSprite.Height), glm::vec2(16, 16));
    MultiSpriteGameObject* gameObject = new MultiSpriteGameObject(glm::vec2(0 / 2, screenHeight / 2), glm::vec2(48, 48), playerSprite, glm::vec3(1, 1, 1));
    gameObject->Rois.push_back(smallMarioRegion);

    MarioCharacter* mario = new MarioCharacter(Util::TEAM_0, Util::MARIO_STAND, Util::MARIO_SMALL_STAGE, gameObject);
    return (ICharacter*)mario;
}