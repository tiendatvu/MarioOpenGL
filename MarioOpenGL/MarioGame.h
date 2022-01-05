#ifndef MARIO_GAME_H
#define MARIO_GAME_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "MarioCharacterFactory.h"
#include "WalkCommand.h"
#include "JumpCommand.h"
#include "PhysicsEngine.h"

// Represent the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE
};

// Game holds all game-releated state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and managebility.
class MarioGame
{
public:
    GameState State;
    bool Keys[1024];
    bool IsPressed;
    unsigned int Width, Height;
    std::vector<GameLevel*> Levels;
    unsigned int           LevelIdx;
    // Contructor/Destructor
    MarioGame(unsigned int width, unsigned int height);
    ~MarioGame();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // Game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    // Player
    ICharacter *Mario;

    // Commands
    ICommand *WalkingCommand;
    ICommand *JumpingCommand;

    // Physics engine
    PhysicsEngine *GamePhysicsEngine;

private:
    SpriteRenderer *GameRenderer;
};
#endif // !MARIO_GAME_H
