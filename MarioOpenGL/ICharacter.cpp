#include "ICharacter.h"


ICharacter::~ICharacter()
{
    delete this->GameObject;
}

//void ICharacter::UpdatePosition()
//{
//    // có thể sẽ dùng các hàm gọi walk, jump
//}
//
//void ICharacter::UpdateStage(int inStage)
//{
//    
//}

void ICharacter::Draw(SpriteRenderer &renderer)
{
    this->GameObject->Draw(renderer);
}

void ICharacter::Draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition)
{
    this->GameObject->Draw(renderer, offsetPosition);
}