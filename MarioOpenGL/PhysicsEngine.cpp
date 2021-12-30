#include "PhysicsEngine.h"

void PhysicsEngine::UpdateCharacter(ICharacter *character, GameLevel &gameLevel)
{
    // Từ position của character => chia cho unit size của tile trong GameLevel
    // => giá trị tương đối của position của character on the screen
    // HEAD: - Check trùng với Breakable bricks && Stage == BIG MARIO
    // BODY: - Trùng với brick... -> không thể di chuyển
    //       - Trùng với Character team khác -> check stage != SPECIAL -> DIE
}