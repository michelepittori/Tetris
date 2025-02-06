#ifndef ILTETRIS_TETRAMINO_H
#define ILTETRIS_TETRAMINO_H

class Tetramino {
protected:
    char type;                 // Tipo del Tetramino (I,L,O,T,Z)
    int x;
    int y;
    bool isMirrored;

public:
    Tetramino();
    int shape[4][4];
    int getX() const;
    int getY() const;
    void move(int dx, int dy);
    void moveRight(Tetramino& tetramino);
    void moveLeft(Tetramino& tetramino);
    void moveDown(Tetramino &tetramino);
    void rotateClockwise();
    void rotateCounterClockwise();
    void initializeShape(bool isMirrored);
    void draw();
    static int getColor(char type);
    const int(&getShape()const)[4][4];
    char getType() const;
};

#endif //ILTETRIS_TETRAMINO_H
