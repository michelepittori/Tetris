#include "iostream"
#include <fstream>
#include "Game.h"
#include "ncurses.h"
using namespace std;



Game::Game() {
    currentTetramino = Tetramino();
    nextTetramino = Tetramino();
    this->interval = 500;
    this->clearedLines = 0;
    this->score = 0;
    this->gameover = false;
    init();
}


void Game::init(){
    initscr();
    noecho();
    cbreak();
    start_color();
    keypad(stdscr,true);

    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);

    srand(time(0));
    timeout(interval);
}

int Game::updateScore(int completedLines){
    int bonus = 0;
    for (int i = 1; i <= completedLines; i = i + 1){
        bonus = bonus + (i * 100); //se i = 1 bonus = 100, se i = 2 bonus = 200 + 100 ecc..
    }
    score = score + bonus;
    return score;
}

void Game::saveScore(const string &fileName, string username, int score) {
    string usernames[100];
    int scores[100];
    int count = 0;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Errore nell'apertura del file!" << endl;
        return;
    }

    while (inputFile >> usernames[count] >> scores[count]) {
        count++;
        if (count >= 100) break;
    }
    inputFile.close();

    int i;
    for (i = 0; i < count; i++) {
        if (score > scores[i]) {
            break;
        }
    }

    if (count < 100) count++;
    for (int j = count - 1; j > i; j--) {
        usernames[j] = usernames[j - 1];
        scores[j] = scores[j - 1];
    }
    usernames[i] = username;
    scores[i] = score;

    ofstream outputFile(fileName);
    for (int k = 0; k < count; k++) {
        outputFile << usernames[k] << " " << scores[k] << endl;
    }
    outputFile.close();
}

void Game::viewBoard(const std::string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    string line;

    while(!inputFile.eof()){
        getline(inputFile,line);
        cout << line << endl;
    }
    inputFile.close();
}

void Game::processInput() {

    int ch = getch();
    if (ch == 'x'){
        gameover = true;
    }
    else if (ch == KEY_DOWN){
        currentTetramino.moveDown(currentTetramino);
        if(grid.isCollision(currentTetramino)){
            currentTetramino.move(0,-1);
        }
    }
    else if (ch == KEY_LEFT){
        currentTetramino.moveLeft(currentTetramino);
        if(grid.isCollision(currentTetramino)){
            currentTetramino.moveRight(currentTetramino);
        }
    }
    else if (ch == KEY_RIGHT){
        currentTetramino.moveRight(currentTetramino);
        if(grid.isCollision(currentTetramino)){
            currentTetramino.moveLeft(currentTetramino);
        }
    }
    else if (ch == 'q'){
        currentTetramino.rotateClockwise();
        if(grid.isCollision(currentTetramino)){
            currentTetramino.rotateCounterClockwise();
        }
    }
    else if (ch == 'w'){
        currentTetramino.rotateCounterClockwise();
        if(grid.isCollision(currentTetramino)){
            currentTetramino.rotateClockwise();
        }
    }
}

void Game::render(){
    clear();
    grid.draw_grid(0,0); //disegna la griglia
    currentTetramino.draw(); //disegna il tetramino
    //informazioni sul punteggio e linee pulite
    mvprintw(0,30, "Lines: %d", clearedLines);
    mvprintw(1,30, "Score: %d", score);

    refresh();
}

void Game::run() {
    while(!gameover){
        processInput();
        update();
        render();
        refresh();
    }
    end();
}


void Game::update() {
    currentTetramino.moveDown(currentTetramino);
    if(grid.isCollision(currentTetramino)){
        grid.placeTetramino(currentTetramino);
        currentTetramino = nextTetramino;
        nextTetramino = Tetramino();
    }
}

void Game::end(){
    timeout(-1);
    clear();
    mvprintw(10,10, "Game over! premi un tasto per continuare");
    refresh();
    getch();
    clear();
    echo();
    char username[51];
    memset(username,0,sizeof(username));
    clear();
    mvprintw(10,10, "Inserisci il tuo nome: ");
    refresh();
    getnstr(username,50);
    noecho();
    string user(username);
    endwin();
    saveScore("Classifica.txt",username,score);
    menu();
}

void Game::menu() {
    int highlight = 0;
    int choice = 0;
    int ch;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (true) {
        if (highlight == 0) attron(A_REVERSE);
        mvprintw(5, 10, "Gioca");
        attroff(A_REVERSE);

        if (highlight == 1) attron(A_REVERSE);
        mvprintw(7, 10, "Classifica");
        attroff(A_REVERSE);

        ch = getch();

        if (ch == KEY_UP)
            highlight = (highlight - 1 + 2) % 2;
        else if (ch == KEY_DOWN)
            highlight = (highlight + 1) % 2;
        else if (ch == 10) { // Invio
            choice = highlight;
            endwin();
            if(choice == 0){
                reset();
                run();
            }
            else if (choice == 1) {
                ifstream inputFile("Classifica.txt");
                if (!inputFile) {
                    cout << "Errore nell'apertura del file della classifica!" << endl;
                    return;
                }
                cout << "Classifica:" << endl;
                viewBoard("Classifica.txt");

            }
            return;
        }
    }
}


void Game::reset() {
    gameover = false;
    currentTetramino = Tetramino();
    nextTetramino = Tetramino();
    score = 0;
    clearedLines = 0;
    //griglia[][] = initialize();
    timeout(interval);
}
