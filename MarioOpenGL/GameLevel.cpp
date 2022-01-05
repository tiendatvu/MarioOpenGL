#include "GameLevel.h"
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
    this->DotData = "";

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned char> row;
            while (sstream >> tileCode) // read each word seperated by clause
            {
                row.push_back(tileCode);
                this->DotData += tileCode;
            }
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
        {
            this->init(tileData, levelWidth, levelHeight);
        }
    }
}

void GameLevel::Update(glm::vec2 &playerPos, const glm::vec2 &playerSize, const float &screenWidth)
{
    const int delta = 2;
    int offsetX = -(this->CameraPos.x / this->UnitSize.x);

    int startX = offsetX - delta < 0 ? 0 : offsetX - delta;
    startX     = startX > TileNum.x ? TileNum.x : startX;
    int startY = 0;
    
    int endX = this->VisibleTiles.x + offsetX + delta;
    endX     = endX > TileNum.x ? TileNum.x : endX;
    int endY = TileNum.y;

    VisibleStart = glm::vec2(startX, startY);
    VisibleEnd = glm::vec2(endX, endY);

    // update camera position with Mario movement
    float halfWidth = screenWidth / 2.0f;
    if (playerPos.x > halfWidth)
    {
        if (endX < TileNum.x)
        {
            this->CameraPos.x += halfWidth - playerPos.x;
            playerPos.x = halfWidth;
        }
        else
        {
            if (playerPos.x >= screenWidth - playerSize.x)
            {
                playerPos.x = screenWidth - playerSize.x;
            }            
        }
    }
    else if (playerPos.x <= 0)
    {
        if (this->CameraPos.x >= 0)
        {
            this->CameraPos.x = 0;
        }
        else
        {
            this->CameraPos.x -= playerPos.x;
        }
        playerPos.x = 0;
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (int y = VisibleStart.y; y < VisibleEnd.y; y++)
    {
        for (int x = VisibleStart.x; x < VisibleEnd.x; x++)
        {
            int idx = TileNum.x * y + x;
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
    TileNum = glm::vec2(tileData[0].size(), tileData.size()); // note we can index vector at [0] since this function is only called if height > 0
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
    this->CameraPos = glm::vec2(0, 0);
    // Fix x, iterate y
    // -> store inside the bricks list: y * width + x    
    for (unsigned int y = 0; y < TileNum.y; y++)
    {
        for (unsigned int x = 0; x < TileNum.x; x++)
        {
            glm::vec2 pos(UnitSize.x * x, UnitSize.y * y);
            int idx = TileNum.x * y + x;
            char tmpChar = this->DotData[idx];
            // check block type from level data (2D level array)
            //if (tileData[y][x] != tmpChar)
            //{
            //    int a = 1;
            //}

            //switch (tileData[y][x])
            switch (tmpChar)
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