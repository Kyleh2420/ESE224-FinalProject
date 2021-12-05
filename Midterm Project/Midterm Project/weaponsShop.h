#pragma once
#include <fstream>
#include <iomanip>
#include <vector>
#include <stack>
#ifndef PLAYER
#define PLAYER
#include "player.h"
#endif
#include "weapon.h"
#ifndef TEMPLATESTACK
#define TEMPLATESTACK
#include "templateStack.h"
#endif
/*
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
*/

//This class, similar to the pokemon lab(pokedex), creates the linked list using the class weaponNode (pokeNode)
//It is then run by the driver class shop (pokemonTrainer)
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

        weaponNode* purchaseProduct(player& p1);
};

//THe driver class for the weaponsShopv2 class
class shop {
    private:
    //File loading and declaring an active linked list
    fstream weaponFile;
    string weaponFileName;
    weaponsShopv2 listOfWeapons;
    //Flag will go true if the file could not be opened
    bool flag = false;

    //Shopping tracker variables
    weaponNode* tmp;
    stack <weaponNode*> itemStack;


    //Tmp vars to be loaded in
    int cost=0, dmg=0;
    int maxHP=0, HP=0;
    string name="";
    public:
    //The following functions really drive the program
        shop(player& p1, int floor);
        void runShop(player& p1);
};