#ifndef I_CHARACTER
#define I_CHARACTER

#include "GameObject.h"
#include "Util.h"

class ICharacter
{
private:
    int teamNo;
    int status; // đứng, ngồi, chạy, đi, bắn, nhảy...
    int stage; // world one, worl two ứng với từng nhân vật
    MultiSpriteGameObject* gameObject;

public:
    virtual void updatePosition();
    virtual void updateStage(int inStage);
    virtual void draw(SpriteRenderer &renderer);
    virtual void draw(SpriteRenderer &renderer, glm::vec2 &offsetPosition);
};

#endif // !I_CHARACTER
