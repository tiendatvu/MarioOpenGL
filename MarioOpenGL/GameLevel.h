#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel
{
public:
    // level state
    std::vector<MultiSpriteGameObject> Bricks;
    // constructor
    GameLevel() {};
    // loads level from file
    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer &renderer);
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned char>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif // !GAME_LEVEL_H
