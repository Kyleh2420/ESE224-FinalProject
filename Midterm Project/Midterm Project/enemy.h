#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifndef PLAYER
#define PLAYER
#include "player.h"
#endif
using namespace std;

class enemy : public player{
private:
	//Enemys level. Each level increase should increase their stats
	int level = 0;


	//The following is for the random generation of enemies
	vector<string> listOfNames;
	vector<int> listOfMaxHP;
	vector<int> listOfHP;
	vector<int> listOfAD;
	vector<int> listOfLevel;
	string enemyFileName;
	fstream enemyList;
	int selector;
	void getLineCount();
	void randomizeSelector();
public:
	//Default constructor
	enemy(int floorLevel);
	//Enemy Constructor. Enter Name, MaxHP, hpCurrent, damage, and level
	enemy(string n, int max, int hp, int ad, int lvl);

	//Getters!
	//Returns the [int] current level of the enemy
	int getLvl();

	//Setters!
	void setLvl(int input);

	//Modifiers!
	void modHealth(int input);
	void modDamage(int input);

	//Example Usage: 
	//cout << enemyName << endl;
	friend ostream& operator <<(ostream& os, const enemy& e);
};

