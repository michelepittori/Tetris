#include "Grid.h"
#include "ncurses.h"

Grid::Grid() {
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = 0;
        }
    }
}

// Funzione per disegnare la griglia con bordi
void Grid::draw_grid(int start_y, int start_x){
    // Disegna i bordi esterni
    for (int i = 0; i <= GRID_HEIGHT + 1; ++i) {
        for (int j = 0; j <= GRID_WIDTH + 1; ++j) {
            int y = start_y + i;
            int x = start_x + j;

            // Disegna i bordi
            if (i == 0 && j == 0) {
                mvaddch(y, x, ACS_ULCORNER); // Angolo superiore sinistro
            } else if (i == 0 && j == GRID_WIDTH + 1) {
                mvaddch(y, x, ACS_URCORNER); // Angolo superiore destro
            } else if (i == GRID_HEIGHT + 1 && j == 0) {
                mvaddch(y, x, ACS_LLCORNER); // Angolo inferiore sinistro
            } else if (i == GRID_HEIGHT + 1 && j == GRID_WIDTH + 1) {
                mvaddch(y, x, ACS_LRCORNER); // Angolo inferiore destro
            } else if (i == 0 || i == GRID_HEIGHT + 1) {
                mvaddch(y, x, ACS_HLINE); // Linea orizzontale
            } else if (j == 0 || j == GRID_WIDTH + 1) {
                mvaddch(y, x, ACS_VLINE); // Linea verticale
            } else {
                mvaddch(y, x, ' '); // Spazio vuoto
            }
        }
    }
}

bool Grid::isCollision(Tetramino& tetramino, int new_x, int new_y) {
     for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (tetramino.shape[i][j] == 1) {
                    int grid_x = new_x + j;
                    int grid_y = new_y + i;

                    // Controlla i bordi della griglia solo se la cella è realmente parte del tetramino
                    if (grid_x < 0 || grid_x >= GRID_WIDTH) {
                        return true; // Collisione ai lati, ignora il movimento
                    }

                    if (grid_y >= GRID_HEIGHT || (grid_y >= 0 && grid[grid_y][grid_x] != 0)) {
                        placeTetramino(tetramino,grid_x,grid_y);
                        return true; // Collisione con il basso o con un blocco esistente
                    }
                }
            }
        }
        return false;
}

void Grid::placeTetramino(Tetramino& tetramino, int x, int y) {
    for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (tetramino.shape[i][j] == 1) {
                    int grid_x = x + j;
                    int grid_y = y + i;
                    if (grid_y >= 0 && grid_y < GRID_HEIGHT && grid_x >= 0 && grid_x < GRID_WIDTH) {
                        grid[grid_y][grid_x] = 1; // Salva il tetramino nella griglia
                    }
                }
            }
     }
}
