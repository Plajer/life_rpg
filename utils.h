#include <string>

using namespace std;

#ifndef LIFE_RPG_UTILS_H
#define LIFE_RPG_UTILS_H

int getRandom(int, int);
void typewriter(string, int);
void typewriter(string);
void loadData();
void saveData();
string playerClassToString();
void startMainMenu();

#endif //LIFE_RPG_UTILS_H
