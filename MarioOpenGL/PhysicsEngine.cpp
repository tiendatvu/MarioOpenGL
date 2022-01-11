#include "PhysicsEngine.h"
#include "Util.h"

void PhysicsEngine::Update(ICharacter *character, GameLevel *gameLevel)
{
    // Từ position của character => chia cho unit size của tile trong GameLevel
    // => giá trị tương đối của position của character on the screen
    // HEAD: - Check trùng với Breakable bricks && Stage == BIG MARIO
    // BODY: - Trùng với brick... -> không thể di chuyển
    //       - Trùng với Character team khác -> check stage != SPECIAL -> DIE
    
    glm::vec2 characterPos = character->Position - gameLevel->CameraPos;
    glm::vec2 tlTilePos = characterPos / gameLevel->UnitSize;
    glm::vec2 bTilePos = (characterPos + glm::vec2(0, character->Size.y)) / gameLevel->UnitSize;
    glm::vec2 rTilePos = (characterPos + glm::vec2(character->Size.x, 0)) / gameLevel->UnitSize;
    tlTilePos = glm::vec2(floor(tlTilePos.x), floor(tlTilePos.y));
    bTilePos  = glm::vec2(floor(bTilePos.x), floor(bTilePos.y));
    rTilePos  = glm::vec2(floor(rTilePos.x), floor(rTilePos.y));

    int tlIdx = gameLevel->TileNum.x * tlTilePos.y + tlTilePos.x;
    int bIdx = gameLevel->TileNum.x * bTilePos.y + bTilePos.x;
    int rIdx = gameLevel->TileNum.x * rTilePos.y + rTilePos.x;
    char tlChar = gameLevel->DotData[tlIdx];
    char bChar = gameLevel->DotData[bIdx];
    char rChar = gameLevel->DotData[rIdx];

    if (character->IsRightToLeft)
    {
        switch (character->Status)
        {
        case Util::MARIO_JUMP:
            if (tlChar != '.')
            {
                character->Position = glm::vec2((tlTilePos.x + 1) * gameLevel->UnitSize.x + gameLevel->CameraPos.x, character->Position.y);
            }
            if (bChar != '.' && character->IsOnGround == false)
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
                character->UpdatePropertiesByStatus(Util::MARIO_STAND);
            }
            break;
        case Util::MARIO_WALK:
            if (tlChar != '.')
            {
                character->Position = glm::vec2((tlTilePos.x + 1) * gameLevel->UnitSize.x, character->Position.y) + gameLevel->CameraPos.x;
            }
            if (bChar != '.')
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
            }
            else
            {
                character->UpdatePropertiesByStatus(Util::MARIO_FALL);
            }
            break;
        case Util::MARIO_STAND:
            if (bChar == '.')
            {
                character->UpdatePropertiesByStatus(Util::MARIO_FALL);
            }
            break;
        case Util::MARIO_FALL:
            if (bChar != '.')
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
                character->UpdatePropertiesByStatus(Util::MARIO_STAND);
            }
            break;
        default:
            break;
        }
    }
    else
    {
        switch (character->Status)
        {
        case Util::MARIO_JUMP:
            if (rChar != '.')
            {
                character->Position = glm::vec2(rTilePos.x * gameLevel->UnitSize.x - character->Size.x, character->Position.y) + gameLevel->CameraPos;
            }
            if (bChar != '.' && character->IsOnGround == false)
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
                character->UpdatePropertiesByStatus(Util::MARIO_STAND);
            }
            break;
        case Util::MARIO_WALK:
            if (rChar != '.')
            {
                character->Position = glm::vec2(rTilePos.x * gameLevel->UnitSize.x - character->Size.x, character->Position.y) + gameLevel->CameraPos;
            }
            if (bChar != '.')
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
            }
            break;
        case Util::MARIO_STAND:
            if (bChar == '.')
            {
                character->UpdatePropertiesByStatus(Util::MARIO_FALL);
            }
            break;
        case Util::MARIO_FALL:
            if (bChar != '.')
            {
                character->Position = glm::vec2(character->Position.x, bTilePos.y * gameLevel->UnitSize.y - character->Size.y);
                character->UpdatePropertiesByStatus(Util::MARIO_STAND);
            }
            break;
        default:
            break;
        }
    }
}