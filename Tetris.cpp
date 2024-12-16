//
// Created by Michele Pittori on 15/12/2024.
//

#include "Tetris.h"
#include <iostream>
#include <ncurses/curses.h>

const int GRID_HEIGHT = 20; // Altezza della griglia
const int GRID_WIDTH = 20;  // Larghezza della griglia

// Funzione per disegnare la griglia con bordi
void draw_grid(int start_y, int start_x) {
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

using namespace std;
int main() {
  // Inizializza ncurses
  initscr();              // Inizializza lo schermo
  noecho();               // Non mostra l'input dell'utente
  curs_set(0);            // Nasconde il cursore
  keypad(stdscr, TRUE);   // Abilita i tasti speciali

  // Disegna la griglia al centro dello schermo
  int start_y = (LINES - GRID_HEIGHT) / 2; // Calcola posizione verticale centrale
  int start_x = (COLS - (GRID_WIDTH + 2)) / 2; // Calcola posizione orizzontale centrale
  draw_grid(start_y, start_x);

  // Attendi che l'utente prema un tasto prima di uscire
  getch();
  endwin(); // Termina ncurses

  return 0;
}

