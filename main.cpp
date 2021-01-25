#include <stdio.h>
#include "sdlsystem.h"
#include "constants.h"
#include "GameManager.h"


int main(int argc, char* args[]) {
    GameManager gameManager;
    gameManager.init();
    gameManager.playGame();

    return 0;
}