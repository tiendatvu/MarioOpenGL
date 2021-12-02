#include "GameLevel.h"
#include "Util.h"

#include <fstream>
#include <sstream>

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
    //for (int x = 0; x < this->VisibleTiles.x + 1; x++)    
    //{
    //    for (int y = 0; y < this->VisibleTiles.y + 1; y++)
    //    {
    //        int idx = y * this->VisibleTiles.x + x;
    //        if (!this->Bricks[idx].IsDestroyed)
    //        {
    //            this->Bricks[idx].Draw(renderer, this->CameraPos);
    //        }
    //    }
    //}

    for (MultiSpriteGameObject &tile : this->Bricks)
    {
        if (!tile.IsDestroyed)
            tile.Draw(renderer, this->CameraPos);
    }
}

void GameLevel::init(std::vector<std::vector<unsigned char>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();  // note we can index vector at [0] since this function is only called if height > 0    
    Texture2D tileSetSprite = ResourceManager::GetTexture("Tileset");
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
    RegionOfInterest* backgroundRegion = new RegionOfInterest(regionScale, glm::vec2(349.0f / tileSetSprite.Width, 33.0f / tileSetSprite.Height), tileSize);

    // initialize level tiles based on tileData
    //glm::vec2 unitSize(unitWidth, unitHeight); // size of the texture displayed on the screen
    glm::vec2 unitSize(unitWidth * Util::TILE_SCALE, unitHeight * Util::TILE_SCALE); // size of the texture displayed on the screen
    //glm::vec2 unitSize(unitWidth * levelWidth / width, unitHeight * levelHeight / height); // size of the texture displayed on the screen
    this->VisibleTiles = glm::vec2(levelWidth / unitSize.x, levelHeight / unitSize.y);
    this->CameraPos = glm::vec2(0, 0);
    // Fix x, iterate y
    // -> store inside the bricks list: y * width + x
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            glm::vec2 pos(unitSize.x * x, unitSize.y * y);
            // check block type from level data (2D level array)
            switch (tileData[y][x])
            {
            case 'G':
                // Ground
                tmp = MultiSpriteGameObject(pos, unitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(groundRegion);
                break;
            case 'b':
                // breakable brick
                tmp = MultiSpriteGameObject(pos, unitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(breakableBrickRegion);
                break;
            case 'B':
                // Brick
                tmp = MultiSpriteGameObject(pos, unitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(brickRegion);
                break;
            case '?':
                // Question brick
                tmp = MultiSpriteGameObject(pos, unitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(questionRegion);
                break;
            case '1':
                // top left pipe
                break;
            case '2':
                // top right pipe
                break;
            case '3':
                // below left pipe
                break;
            case '4':
                // below right pipe
                break;
            default:
                tmp = MultiSpriteGameObject(pos, unitSize, tileSetSprite, glm::vec3(1, 1, 1));
                tmp.Rois.push_back(backgroundRegion);
                break;
            }

            this->Bricks.push_back(tmp);
        }
    }
}