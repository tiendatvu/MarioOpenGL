﻿
#include "Util.h"
#include "MarioGame.h"
#include "ResourceManager.h"
#include <iostream>

MarioGame::MarioGame(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

MarioGame::~MarioGame()
{
    delete GameRenderer;
    delete MarioPlayer;
}

void MarioGame::Init()
{
    // Load shaders
    ResourceManager::LoadShader("MarioOpenGL/Shaders/sprite.vs", "MarioOpenGL/Shaders/sprite.frs", nullptr, "sprite");
    // configure projection
    // do ta định nghĩa top-left là (0, 0)
    // mà camera ortho sẽ convert hệ tọa độ [-1 : 1]
    // do đó, horizontally: 0 -> width  tương ứng [-1 : 1]
    //        vertically:   0 -> height tương ứng [-1 : 1]
    // Tại SpriteRenderer, ta định nghĩa
    // float vertices[] = {
    //     // pos      // tex
    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 0.0f, 0.0f,
    // 
    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f, 0.0f
    // };
    // như vậy, với position được định nghĩa, texture sẽ được render tại vị trí (0,0) đến (1,1) trên hệ trục tọa độ
    // -> texture sẽ được render tại top-left = gốc (0, 0) của bức ảnh    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width / Util::TILE_SCALE), static_cast<float>(this->Height / Util::TILE_SCALE), 0.0f, -1.0f, 1.0f);    

    // configure shader
    Shader shader = ResourceManager::GetShader("sprite");
    shader.Use();
    shader.SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);
    // set render-specific controls
    GameRenderer = new SpriteRenderer(shader);
    // Load textures    
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_ItemAndBrickBlocks.png", true, "ItemAndBrick");
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_Tileset.png", false, "Tileset");
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_MarioAndLuigi.png", false, "Player");

    // load levels
    GameLevel overWorldLv; overWorldLv.Load("MarioOpenGL/Assets/Levels/OverWorld.lvl", this->Width, this->Height);
    this->Levels.push_back(overWorldLv);
    this->LevelIdx = 0;

    // load mario player
    Texture2D playerSprite = ResourceManager::GetTexture("Player");
    glm::vec2 regionScale = glm::vec2(16.0f / playerSprite.Width, 16.0f / playerSprite.Height);
    RegionOfInterest* smallMarioRegion = new RegionOfInterest(regionScale, glm::vec2(0.0f / playerSprite.Width, 8.0f / playerSprite.Height), glm::vec2(16, 16));
    MarioPlayer = new MultiSpriteGameObject(glm::vec2(0 / 2, this->Height / 2), glm::vec2(48, 48), playerSprite, glm::vec3(1, 1, 1));
    MarioPlayer->Rois.push_back(smallMarioRegion);
}

void MarioGame::Update(float dt)
{
    this->MarioPlayer->Position += this->MarioPlayer->Velocity;

    float halfWidth = this->Width / 2.0f;
    if (this->MarioPlayer->Position.x >= halfWidth)
    {
        this->Levels[this->LevelIdx].CameraPos.x += halfWidth - this->MarioPlayer->Position.x;
        this->MarioPlayer->Position.x = halfWidth;
    }
    //else if (this->MarioPlayer->Position.x < 0 && this->Levels[this->LevelIdx].CameraPos.x > 0)
    else if (this->MarioPlayer->Position.x < 0)
    {
        this->Levels[this->LevelIdx].CameraPos.x -= this->MarioPlayer->Position.x;
        this->MarioPlayer->Position.x = 0;
    }
}

void MarioGame::ProcessInput(float dt)
{
    if (this->Keys[GLFW_KEY_A])
    {
        // left
        this->MarioPlayer->Velocity = glm::vec2(-Util::MARIO_NORMAL_SPEED, 0);
    }
    else if (this->Keys[GLFW_KEY_D])
    {
        // right
        this->MarioPlayer->Velocity = glm::vec2(Util::MARIO_NORMAL_SPEED, 0);
    }
    else if (this->Keys[GLFW_KEY_SPACE])
    {
        // jump

    }
    else if (this->Keys[GLFW_KEY_ENTER] || this->Keys[GLFW_KEY_0])
    {
        // fire

    }
    else
    {
        this->MarioPlayer->Velocity = glm::vec2(0, 0);
    }
}

void MarioGame::Render()
{
    // draw level
    this->Levels[this->LevelIdx].Draw(*this->GameRenderer);

    // draw player
    this->MarioPlayer->Draw(*this->GameRenderer);
}