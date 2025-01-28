#include "Grid.h"
#include "ncurses.h"

Grid::Grid() {
    this -> GRID_HEIGHT = 20;
    this -> GRID_WIDTH = 20;
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

bool Grid::isCollision(Tetramino& tetramino) {
    return false;
}

void Grid::placeTetramino(Tetramino& tetramino) {}
