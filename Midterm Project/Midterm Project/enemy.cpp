#include "enemy.h"

enemy::enemy(int floorLevel) {
    switch (floorLevel) {
    case 0:
        enemyFileName = "F0Enemies.txt";
        //cout << "Opening " << enemyFileName << endl;
        enemyList.open(enemyFileName);
        if (enemyList.fail()) {
            cerr << "Error: F0Enemies.txt not found" << endl;
            exit(1);
        }
        break;
    case 1:
        enemyFileName = "F1Enemies.txt";
        //cout << "Opening " << enemyFileName << endl;
        enemyList.open(enemyFileName);
        if (enemyList.fail()) {
            cerr << "Error: F1Enemies.txt not found" << endl;
            exit(1);
        }
        break;
    case 2:
        enemyFileName = "F2Enemies.txt";
        //cout << "Opening " << enemyFileName << endl;
        enemyList.open(enemyFileName);
        if (enemyList.fail()) {
            cerr << "Error: F2Enemies.txt not found" << endl;
            exit(1);
        }
        break;
    case 3:
        enemyFileName = "F3Enemies.txt";
        //cout << "Opening " << enemyFileName << endl;
        enemyList.open(enemyFileName);
        if (enemyList.fail()) {
            cerr << "Error: F3Enemies.txt not found" << endl;
            exit(1);
        }
        break;
    default:
        cout << "Well that wasn't supposed to happen. We couldn't find that floor!" << endl;
        break;
    }

    //The following reads in the enemy list into the corresponding vector lists.
    getLineCount();
    randomizeSelector();
    name = listOfNames[selector];
    maxHealth = listOfMaxHP[selector];
    healthPoints = listOfHP[selector];
    attackDamage = listOfAD[selector];
    level = listOfLevel[selector];
}

enemy::enemy(string n, int max, int hp, int ad, int lvl) {
    name = n;
    maxHealth = max;
    healthPoints = hp;
    attackDamage = ad;
    level = lvl;
}

//Getters!
int enemy::getLvl() {
    return level;
}

//Setters!
void enemy::setLvl(int input) {
    level = input;
}

//Modifiers
void enemy::modHealth(int input) {
    healthPoints += input;
    if (healthPoints > maxHealth) {
        healthPoints = maxHealth;
    }
}

void enemy::modDamage(int input) {
    attackDamage += input;
    if (attackDamage < 0) {
        attackDamage = 0;
    }
}

ostream& operator << (ostream& os, const enemy& e) {
    os << "\nName: " << e.name << "\nMax Health: " << e.maxHealth 
    << "\nHP: " <<  e.healthPoints << "\nDamage: " << e.attackDamage * e.level << "\nLevel: " <<  e.level;
    return os;
}


//The following pertains to the randomization selection of enemies


 void enemy::getLineCount() {
    while (!enemyList.eof()) {
        enemyList >> maxHealth >> healthPoints >> attackDamage >> level;
        getline(enemyList, name);
        listOfNames.push_back(name);
        listOfMaxHP.push_back(maxHealth);
        listOfHP.push_back(healthPoints);
        listOfAD.push_back(attackDamage);
        listOfLevel.push_back(level);
    }
    //cout << "Line count is: " <<  listOfNames.size() << endl;
}


void enemy::randomizeSelector() {
    srand(time(0));
    selector = rand() % listOfNames.size();
}