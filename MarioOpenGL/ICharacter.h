#ifndef I_CHARACTER_H
#define I_CHARACTER_H

#include "GameObject.h"
#include <map>

class ICharacter : public MultiSpriteGameObject
{
public:
    int TeamNo;
    // đứng, ngồi, chạy, đi, bắn, nhảy...
    int Status;
    // * ví dụ mario: 
    // stage1: small size
    // stage2: medium size, bigger than small
    // stage3: medium size, can shoot
    // stage4: special state : walk fast(at run speed), last a few seconds, after special effect -> return to stage3
    int Stage;
    // Lưu trữ list của region of interest cho các stage và các status khác nhau của character
    std::map<int, std::vector<RegionOfInterest*>> RoisMap;
    // 
    bool IsOnGround;

public:
    ~ICharacter();
    /*virtual void UpdatePosition();
    virtual void UpdateStage(int inStage);*/
    virtual void CreateRegionOfInterestList(int levelIndex) = 0;
    // base on Status and Stage -> Assign the current list of Rois(regions of interest) for the character
    virtual void SetCurrentVisual() = 0;
    virtual void UpdatePropertiesByStatus(int status) = 0;

protected:
    virtual std::vector<RegionOfInterest*> GetStatusRois(glm::vec2 &offset, glm::vec2 &delta, const glm::vec2 &size, int numRois) = 0;
};

#endif // !I_CHARACTER_H
