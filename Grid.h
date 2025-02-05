#ifndef ILTETRIS_GRID_H
#define ILTETRIS_GRID_H
#include "Tetramino.h"

class Grid {
protected:
    int GRID_HEIGHT;
    int GRID_WIDTH;
    int grid[GRID_HEIGHT][GRID_WIDTH];

public:
    Grid();
    void draw_grid(int start_y, int start_x);
    bool isCollision(Tetramino& tetramino);
    void placeTetramino(Tetramino& tetramino);
};

#endif //ILTETRIS_GRID_H
