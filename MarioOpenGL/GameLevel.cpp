﻿#include "GameLevel.h"
#include "Util.h"

#include <fstream>
#include <sstream>
#include <math.h>

static std::string solDir = _SOLUTION_DIR;

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->Bricks.clear();
    // load from file
    unsigned char tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(solDir + file);
    std::vector<std::vector<unsigned char>> tileData;

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned char> row;
            while (sstream >> tileCode) // read each word seperated by clause
            {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
        {
            this->init(tileData, levelWidth, levelHeight);
        }
    }
}

void GameLevel::Update(glm::vec2 playerPos)
{

}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    int numX = this->VisibleTiles.x + this->VisibleTileOffset.x + 1;
    int numY = this->VisibleTiles.y + this->VisibleTileOffset.y + 1;
    for (int x = this->VisibleTileOffset.x; x < numX; x++)
    //for (int x = this->VisibleTileOffset.x; x < this->VisibleTiles.x + 1; x++)
    {
        for (int y = this->VisibleTileOffset.y; y < this->VisibleTiles.y + 1; y++)
        {
            int idx = y * this->VisibleTiles.x + x;
            //int idx = x * this->VisibleTiles.y + y;
            if (!this->Bricks[idx].IsDestroyed)
            {
                this->Bricks[idx].Draw(renderer, this->CameraPos);
            }
        }
    }

    //for (MultiSpriteGameObject &tile : this->Bricks)
    //{
    //    if (!tile.IsDestroyed)
    //        tile.Draw(renderer, this->CameraPos);
    //}
}

// Trong trường hơp này, chỉ reinit lại thành background.
// TODO: init lại với các trường hợp background khác nhau
void GameLevel::ReInitTile(int index)
{
    // TODO: làm lại đoạn code này
    Texture2D tileSetSprite = ResourceManager::GetTexture("TileSet");
    float unitWidth = 16.0f;
    float unitHeight = 16.0f;
    glm::vec2 regionScale = glm::vec2(unitWidth / tileSetSprite.Width, unitHeight / tileSetSprite.Height);
    glm::vec2 tileSize(unitWidth, unitHeight); // tile size in the sprite sheet
    RegionOfInterest* backgroundRegion = new RegionOfInterest(regionScale, glm::vec2(349.0f / tileSetSprite.Width, 33.0f / tileSetSprite.Height), tileSize);

    // 
    int roiSize = this->Bricks[index].Rois.size();
    for (size_t i = 0; i < roiSize; i++)
    {
        delete this->Bricks[index].Rois[i];
    }
    this->Bricks[index].Rois.clear();
    this->Bricks[index].Rois.shrink_to_fit();


    this->Bricks[index].Rois.push_back(backgroundRegion);
}

void GameLevel::init(std::vector<std::vector<unsigned char>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();  // note we can index vector at [0] since this function is only called if height > 0    
    //Texture2D tileSetSprite = ResourceManager::GetTexture(Util::TEXTURE_TILE_SET);
    Texture2D tileSetSprite = ResourceManager::GetTexture("TileSet");
    float unitWidth = 16.0f;
    float unitHeight = 16.0f;
    glm::vec2 regionScale = glm::vec2(unitWidth / tileSetSprite.Width, unitHeight / tileSetSprite.Height);
    // Define brick types
    glm::vec2 tileSize(unitWidth, unitHeight); // tile size in the sprite sheet
    MultiSpriteGameObject tmp;
    RegionOfInterest* groundRegion = new RegionOfInterest(regionScale, glm::vec2(0.0f, 16.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* breakableBrickRegion = new RegionOfInterest(regionScale, glm::vec2(17.0f / tileSetSprite.Width, 16.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* brickRegion = new RegionOfInterest(regionScale, glm::vec2(34.0f / tileSetSprite.Width, 16.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* questionRegion = new RegionOfInterest(regionScale, glm::vec2(298.0f / tileSetSprite.Width, 78.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* pipe1Region = new RegionOfInterest(regionScale, glm::vec2(119.0f / tileSetSprite.Width, 196.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* pipe2Region = new RegionOfInterest(regionScale, glm::vec2(136.0f / tileSetSprite.Width, 196.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* pipe3Region = new RegionOfInterest(regionScale, glm::vec2(119.0f / tileSetSprite.Width, 213.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* pipe4Region = new RegionOfInterest(regionScale, glm::vec2(136.0f / tileSetSprite.Width, 213.0f / tileSetSprite.Height), tileSize);
    RegionOfInterest* backgroundRegion = new RegionOfInterest(regionScale, glm::vec2(349.0f / tileSetSprite.Width, 33.0f / tileSetSprite.Height), tileSize);

    // initialize level tiles based on tileData
    //glm::vec2 unitSize(unitWidth, unitHeight); // size of the texture displayed on the screen
    UnitSize = glm::vec2(unitWidth * Util::TILE_SCALE, unitHeight * Util::TILE_SCALE); // size of the texture displayed on the screen
    //glm::vec2 unitSize(unitWidth * levelWidth / width, unitHeight * levelHeight / height); // size of the texture displayed on the screen
    this->VisibleTiles = glm::vec2(levelWidth / UnitSize.x, levelHeight / UnitSize.y);
    this->VisibleTileOffset = glm::vec2(0, 0);
    this->CameraPos = glm::vec2(0, 0);
    // Fix x, iterate y
    // -> store inside the bricks list: y * width + x
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            glm::vec2 pos(UnitSize.x * x, UnitSize.y * y);
            // check block type from level data (2D level array)
            switch (tileData[y][x])
            {
            case 'G':
                // Ground
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(groundRegion);
                break;
            case 'b':
                // breakable brick
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(breakableBrickRegion);
                break;
            case 'B':
                // Brick
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(brickRegion);
                break;
            case '?':
                // Question brick
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(questionRegion);
                break;
            case '1':
                // top left pipe
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(pipe1Region);
                break;
            case '2':
                // top right pipe
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(pipe2Region);
                break;
            case '3':
                // below left pipe
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(pipe3Region);
                break;
            case '4':
                // below right pipe
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(pipe4Region);
                break;
            default:
                tmp = MultiSpriteGameObject(pos, UnitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(backgroundRegion);
                break;
            }

            this->Bricks.push_back(tmp);
        }
    }
}