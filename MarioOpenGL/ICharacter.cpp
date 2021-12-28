#include "ICharacter.h"


ICharacter::~ICharacter()
{
}

void ICharacter::UpdateRoisByStatus(int status)
{
    this->Status = status;
    this->Rois = this->RoisMap[this->Status];
}