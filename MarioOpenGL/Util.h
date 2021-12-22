#ifndef Util
class Util
{
public:
    static constexpr unsigned int TILE_SCALE = 3;
    static constexpr unsigned int CAMERA_WIDTH = 256;
    static constexpr unsigned int CAMERA_HEIGHT = 240;
    static constexpr int MARIO_NORMAL_SPEED = 10;

    static enum PlayerTeam
    {
        TEAM_0 = 0,
        TEAM_1 = 1
    };

    static enum CharacterStatus
    {
        MARIO_STAND = 0,
        MARIO_WALK,
        MARIO_JUMP,
        MARIO_RUN
    };

    static enum CharacterStage
    {
        MARIO_SMALL_STAGE = 0,
        MARIO_MEDIUM_STAGE,
        MARIO_MEDIUM_SHOOT_STAGE
    };

    static enum GameLevel
    {
        OverWorld = 0,
        UnderWorld = 1
    };

};
#endif // !Util