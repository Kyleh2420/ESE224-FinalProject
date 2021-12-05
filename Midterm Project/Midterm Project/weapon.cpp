#include "Weapon.h"
#include <iomanip>

/*
weapon::weapon() {
    wItem = "";
    wDamage = 0;
    wCost = 0;
    wMaxHP = 0;
    wHP = 0;
}
weapon::weapon(string i, int d, int c, int m, int h) {
    wItem = i;
    wDamage = d;
    wCost = c;
    wMaxHP = m;
    wHP = h;
}

//Getters
string weapon::getItem() {
    return wItem;
}

int weapon::getDMG() {
    return wDamage;
}

int weapon::getCost() {
    return wCost;
}
int weapon::getMaxHP() {
    return wMaxHP;
}
int weapon::getHP() {
    return wHP;
}

//Setters
void weapon::setItem(string in) {
    wItem = in;
}
void weapon::setDMG(int i) {
    wDamage = i;
}
void weapon::setCost(int i) {
    wCost = i;
}
void weapon::setMaxHP(int i) {
    wMaxHP = i;
}
void weapon::setHP(int i) {
    wHP = i;
}


*/

//The following is for weaponNode, the doubly linked list version of the shop

//To create a new node
weaponNode::weaponNode(string name, int dmg, int cost, int maxHP, int HP) {
    this->item = name;
    this->dmg = dmg;
    this->cost = cost;
    this->maxHP = maxHP;
    this->HP = HP;
}

//Setters!

//Points to the next item in the shop
void weaponNode::setNext(weaponNode* next) {
    this->next = next;
}

//Points to the previous item in the shop
void weaponNode::setPrev(weaponNode* prev) {
    this->prev = prev;
}

//Returns the next item in the shop
weaponNode* weaponNode::getNext() {
    return next;
}

//Returns the previous item in the shop
weaponNode* weaponNode::getPrev() {
    return prev;
}

//Getters!

//Returns the name of the item
string weaponNode::getItem() {
    return item;
}

int weaponNode::getDMG() {
    return dmg;
}

int weaponNode::getCost() {
    return cost;
}
int weaponNode::getMaxHP() {
    return maxHP;
}
int weaponNode::getHP() {
    return HP;
}


//Will print out different text based on whether is potion or not
void weaponNode::print() {
    cout << " ";
    if (getDMG() != 0) {
        cout << setw(3) << right <<getCost()
            << setw(9) << right << getDMG() << " Dmg   "
            << left << getItem() << endl;
    //The following is a potion. 
    } else {
        cout << setw(3) << right << getCost()
        << setw(15) << right << "Unknown   "
        << left << getItem() << endl;
    }
}