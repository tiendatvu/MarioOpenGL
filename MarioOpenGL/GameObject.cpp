#include "GameObject.h"

MultiSpriteGameObject::MultiSpriteGameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), IsDestroyed(false), IsRightToLeft(false)
{
    this->RoiIdx = 0;
    this->RoiIteratorDirection = 1;
}
MultiSpriteGameObject::MultiSpriteGameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), IsDestroyed(false), IsRightToLeft(false)
{
    this->RoiIdx = 0;
    this->RoiIteratorDirection = 1;
}

void MultiSpriteGameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Rois[this->RoiIdx]->RegionScale, this->Rois[this->RoiIdx]->OffsetScale, this->Size, this->Rotation, this->Color, this->IsRightToLeft);
}

void MultiSpriteGameObject::Draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition)
{
    renderer.DrawSprite(this->Sprite, this->Position + offsetPosition, this->Rois[this->RoiIdx]->RegionScale, this->Rois[this->RoiIdx]->OffsetScale, this->Size, this->Rotation, this->Color, this->IsRightToLeft);
}
