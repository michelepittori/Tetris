#include "ncurses.h"
#include "Tetramino.h"
#include <iostream>


Tetramino :: Tetramino(int startX, int startY, char type, bool isMirrored) {
    this-> x = startX;
    this-> y = startY;
    this-> type = type;
    initializeShape(isMirrored);
}

Tetramino Tetramino::generate(){
    char type[5] = {'I','L','O','T','Z'};
    int randomType = rand() % 5;
    bool isMirrored = rand() % 2;

    return Tetramino (5,1,type[randomType],isMirrored);
}
void Tetramino::initializeShape(bool isMirrored){
    //inizializza la shape a 0
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            shape[i][j] = 0;
        }
    }
    // crea le varie forme a seconda del tipo
    if(type == 'I'){
       for(int i = 0; i < 4; i = i + 1){
           shape[i][0] = 1;
       }
    }
    else if(type == 'O'){
        shape[1][1] = 1;
        shape[1][2] = 1;
        shape[2][1] = 1;
        shape[2][2] = 1;
    }
    else if(type == 'L'){
        if(isMirrored){
            shape[1][1] = 1;
            shape[2][1] = 1;
            shape[3][1] = 1;
            shape[3][2] = 1;
        }
        else{
            shape[1][2] = 1;
            shape[2][2] = 1;
            shape[3][1] = 1;
            shape[3][2] = 1;
        }

    }
    else if(type == 'T'){
        shape[3][0] = 1;
        shape[3][1] = 1;
        shape[3][2] = 1;
        shape[2][1] = 1;
    }
    else if(type == 'Z'){
        if(isMirrored){
            shape[2][1] = 1;
            shape[2][2] = 1;
            shape[3][2] = 1;
            shape[3][3] = 1;
        }
        else{
            shape[2][1] = 1;
            shape[2][2] = 1;
            shape[3][0] = 1;
            shape[3][1] = 1;
        }
    }
}

 int Tetramino::getX()const {
    return x;
}

int Tetramino::getY()const {
    return y;
}

int Tetramino::getColor(char type) {
    if(type == 'I') return 2;
    else if(type == 'L') return 3;
    else if(type == 'O') return 4;
    else if(type == 'T') return 5;
    else return 6;
}

void Tetramino::move(int dx, int dy){
    x = x + dx;
    y = y + dy;
}

void Tetramino::rotateClockwise() {
    //matrice temporanea per non sovrascrivere
    int temp[4][4];
    //il valore nella riga i diventa il valore nella colonna j ma invertito
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            temp[j][3 - i] = shape[i][j];
        }
    }
    //ricopio nella matrice shape
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            shape[i][j] = temp[i][j];
        }
    }
}

void Tetramino::rotateCounterClockwise() {
    int temp[4][4];
    //stesso concetto della rotazione oraria ma applicato alle righe e non alle colonne
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            temp[3 - j][i] = shape[i][j];
        }
    }
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            shape[i][j] = temp[i][j];
        }
    }
}

void Tetramino::draw() {
    int color = getColor(type);
    attron(COLOR_PAIR(color));
    for(int i = 0; i < 4; i = i + 1){
        for(int j = 0; j < 4; j = j + 1){
            if(shape[i][j] == 1){
                mvprintw(y + i,(x + j) * 2,"  ");
            }
        }
    }
    attroff(COLOR_PAIR(color));
}

const int (&Tetramino :: get_shape()const)[4][4]{
    return shape;
}

char Tetramino::getType()const{
    return type;
}
