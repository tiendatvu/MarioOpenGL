#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
    static constexpr unsigned int TILE_SCALE = 3;
    static constexpr unsigned int CAMERA_WIDTH = 256;
    static constexpr unsigned int CAMERA_HEIGHT = 240;
    static constexpr float MARIO_WALK_SPEED = 0.05;
    static constexpr float MARIO_RUN_SPEED = 15;

    static const std::string TEXTURE_PLAYER;
    static const std::string TEXTURE_TILE_SET;
    static const std::string TEXTURE_ITEM_AND_BRICK;
    static const std::string SHADER_SPRITE;

    static enum PlayerTeam
    {
        TEAM_0 = 0,
        TEAM_1 = 1
    };

    static enum CharacterStatus
    {
        MARIO_STAND = 0,
        MARIO_WALK,
        MARIO_ABOUT_RUN,
        MARIO_JUMP,
        MARIO_SIT,
        MARIO_FIRE,
        MARIO_DIE
    };

    /// - Nếu gặp phải enemy/đạn thường
    ///   -> NextStage = Stage - 1 -> check NextStage < 0 then CharacterStatus = die
    /// - Nếu ăn được nấm thường
    ///   -> NextStage = Stage + 1 -> check NextStage >= MARIO_FIRE_STAGE then Stage = MARIO_FIRE_STAGE and not change anything
    ///                                     NextStage < MARIO_FIRE_STAGE  then switch between current stage and next stage
    /// - Nếu gặp phải enemy/đạn đặc biệt -> CharacterStatus = die
    /// - Nếu ăn được nấm đặc biệt -> NextStage = MARIO_FIRE_STAGE (switch between current stage and MARIO_FIRE_STAGE)
    static enum MarioLuigiStage
    {
        SMALL_STAGE = 0,
        BIG_STAGE,
        FIRE_STAGE,
        GROW_SHRINK_STAGE
    };

    static enum GameLevel
    {
        OverWorld = 0,
        UnderWorld = 1
    };
};

//const std::string Util::TEXTURE_PLAYER = "Player";
//const std::string Util::TEXTURE_TILE_SET = "TileSet";
//const std::string Util::TEXTURE_ITEM_AND_BRICK = "ItemAndBrick";
//const std::string Util::SHADER_SPRITE = "sprite";

#endif // !UTIL_H