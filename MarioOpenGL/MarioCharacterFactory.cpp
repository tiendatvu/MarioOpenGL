#include "MarioCharacterFactory.h"
#include "ResourceManager.h"
#include "Util.h"

ICharacter* MarioCharacterFactory::CreateCharacter(unsigned int levelIndex, unsigned int screenWidth, unsigned int screenHeight)
{
    //Texture2D playerSprite = ResourceManager::GetTexture(Util::TEXTURE_PLAYER);
    Texture2D playerSprite = ResourceManager::GetTexture("Player");
    MultiSpriteGameObject* gameObject = new MultiSpriteGameObject(glm::vec2(0 / 2, screenHeight / 2), glm::vec2(48, 48), playerSprite, glm::vec3(1, 1, 1));
    MarioCharacter* mario = new MarioCharacter(Util::TEAM_0, Util::MARIO_STAND, Util::SMALL_STAGE, gameObject);
    mario->CreateRegionOfInterestList(levelIndex);
    return (ICharacter*)mario;
}