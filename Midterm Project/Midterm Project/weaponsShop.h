#pragma once
#include <fstream>
#include <iomanip>
#include <vector>
#ifndef PLAYER
#define PLAYER
#include "player.h"
#include "weapon.h"
#endif


class weaponsShop {
    private:
        vector<weapon> weaponsList;
        fstream weaponFile;
        string weaponFileName = "weaponsList.txt", item;

    public:

    void weaponShop(player& p1);
};
