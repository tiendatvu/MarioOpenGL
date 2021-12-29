#include "MarioCharacterFactory.h"
#include "Util.h"

ICharacter* MarioCharacterFactory::CreateCharacter(unsigned int levelIndex, unsigned int screenWidth, unsigned int screenHeight)
{
    //Texture2D playerSprite = ResourceManager::GetTexture(Util::TEXTURE_PLAYER);
    //MarioCharacter* mario = new MarioCharacter(Util::TEAM_0, Util::MARIO_STAND, Util::SMALL_STAGE, gameObject);
    glm::vec2 initPost = glm::vec2(90 / 2, screenHeight / 2);
    glm::vec2 initSize = glm::vec2(48, 48);
    glm::vec3 initColor = glm::vec3(1, 1, 1);
    //glm::vec2 initSpeed = glm::vec2(Util::MARIO_WALK_SPEED, Util::MARIO_WALK_SPEED);
    glm::vec2 initSpeed = glm::vec2(3.0f, 3.0f);
    MarioCharacter* mario = new MarioCharacter(Util::TEAM_0, Util::MARIO_STAND, Util::SMALL_STAGE,
                                               initPost, initSize, "Player", initColor, initSpeed);
    
    mario->CreateRegionOfInterestList(levelIndex);
    return (ICharacter*)mario;
}