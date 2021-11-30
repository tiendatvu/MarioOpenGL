
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
    
    Shader shader = ResourceManager::GetShader("sprite");
    shader.Use();
    shader.SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);
    // set render-specific controls
    GameRenderer = new SpriteRenderer(shader);
    // Load textures
    ResourceManager::LoadTexture("MarioOpenGL/Assets/Tiles/ItemAndBrick.png", true, "itemAndBrick");
    //ResourceManager::LoadTexture("MarioOpenGL/Assets/Images/background.jpg", false, "background");

    
}

void MarioGame::Update(float dt)
{

}

void MarioGame::ProcessInput(float dt)
{

}

void MarioGame::Render()
{
    // draw background
    Texture2D background = ResourceManager::GetTexture("itemAndBrick");
    GameRenderer->DrawSprite(background, glm::vec2(0.0f, 0.0f),
                             glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
                             glm::vec2(this->Width, this->Height), 0.0f,
                             glm::vec3(1.0f));
}