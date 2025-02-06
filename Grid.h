#ifndef ILTETRIS_GRID_H
#define ILTETRIS_GRID_H
#include "Tetramino.h"

class Grid {
protected:
    int GRID_HEIGHT;
    int GRID_WIDTH;

public:
    Grid();
    int grid[22][12];
    void initialize();
    void draw_grid();
    bool isCollision(const Tetramino &tetramino);
    bool placeTetramino(const Tetramino &tetramino);
    int clearLines();
};

#endif //ILTETRIS_GRID_H
