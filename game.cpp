#include <Windows.h>
#include <iostream>
#include "game.h"
#include "utils.h"

using namespace std;

GameData globalGameData;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void handleRandomEvents() {
    if (getRandom(1, 100) <= 20 && globalGameData.health < 100) {
        typewriter("Bardzo dobrze sie wyspales i twoje HP wyleczylo sie o 1 dodatkowy punkt!", 15);
        cout << endl;
        globalGameData.health += 1;
    }
    if (getRandom(1, 100) <= 10) {
        typewriter("Kupiles zdrapke i niespodziewanie wygrales 5zl!", 15);
        cout << endl;
        globalGameData.money += 5;
    }
}

void startNewDay() {
    if(globalGameData.dead) {
        if(globalGameData.knowledge >= 300) {
            cout << "Skonczyles pierwszy semestr studiow, twoja gra sie skonczyla!" << endl;
            return;
        }
        cout << "Jestes martwy, mozesz sprobowac ponownie w nowym zyciu!" << endl;
        return;
    }
    handleRandomEvents();
    if (globalGameData.hunger >= 70) {
        if (globalGameData.hunger == 100) {
            typewriter("Aua, przez glod tracisz 1 punkt zdrowia.", 15);
            globalGameData.health -= 1;
        } else {
            typewriter("*Burczenie* Twoj brzuch informuje ze jest glodny, chyba powinienes cos zjesc.", 15);
        }
        cout << endl;
    }
    if (globalGameData.health <= 0) {
        typewriter("Czujesz sie... ");
        typewriter("martwy...", 200);
        cout << endl;
        typewriter("Twoja historia wlasnie sie skonczyla.");
        globalGameData.dead = true;
        saveData();
        return;
    }
    cout << "" << endl;
    cout << "Co planujesz dzisiaj zrobic?" << endl;
    cout << "0. Statystyki o mnie" << endl;
    cout << "1. Spij caly dzien ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "(+5 Glod, +1 HP)" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "2. Zamow pizze ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "(-15 Glod, -5 Pieniadze)" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "3. Ukradnij pieniadze z banku ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "(+15/+200 Pieniadze, -5/-100 HP)" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "4. Ucz sie ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "(+" + to_string(5 + globalGameData.xpBoost) + " Wiedza, +5 Glod)" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "5. Zdaj egzamin koncowy ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    if(globalGameData.knowledge >= 300) {
        cout << "(odblokowane)";
    } else {
        cout << "(wymaga 300 Wiedza)";
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << endl;
    while (true) {
        string num;
        cin >> num;
        if (num == "0") {
            cout << playerClassToString() << " (ty)" << endl;
            cout << "HP: " << globalGameData.health;
            if (globalGameData.health >= 90) {
                cout << " (zdrowy uczen!)";
            }
            cout << endl;
            cout << "Wiedza: " << globalGameData.knowledge << endl;
            cout << "Pieniadze: " << globalGameData.health << endl;
            cout << "Poziom glodu: ";
            if (globalGameData.hunger >= 90) {
                cout << "Bardzo glodny";
            } else if (globalGameData.hunger >= 70) {
                cout << "Dosyc glodny";
            } else if (globalGameData.hunger >= 50) {
                cout << "Glodny";
            } else if (globalGameData.hunger >= 30) {
                cout << "Nieco glodny";
            } else {
                cout << "Najedzony";
            }
            cout << endl;

            typewriter("To ja... Wszystko o mnie i moim stanie zdrowia. W miedzyczasie pojde spac...", 75);
            break;
        } else if (num == "1") {
            globalGameData.health += 1;
            if (globalGameData.health > 100) {
                globalGameData.health = 100;
            }
            globalGameData.hunger += 5;
            if (globalGameData.hunger > 100) {
                globalGameData.hunger = 100;
            }
            typewriter("Dobranoc...");
            break;
        } else if (num == "2") {
            if (globalGameData.money < 5) {
                cout << "Nie stac cie na to!" << endl;
                continue;
            }
            if (globalGameData.hunger < 15) {
                cout << "Nie czujesz potrzeby zeby to zrobic." << endl;
                continue;
            }
            globalGameData.money -= 5;
            globalGameData.hunger -= 15;
            typewriter("Mmm pizza... ");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            typewriter("(-15 Glod, -5 Pieniadze)", 15);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            cout << endl;
            typewriter("Teraz moge isc spac...", 15);
            break;
        } else if(num == "3") {
            int rand = getRandom(1, 100);
            int money = getRandom(15, 200);
            globalGameData.money += money;
            if(rand <= 80) {
                globalGameData.health -= 5;
            } else if(rand <= 40) {
                globalGameData.health -= 30;
            } else if(rand <= 20) {
                globalGameData.health -= 70;
            } else if(rand <= 20) {
                globalGameData.health -= 100;
            }
            typewriter("Okradlem bank! Suuuupeer...", 75);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            typewriter("(-" + to_string(rand) + " HP, " + to_string(money) + " Pieniadze)", 15);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            cout << endl;
            typewriter("Teraz moge isc spac...", 15);
            break;
        } else if(num == "4") {
            cout << "Nauczyles sie nowych zagadnien!" << endl;
            globalGameData.hunger += 5;
            globalGameData.knowledge += 5 + globalGameData.xpBoost;
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            typewriter("(+5 Glod, +" + to_string(5 + globalGameData.xpBoost) + " Wiedza)", 15);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            cout << endl;
            typewriter("Teraz moge isc spac...", 15);
            break;
        } else if(num == "5") {
            if(globalGameData.knowledge < 300) {
                cout << "Nie jestes na tyle wycwiczony zeby podejsc do egzaminu." << endl;
                continue;
            }
            cout << "Przystapiles i zakonczyles z powodzeniem egzamin koncowy!" << endl;
            typewriter("Idziesz spac z wiedza ze skonczyles pierwszy semestr studiow...", 15);
            globalGameData.dead = true;
            break;
        } else if(num == "motherlode") {
            typewriter("Ktos ci wyslal", 75);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            typewriter(" pieniadze!", 150);
            cout << endl;
            globalGameData.money += 500;
            typewriter("(+500 Pieniadze)", 15);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            continue;
        } else if(num == "knowledgeup") {
            typewriter("Czujesz sie madrzejszy o 300 punktow Wiedzy!", 75);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            globalGameData.knowledge += 300;
            cout << endl;
            typewriter("(+300 Wiedza)", 15);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            continue;
        }
    }
    cout << endl;
    Sleep(1000);
    saveData();
    startNewDay();
}

void startGame() {
    typewriter("Witaj w grze ");
    Sleep(500);
    typewriter("Life RPG", 250);
    cout << endl;
    startNewDay();
}

void startNewGame() {
    cout << " __          __    _     _                 _____          _             \n"
            " \\ \\        / /   | |   (_)               |  __ \\        | |            \n"
            "  \\ \\  /\\  / /   _| |__  _  ___ _ __ ____ | |__) |__  ___| |_ __ _  ___ \n"
            "   \\ \\/  \\/ / | | | '_ \\| |/ _ \\ '__|_  / |  ___/ _ \\/ __| __/ _` |/ __|\n"
            "    \\  /\\  /| |_| | |_) | |  __/ |   / /  | |  | (_) \\__ \\ || (_| | (__ \n"
            "     \\/  \\/  \\__, |_.__/|_|\\___|_|  /___| |_|   \\___/|___/\\__\\__,_|\\___|\n"
            "              __/ |                                                     \n"
            "             |___/                                                      " << endl;
    cout << "1. Uczen (HP 100, Wiedza 50, Exp Boost 0, Pieniadze 50zl)" << endl;
    cout << "2. Dobry Uczen (HP 75, Wiedza 100, Exp Boost 2, Pieniadze 75zl)" << endl;
    cout << "3. Szybki Uczen (HP 100, Wiedza 40, Exp Boost 5, Pieniadze 75zl)" << endl;
    int num;
    cin >> num;
    while (true) {
        if (num == 1) {
            cout << "Wybrales postac: Uczen" << endl;
            globalGameData.health = 100;
            globalGameData.knowledge = 50;
            globalGameData.xpBoost = 0;
            globalGameData.money = 50;
            globalGameData.playerClass = 0;
            break;
        } else if (num == 2) {
            cout << "Wybrales postac: Dobry Uczen" << endl;
            globalGameData.health = 75;
            globalGameData.knowledge = 100;
            globalGameData.xpBoost = 2;
            globalGameData.money = 75;
            globalGameData.playerClass = 1;
            break;
        } else if (num == 3) {
            cout << "Wybrales postac: Szybki Uczen" << endl;
            globalGameData.health = 100;
            globalGameData.knowledge = 40;
            globalGameData.xpBoost = 5;
            globalGameData.money = 75;
            globalGameData.playerClass = 2;
            break;
        }
    }
    globalGameData.hunger = 0;
    saveData();
    startGame();
}

void popupWelcomeAndAwait() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "  _      _  __       _____  _____   _____ \n"
            " | |    (_)/ _|     |  __ \\|  __ \\ / ____|\n"
            " | |     _| |_ ___  | |__) | |__) | |  __ \n"
            " | |    | |  _/ _ \\ |  _  /|  ___/| | |_ |\n"
            " | |____| | ||  __/ | | \\ \\| |    | |__| |\n"
            " |______|_|_| \\___| |_|  \\_\\_|     \\_____|\n"
            "                                          \n"
            "                                          " << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    loadData();
    cout << "1. Nowa Gra" << endl;
    cout << "2. Kontynuuj";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    if (globalGameData.loaded) {
        cout << " (" << playerClassToString() << " " << globalGameData.health << " HP)" << endl;
    } else {
        cout << " (Brak)" << endl;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    while (true) {
        int num;
        cin >> num;
        if (num == 1) {
            startNewGame();
            break;
        } else if (num == 2) {
            if (!globalGameData.loaded) {
                cout << "Brak zapisu gry!" << endl;
                continue;
            }
            startGame();
        }
    }
}

void startMainMenu() {
    popupWelcomeAndAwait();
}
