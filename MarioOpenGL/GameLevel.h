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
    // camera position of the level
    glm::vec2 CameraPos;
    // the number of tiles could be displayed on the screen
    glm::vec2 VisibleTiles;
    glm::vec2 VisibleTileOffset;
    glm::vec2 UnitSize;
    // level state
    std::vector<MultiSpriteGameObject> Bricks;
    // constructor
    GameLevel() {};
    // loads level from file
    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer &renderer);
    // update level
    void Update(glm::vec2 playerPos);

    void ReInitTile(int index);
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned char>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif // !GAME_LEVEL_H
