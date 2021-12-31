#include "ICharacter.h"
#include "Util.h"

ICharacter::~ICharacter()
{
}

void ICharacter::UpdateRoisByStatus(int status)
{
    // SMALL MARIO không thể FIRE
    //if (this->Stage == Util::SMALL_STAGE && status == Util::MARIO_FIRE)
    //{
    //    return;
    //}

    this->RoiIdx = 0;
    this->Status = status;
    this->Rois = this->RoisMap[this->Status];
}

glm::vec2 ICharacter::GetCurrentTilePostion(glm::vec2 tileUnitSize)
{
    glm::vec2 tmp = this->Position / tileUnitSize;
    return tmp;
}