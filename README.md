# Tetris

implementazione del tetris classico in c++ utilizzando la libreria ncurses.

# Autori

Ferrari Nicolo' (nicolo.ferrari@studio.unibo.it)
Pittori Michele ()

# Requisiti

Compilatore C++
Libreria ncurses
Sistema operativo Linux/macOS o Windows

# Compilazione

per compilare il gioco digitare: 
g++ main.cpp Game.cpp Tetramino.cpp Grid.cpp -o tetris -lncurses

#Esecuzione

per avviare il gioco digitare:
./tetris

# Comandi

Freccia destra: Muove il tetramino a destra
Freccia sinistra: Muove il tetramino a sinistra
Freccia in basso: Accelera la caduta del tetramino
Q: Ruota il tetramino in senso orario 
W: Ruota il tetramino in senso antiorario
X: Termina la partita
