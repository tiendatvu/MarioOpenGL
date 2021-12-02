#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

// Container object for holding all state relevant for a single game object entity.
// Each object in the game likely needs the minimal of state as described within GameObject.
//class GameObject
//{
//public:
//    // Represent the position in the sprite sheet
//    glm::vec2 Roi, Offset;
//    // Object state
//    glm::vec2 Position, Size, Velocity;
//    glm::vec3 Color;
//    float     Rotation;
//    bool      IsSolid;
//    bool      IsDestroyed;
//    // render state
//    Texture2D Sprite;
//    // constructors
//    GameObject();
//    GameObject(glm::vec2 pos, glm::vec2 roi, glm::vec2 offset, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
//    // draw sprite
//    virtual void Draw(SpriteRenderer &renderer);
//};

class RegionOfInterest
{
public:
    // Ranging from [0:1][0:1] = [0:width][0:height]
    glm::vec2 RegionScale;
    // Ranging from [0:1][0:1] = [0:width][0:height]
    glm::vec2 OffsetScale;
    // Size to display on the screen
    glm::vec2 Size;

    RegionOfInterest(glm::vec2 region, glm::vec2 offset, glm::vec2 size) 
    : RegionScale(region), OffsetScale(offset), Size(size)
    {}
};

class MultiSpriteGameObject
{
public:
    // object state
    glm::vec2                      Position, Size, Velocity;
    glm::vec3                      Color;
    float                          Rotation;
    bool                           IsSolid;
    bool                           IsDestroyed;
    int                            RoiIdx;
    std::vector<RegionOfInterest*> Rois;

    // render state
    Texture2D Sprite;
    // constructor(s)
    MultiSpriteGameObject();
    MultiSpriteGameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer &renderer);
    virtual void Draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition);
};

#endif // !GAME_OBJECT_H
