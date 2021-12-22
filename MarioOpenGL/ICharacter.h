#ifndef I_CHARACTER
#define I_CHARACTER

#include "GameObject.h"

class ICharacter
{
protected:
    int TeamNo;
    // đứng, ngồi, chạy, đi, bắn, nhảy...
    int Status;
    // * ví dụ mario: 
    // stage1: small size
    // stage2 : medium size, bigger than small
    // stage3 : medium size, can shoot
    // stage4 : special state : walk fast(at run speed), last a few seconds, after special effect -> return to stage3
    int Stage;
    // Quyết định sẽ load file tile nào để render character
    //int CurrentLevel;
    MultiSpriteGameObject* GameObject;

public:
    ~ICharacter();
    /*virtual void UpdatePosition();
    virtual void UpdateStage(int inStage);*/
    virtual void Draw(SpriteRenderer &renderer);
    virtual void Draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition);
};

#endif // !I_CHARACTER
