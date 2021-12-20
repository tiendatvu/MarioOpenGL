#include "ICharacter.h"

void ICharacter::updatePosition()
{
    // có thể sẽ dùng các hàm gọi walk, jump
}

void ICharacter::updateStage(int inStage)
{
    
}

void ICharacter::draw(SpriteRenderer &renderer)
{
    this->gameObject->Draw(renderer);
}

void ICharacter::draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition)
{
    this->gameObject->Draw(renderer, offsetPosition);
}