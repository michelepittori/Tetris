#ifndef ILTETRIS_GAME_H
#define ILTETRIS_GAME_H
#include "string"
#include "Grid.h"
using namespace std;

class Game {
protected:
    int interval;
    int score;
    bool gameover;
    int clearedLines;
    Grid grid;
    Tetramino currentTetramino;
    Tetramino nextTetramino;

public:
    Game();
    int updateScore(int completedLines);
    void saveScore(const string &fileName,string username, int score);
    void viewBoard(const string &fileName);
    void init();
    void processInput();
    void handleCollision();
    void render();
    void run();
    void update();
    void end();
    void menu();
    void reset();
};

#endif
