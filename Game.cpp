#include "iostream"
#include <fstream>
#include "Game.h"
using namespace std;



Game ::Game() : currentTetramino(3,0,'I', false),
                nextTetramino(3,1,'I',false){
}


int Game::updateScore(int completedLines) {
    //completedLInes sarebbe un valore da ritornare in una funzione di pulizia delle righe complete
    int score = completedLines * 100;
    int bonus = 0;
    for (int i = 0; i < completedLines; i = i + 1) {
        bonus = bonus + (i * 100); //se i = 1 bonus = 100, se i = 2 bonus = 200 + 100 ecc..
    }
    score += bonus;
    totalScore = totalScore + score;
    return totalScore;
}

void Game::saveScore(const string &fileName, string username, int score) {
    ofstream outputFile(fileName, ios::app);
    if (!outputFile) {
        cout << "Errore nell'apertura del file!" << endl;
        return;
    }
    outputFile << username << " " << score << endl;
    outputFile.close();
    cout << "Punteggio salvato con successo!" << endl;
}

void Game::viewBoard(const std::string &fileName) {
    //non ordina i punteggi
    ifstream inputFile;
    inputFile.open(fileName);
    string line;

    while(!inputFile.eof()){
        getline(inputFile,line);
        cout << line << endl;
    }
    inputFile.close();
}


void testBoard(){
    Game game;
    int score = game.updateScore(3);
    string username;
    cout<<"Inserisci il tuo nome"<<endl;
    cin>>username;
    game.saveScore("Classifica.txt",username, score);
    game.viewBoard("Classifica.txt");

}
int main() {

testBoard();

    return 0;
