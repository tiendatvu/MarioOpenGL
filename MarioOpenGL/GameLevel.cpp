#include "GameLevel.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->Bricks.clear();
    // load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
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

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (MultiSpriteGameObject &tile : this->Bricks)
    {
        if (!tile.IsDestroyed)
        {
            tile.Draw(renderer);
        }
    }
}

void GameLevel::init(std::vector<std::vector<unsigned char>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();  // note we can index vector at [0] since this function is only called if height > 0
    float unitWidth = levelWidth / static_cast<float> (width);
    float unitHeight = levelHeight / static_cast<float> (height);

    // initialize level tiles based on tileData
    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            // check block type from level data (2D level array)
            switch (tileData[y][x])
            {
            case 'G':
                break;
            case 'B':
                break;
            case 'Q':
                break;
            case 'P':
                break;
            default:
                break;
            }
        }
    }
}