//
// Created by Denis on 09.01.2022.
//

#ifndef LIFE_RPG_GAME_H
#define LIFE_RPG_GAME_H


class GameData {
public:
    bool loaded = false;
    int health;
    int hunger;
    int knowledge;
    int xpBoost;
    int money;

    int playerClass;
    bool dead = false;
};
extern GameData globalGameData;

void startNewDay();
void startGame();
void startNewGame();
void popupWelcomeAndAwait();
void startMainMenu();

#endif //LIFE_RPG_GAME_H
