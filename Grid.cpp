#include "Grid.h"
#include "ncurses.h"

Grid::Grid() {
    this -> GRID_HEIGHT = 20;
    this-> GRID_WIDTH = 10;
    initialize();
}

void Grid::initialize() {
    for (int i = 0; i < GRID_HEIGHT + 2; i = i + 1) {
        for (int j = 0; j < GRID_WIDTH + 2; j = j + 1) {
            if (i == 0 || i == GRID_HEIGHT + 1 || j == 0 || j == GRID_WIDTH + 1) {
                grid[i][j] = 1; // Bordi
            } else {
                grid[i][j] = 0; // Interno
            }
        }
    }
}

void Grid::draw_grid() {
    for (int i = 0; i < GRID_HEIGHT + 2; i = i + 1) {
        for (int j = 0; j < GRID_WIDTH + 2; j = j + 1) {
            if (grid[i][j] == 1) {
                mvaddch(i, j * 2, ACS_CKBOARD);
                mvaddch(i, j * 2 + 1, ACS_CKBOARD);
            } else if ( grid[i][j] != 0){
                int color = grid[i][j];
                attron(COLOR_PAIR(color));
                mvaddch(i, j * 2, ACS_CKBOARD);
                mvaddch(i, j * 2 + 1, ACS_CKBOARD);
                attroff(COLOR_PAIR(color));
            } else {
                mvaddch(i, j * 2, ' ');
                mvaddch(i, j * 2 + 1, ' ');
            }
        }
    }
}

bool Grid::isCollision( const Tetramino &tetramino) {
    const int (&shape)[4][4] = tetramino.getShape();
    for (int i = 0; i < 4; i = i + 1) {
        for (int j = 0; j < 4; j = j + 1) {
            if (shape[i][j] == 1) {
                int newX = tetramino.getX() + j;
                int newY = tetramino.getY() + i;
                if(grid[newY][newX] != 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grid::placeTetramino(const Tetramino &tetramino) {
    const int (&shape)[4][4] = tetramino.getShape();
    int color = tetramino.getColor(tetramino.getType());
    for (int i = 0; i < 4; i = i + 1) {
        for (int j = 0; j < 4; j = j + 1) {
            if (shape[i][j] == 1) {
                int newX = tetramino.getX() + j;
                int newY = tetramino.getY() + i;
                if (newX >= 1 && newX <= GRID_WIDTH && newY >= 1 && newY <= GRID_HEIGHT) {
                    grid[newY][newX] = color;
                }
            }
        }
    }
    return true;
}

int Grid::clearLines() {
    int clearedLines = 0;
    for (int i = 1; i <= GRID_HEIGHT; i = i + 1) {
        bool isComplete = true;
        for (int j = 1; j <= GRID_WIDTH; j = j + 1) {
            if (grid[i][j] == 0) {
                isComplete = false;

            }
        }
        if (isComplete) {
            clearedLines = clearedLines + 1;
            // Sposta tutte le righe sopra questa verso il basso
            for (int k = i; k > 1; k = k - 1) {
                for (int j = 1; j <= GRID_WIDTH; j = j + 1) {
                    grid[k][j] = grid[k - 1][j];
                }
            }
            // Pulisci la riga superiore
            for (int j = 1; j <= GRID_WIDTH; j = j + 1) {
                grid[1][j] = 0;
            }
            i = i - 1;
        }
    }
    return clearedLines;
}
