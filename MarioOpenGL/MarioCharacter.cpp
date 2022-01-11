#include "MarioCharacter.h"
#include "Util.h"
#include "ResourceManager.h"

const glm::vec2 MarioCharacter::WALK_SPEED = glm::vec2(8.0f, 8.0f);
const glm::vec2 MarioCharacter::JUMP_SPEED = glm::vec2(5.0f, 12.0f);

MarioCharacter::MarioCharacter(int teamNo, int status, int stage, glm::vec2 pos, glm::vec2 size, std::string spriteName, glm::vec3 color, glm::vec2 velocity)
{
    this->RoiIdx = 0;
    this->RoiIteratorDirection = 1;
    this->Position = pos;
    this->Size = size;
    this->Sprite = ResourceManager::GetTexture(spriteName);
    this->Color = color;
    this->Velocity = velocity;
    this->TeamNo = teamNo;
    this->Status = status;
    this->Stage = stage;
    this->IsRightToLeft = false;
    this->IsOnGround = false;
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

    this->Rois = this->RoisMap[this->Status];
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
        case Util::MARIO_FALL:
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
    glm::vec2 regionScale = glm::vec2(size.x / this->Sprite.Width, size.y / this->Sprite.Height);
    for (int i = 0; i < numRois; i++)
    {
        glm::vec2 tmpOffset = glm::vec2(offset.x / this->Sprite.Width, offset.y / this->Sprite.Height);
        RegionOfInterest* roi = new RegionOfInterest(regionScale, tmpOffset, size);
        list.push_back(roi);
        offset.x += size.x + delta.x;
    }

    return list;
}

void MarioCharacter::SetCurrentVisual()
{
    int numRois = this->Rois.size() - 1;
    if (numRois == 0)
    {
        return;
    }

    this->RoiIteratorDirection = (this->RoiIdx == numRois && this->RoiIteratorDirection > 0) ||
                                 (this->RoiIdx == 0 && this->RoiIteratorDirection < 0) ?
                                 -this->RoiIteratorDirection : this->RoiIteratorDirection;
    this->RoiIdx += this->RoiIteratorDirection;
}

void MarioCharacter::UpdatePropertiesByStatus(int status)
{
    // SMALL MARIO không thể FIRE
    //if (this->Stage == Util::SMALL_STAGE && status == Util::MARIO_FIRE)
    //{
    //    return;
    //}

    this->RoiIdx = 0;
    this->Status = status;
    this->Rois = this->RoisMap[this->Status];
    this->IsOnGround = true;

    switch (status)
    {
    case Util::MARIO_STAND:
        this->Velocity = glm::vec2(0, 0);
        break;
    case Util::MARIO_WALK:
        this->Velocity = this->WALK_SPEED;
        break;
    case Util::MARIO_ABOUT_RUN:
        this->Velocity = glm::vec2(0, 0);
        break;
    case Util::MARIO_JUMP:
        this->Velocity = this->JUMP_SPEED;
        break;
    case Util::MARIO_FALL:
        this->Velocity = glm::vec2(0, this->WALK_SPEED.y / 2);
        this->IsOnGround = false;
        break;
    case Util::MARIO_SIT:
        this->Velocity = glm::vec2(0, 0);
        break;
    case Util::MARIO_FIRE:
        this->Velocity = glm::vec2(0, 0);
        break;
    case Util::MARIO_DIE:
        this->Velocity = glm::vec2(0, 5);
        break;
    default:
        break;
    }
}