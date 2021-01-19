#include <stdio.h>
#include "sdlsystem.h"
#include "constants.h"
#include "GameManager.h"


int main(int argc, char* args[]) {
    GameManager gameManager;

    gameManager.init();
    gameManager.startGame();

    return 0;
}