
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
    for (int i = 0; i < this->Levels.size(); i++)
    {
        delete this->Levels[i];
    }
    this->Levels.clear();

    delete GameRenderer;
    delete Mario;
    delete WalkingCommand;
    delete JumpingCommand;
    delete GamePhysicsEngine;
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
    GameLevel *overWorldLv = new GameLevel();
    overWorldLv->Load("MarioOpenGL/Assets/Levels/OverWorld.lvl", this->Width, this->Height);
    this->Levels.insert(this->Levels.begin() + Util::OverWorld, overWorldLv);
    this->LevelIdx = Util::OverWorld;

    // Create characters by factories
    MarioCharacterFactory *mcFactory = new MarioCharacterFactory();
    Mario = mcFactory->CreateCharacter(this->LevelIdx, this->Width, this->Height);

    // Init Commands
    this->WalkingCommand = new WalkCommand();
    this->JumpingCommand = new JumpCommand();
    this->FallingCommand = new FallCommand();
    

    // Init Engines
    this->GamePhysicsEngine = new PhysicsEngine();
}

static float timer = 0.0f;
static glm::vec2 marioPos = glm::vec2(-1, 0);
void MarioGame::Update(float dt)
{
    // Update displayed items on the screen
    if (marioPos.x - this->Mario->Position.x != 0)
    {
        this->Levels[this->LevelIdx]->Update(this->Mario->Position, this->Mario->Size, this->Width);
        marioPos.x = this->Mario->Position.x;
    }

    // Handles collisions
    this->GamePhysicsEngine->Update(this->Mario, this->Levels[this->LevelIdx]);

    timer += dt;
    if (timer <= 0.25)
    {
        return;
    }
    timer = 0.0f;

    // Update current visual of the Mario/Luigi
    this->Mario->SetCurrentVisual();
}

void MarioGame::ProcessInput(float dt)
{
    // Nếu status của Mario là MARIO_JUMP -> not doing anything
    if (Mario->Status == Util::MARIO_JUMP)
    {
        this->JumpingCommand->Execute(Mario);
        return;
    }
    else if (Mario->Status == Util::MARIO_FALL)
    {
        this->FallingCommand->Execute(Mario);
        return;
    }

    if (this->Keys[GLFW_KEY_A])
    {
        // left
        if (!this->IsPressed)
        {
            this->IsPressed = true;
            Mario->IsRightToLeft = true;
            Mario->UpdatePropertiesByStatus(Util::MARIO_WALK);
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
            Mario->UpdatePropertiesByStatus(Util::MARIO_WALK);
        }
        this->WalkingCommand->Execute(Mario);
    }
    else if (this->Keys[GLFW_KEY_SPACE])
    {
        // jump
        if (!this->IsPressed)
        {
            Mario->UpdatePropertiesByStatus(Util::MARIO_JUMP);
            this->IsPressed = true;
        }
        this->JumpingCommand->Execute(Mario);
        Mario->IsOnGround = false;
    }
    else if (this->Keys[GLFW_KEY_ENTER] || this->Keys[GLFW_KEY_0])
    {
        // fire
        if (!this->IsPressed)
        {
            Mario->UpdatePropertiesByStatus(Util::MARIO_FIRE);
            this->IsPressed = true;
        }
    }
    else
    {
        Mario->UpdatePropertiesByStatus(Util::MARIO_STAND);
    }
}

void MarioGame::Render()
{
    // draw level
    this->Levels[this->LevelIdx]->Draw(*this->GameRenderer);

    // draw player
    this->Mario->Draw(*this->GameRenderer);
}