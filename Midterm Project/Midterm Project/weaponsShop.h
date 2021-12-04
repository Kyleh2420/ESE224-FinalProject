#pragma once
#include <fstream>
#include <iomanip>
#include <vector>
#ifndef PLAYER
#define PLAYER
#include "player.h"
#include "weapon.h"
#endif

//The weapons shop handler
class weaponsShop {
    private:
        vector<weapon> weaponsList;
        fstream weaponFile;
        string weaponFileName = "weaponsList.txt", item;
        int cost, dmg, selection;
        int maxHP, HP;
        bool loop = true;
        char acknowledge;
	
    public:

    void weaponShop(player& p1);
    void shopStartup(player& p1);
};


class weaponsShopv2 {
    private:
        typedef weaponNode* weaponNodePtr;
        weaponNodePtr head, tail, current;
        bool flag = true;
    public:
        //The pointers and setup stuff needed 
        weaponsShopv2();
        void addWeapon(weaponNode* weapon);
        void moveToNext();
        void moveToPrev();
        void moveToHead();
        void moveToTail();
        void printAll();
        void setTail(weaponNode* tail);
        weaponNode* getCurrent();
		void deleteAll();

        void purchaseProduct(player& p1);
};

//THe driver class for the weaponsShopv2 class
class shop {
    private:
    fstream weaponFile;
    string weaponFileName;
    weaponsShopv2 listOfWeapons;
    //Flag will go true if the file could not be opened
    bool flag = false;


    //Tmp vars to be loaded in
    int cost, dmg;
    int maxHP, HP;
    string name;
    public:
    //The following functions really drive the program
        shop(player& p1, int floor);
        void runShop(player& p1);
};