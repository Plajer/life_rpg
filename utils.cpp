#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "utils.h"
#include "game.h"

using namespace std;

int getRandom(int start, int end) {
    random_device rd;
    mt19937 generator(rd());
    return uniform_int_distribution<int>(start, end)(generator);
}

void typewriter(string text, int interval) {
    int i = 0;
    while(text[i] != '\0') {
        cout << text[i];
        Sleep(interval);
        i++;
    }
}

void typewriter(string text) {
    typewriter(text, 100);
}

void loadData() {
    ifstream input("rpg.data");
    if(input.fail()) {
        return;
    }
    int data;
    int i = 0;
    while(input >> data) {
        switch(i) {
            case 0:
                globalGameData.health = data;
                break;
            case 1:
                globalGameData.hunger = data;
                break;
            case 2:
                globalGameData.knowledge = data;
                break;
            case 3:
                globalGameData.xpBoost = data;
                break;
            case 4:
                globalGameData.money = data;
                break;
            case 5:
                globalGameData.playerClass = data;
                break;
            case 6:
                globalGameData.dead = (bool) data;
                break;
        }
        i++;
    }
    globalGameData.loaded = true;
}

void saveData() {
    ofstream ofs;
    ofs.open("rpg.data", ofstream::out | ofstream::trunc);
    ofs << globalGameData.health << endl;
    ofs << globalGameData.hunger << endl;
    ofs << globalGameData.knowledge << endl;
    ofs << globalGameData.xpBoost << endl;
    ofs << globalGameData.money << endl;
    ofs << globalGameData.playerClass << endl;
    ofs << globalGameData.dead << endl;
    ofs.close();
}

string playerClassToString() {
    switch(globalGameData.playerClass) {
        case 0:
            return "Uczen";
        case 1:
            return "Dobry Uczen";
        case 2:
            return "Szybki Uczen";
    }
    return "err";
}