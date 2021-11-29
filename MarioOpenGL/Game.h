#ifndef GAME_H
#define GAME_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

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
class Game
{
public:
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    // Contructor/Destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // Game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};
#endif // !GAME_H
