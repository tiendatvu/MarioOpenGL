
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
    //delete MarioPlayer;
    delete Mario;
    delete WalkingCommand;
    delete JumpingCommand;
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
    /*ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_ItemAndBrickBlocks.png", true, Util::TEXTURE_ITEM_AND_BRICK);
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_Tileset.png", false, Util::TEXTURE_TILE_SET);
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_MarioAndLuigi.png", false, Util::TEXTURE_PLAYER);*/
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_ItemAndBrickBlocks.png", true, "ItemAndBrick");
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_Tileset.png", false, "TileSet");
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/NES_SuperMarioBros_MarioAndLuigi.png", false, "Player");

    // load levels
    GameLevel overWorldLv; overWorldLv.Load("MarioOpenGL/Assets/Levels/OverWorld.lvl", this->Width, this->Height);
    this->Levels.insert(this->Levels.begin() + Util::OverWorld, overWorldLv);
    this->LevelIdx = Util::OverWorld;

    // Create characters by factories
    MarioCharacterFactory *mcFactory = new MarioCharacterFactory();
    Mario = mcFactory->CreateCharacter(this->LevelIdx, this->Width, this->Height);

    // Init Commands
    this->WalkingCommand = new WalkCommand();
    this->JumpingCommand = new JumpCommand();
}

static float timer = 0;
void MarioGame::Update(float dt)
{
    //this->Mario->Position += this->MarioPlayer->Velocity;

    //float halfWidth = this->Width / 2.0f;
    //if (this->MarioPlayer->Position.x >= halfWidth)
    //{
    //    this->Levels[this->LevelIdx].CameraPos.x += halfWidth - this->MarioPlayer->Position.x;
    //    this->MarioPlayer->Position.x = halfWidth;
    //}
    ////else if (this->MarioPlayer->Position.x < 0 && this->Levels[this->LevelIdx].CameraPos.x > 0)
    //else if (this->MarioPlayer->Position.x < 0)
    //{
    //    this->Levels[this->LevelIdx].CameraPos.x -= this->MarioPlayer->Position.x;
    //    this->MarioPlayer->Position.x = 0;
    //}

    timer += dt;
    if (timer > 0.25)
    {
        timer = 0;
        this->Mario->SetCurrentVisual();
    }
}

void MarioGame::ProcessInput(float dt)
{
    // Nếu status của Mario là MARIO_JUMP -> not doing anything
    if (Mario->Status == Util::MARIO_JUMP)
    {
        this->JumpingCommand->Execute(Mario);

        if (this->Keys[GLFW_KEY_Z])
        {
            Mario->UpdateRoisByStatus(Util::MARIO_STAND);
        }
        return;
    }

    if (this->Keys[GLFW_KEY_A])
    {
        // left
        if (!this->IsPressed)
        {
            this->IsPressed = true;
            Mario->IsRightToLeft = true;
            Mario->UpdateRoisByStatus(Util::MARIO_WALK);
        }
        this->WalkingCommand->Execute(Mario);
    }
    else if (this->Keys[GLFW_KEY_D])
    {
        // right
        if (!this->IsPressed)
        {
            this->IsPressed = true;
            Mario->IsRightToLeft = false;
            Mario->UpdateRoisByStatus(Util::MARIO_WALK);
        }
        this->WalkingCommand->Execute(Mario);
    }
    else if (this->Keys[GLFW_KEY_SPACE])
    {
        // jump
        if (!this->IsPressed)
        {
            Mario->UpdateRoisByStatus(Util::MARIO_JUMP);
            this->IsPressed = true;
        }
        this->JumpingCommand->Execute(Mario);
    }
    else if (this->Keys[GLFW_KEY_ENTER] || this->Keys[GLFW_KEY_0])
    {
        // fire
        if (!this->IsPressed)
        {
            Mario->UpdateRoisByStatus(Util::MARIO_FIRE);
            this->IsPressed = true;
        }
    }
    else
    {
        Mario->UpdateRoisByStatus(Util::MARIO_STAND);
    }
}

void MarioGame::Render()
{
    // draw level
    this->Levels[this->LevelIdx].Draw(*this->GameRenderer);

    // draw player
    this->Mario->Draw(*this->GameRenderer);
}