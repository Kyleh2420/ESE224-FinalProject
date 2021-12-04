#pragma once
#include <string>
#include <iostream>
using namespace std;

class weapon {
private:
	string wItem;
	int wDamage;
	int wCost;
	int wMaxHP, wHP;
public:
	//Default constructor
	weapon();
	//Weapon constructor
	weapon(string i, int d, int c, int m, int h);
	//Setters!
	void setItem(string in);
	void setDMG(int i);
	void setCost(int i);
	void setMaxHP(int i);
	void setHP(int i);

	//Getters!
	string getItem();
	int getDMG();
	int getCost();
	int getMaxHP();
	int getHP();
};



//Node for the weapons shop
class weaponNode {
    private:
        string item;
        int cost, dmg, selection;
        int maxHP, HP;
        weaponNode* next;
        weaponNode* prev;
    public:
        weaponNode(string name, int dmg, int cost, int maxHP, int HP);
        void setNext(weaponNode* next);
        void setPrev(weaponNode* prev);
        weaponNode* getNext();
        weaponNode* getPrev();
        string getItem();
        int getDMG();
        int getCost();
        int getMaxHP();
        int getHP();
		void print();
};


