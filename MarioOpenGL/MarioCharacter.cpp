#include "MarioCharacter.h"
#include "Util.h"

MarioCharacter::MarioCharacter(int teamNo, int status, int stage, MultiSpriteGameObject *gameObject)
{
    this->TeamNo = teamNo;
    this->Status = status;
    this->Stage = stage;
    this->GameObject = gameObject;
}

void AssignInitProperties(int stage, int status, glm::vec2 &offset, glm::vec2 &delta, glm::vec2 &size, int &numRois);

void MarioCharacter::CreateRegionOfInterestList(int levelIndex)
{
    glm::vec2 offset = glm::vec2(0.0f, 0.0f);
    glm::vec2 delta = glm::vec2(0.0f, 0.0f);
    glm::vec2 size = glm::vec2(0.0f, 0.0f);
    int numRois = 0;

    for (int status = Util::MARIO_STAND; status < Util::MARIO_DIE; status++)
    {
        AssignInitProperties(this->Stage, status, offset, delta, size, numRois);
        std::vector<RegionOfInterest*> tmpRois = GetStatusRois(offset, delta, size, numRois);
        this->RoisMap[status] = tmpRois;
    }

    this->GameObject->Rois = this->RoisMap[this->Status];
}

void AssignInitProperties(int stage, int status, glm::vec2 &offset, glm::vec2 &delta, glm::vec2 &size, int &numRois)
{
    switch (stage)
    {
    case Util::SMALL_STAGE:
        size = glm::vec2(16.0f, 16.0f);
        switch (status)
        {
        case Util::MARIO_STAND:
            offset = glm::vec2(0.0f, 8.0f);
            delta = glm::vec2(0.0f, 0.0f);
            numRois = 1;
            break;
        case Util::MARIO_WALK:
            offset = glm::vec2(20.0f, 8.0f);
            delta = glm::vec2(2.0f, 0.0f);
            numRois = 3;
            break;
        case Util::MARIO_ABOUT_RUN:
            offset = glm::vec2(76.0f, 8.0f);
            delta = glm::vec2(0.0f, 0.0f);
            numRois = 1;
            break;
        case Util::MARIO_JUMP:
            offset = glm::vec2(96.0f, 8.0f);
            delta = glm::vec2(0.0f, 0.0f);
            numRois = 1;
            break;
        case Util::MARIO_DIE:
            offset = glm::vec2(116.0f, 8.0f);
            delta = glm::vec2(0.0f, 0.0f);
            numRois = 1;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }
}

std::vector<RegionOfInterest*> MarioCharacter::GetStatusRois(glm::vec2 &offset, glm::vec2 &delta, const glm::vec2 &size, int numRois)
{
    std::vector<RegionOfInterest*> list;
    glm::vec2 regionScale = glm::vec2(size.x / this->GameObject->Sprite.Width, size.y / this->GameObject->Sprite.Height);
    for (int i = 0; i < numRois; i++)
    {
        glm::vec2 tmpOffset = glm::vec2(offset.x / this->GameObject->Sprite.Width, offset.y / this->GameObject->Sprite.Height);
        RegionOfInterest* roi = new RegionOfInterest(regionScale, tmpOffset, size);
        list.push_back(roi);
        offset.x += size.x + delta.x;
    }

    return list;
}

void MarioCharacter::SetCurrentVisual()
{
    int numRois = this->GameObject->Rois.size() - 1;
    if (numRois == 0)
    {
        return;
    }

    this->GameObject->RoiDir = (this->GameObject->RoiIdx == numRois && this->GameObject->RoiDir > 0) ||
                               (this->GameObject->RoiIdx == 0 && this->GameObject->RoiDir < 0) ?
                               -this->GameObject->RoiDir : this->GameObject->RoiDir;
    this->GameObject->RoiIdx += this->GameObject->RoiDir;
}