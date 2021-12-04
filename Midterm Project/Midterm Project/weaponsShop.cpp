#include "weaponsShop.h"


//Here, the user will be able to spend their coins on getting upgraded weapons.
//This code uses a vector with the class Weapon to store all the information read from the file
void weaponsShop::weaponShop(player& p1) {
	//Every time we enter the weapons shop, take a look through the file as to what is available
	//THis allows for the possiblity of a new weapon's shop on every floor.
	//Thus, it is highly possible that an item that can be brought at a lower level (With more money than is available)
	//is more op than one brought at a later leve. Kinda reminds me of SAO
	vector<weapon> weaponsList;
	fstream weaponFile;
	string weaponFileName = "weaponsList.txt", item;
	int cost, dmg, selection;
	int maxHP, HP;
	bool loop = true;
	char acknowledge;
	//Open the file, reset back to hand if file cannot be opened.
	weaponFile.open(weaponFileName);
	if (weaponFile.fail()) {
		cerr << "We couldn't open the weapons file. You'll have to stick with your fist" << endl;
		p1.setWeapon("Hand");
		p1.setDMG(2);
		return;
	}

//Take in the weapon choices from the file to a vector
	//Format is
	//Damage, cost, string.
	while (!weaponFile.eof()) {
		weaponFile >> cost >> dmg >> maxHP >> HP;
		weaponFile.seekg(1, std::ios_base::cur);
		getline(weaponFile, item);
		weaponsList.push_back(weapon(item, dmg, cost, maxHP, HP));
	}

//This starts the buying process from the user.
	while (loop) {
		cout << "Your options:" << endl;
		cout <<setw(8) << right << "Cost"
			<<setw(11) << right << "Effect"
			<<setw(10) << right << "Item" << endl;
		//Loop through the whole vector, display all the options to the user. Then, have the user make a selection
		for (int i = 0; i < weaponsList.size(); i++) {
			//The following is a weapon;
			if (weaponsList[i].getDMG() != 0) {
				cout << i + 1 << ". "
					<< setw(3) << right << weaponsList[i].getCost()
					<< setw(9) << right << weaponsList[i].getDMG() << " Dmg   "
					<< left << weaponsList[i].getItem() << endl;
			//The following is a potion. 
			} else {
				cout << i + 1 << ". "
					<< setw(3) << right << weaponsList[i].getCost()
					<< setw(15) << right << "Unknown   "
					<< left << weaponsList[i].getItem() << endl;
			}
		}
		cout << "You currently have " << p1.getBal() << " coins" << endl;
		cout << "Enter 0 to exit the buying process. Please enter your selection: ";
		cin >> selection;
//If the user's selection is 0, then we know to exit the loop
		if (selection >= 16) {
			cout << "Sorry, " << selection << " is an invalid choice\n";
		}else if (selection == 0) { //this part breaks if a random input that is not a numbe is chosen
			loop = false;
//Otherwise, let's check if the user can actually buy the item. If they can, then prompt them to ensure their purchase is correct
		} else if (weaponsList[selection-1].getCost() > p1.getBal()) {
			cout << "Sorry, you can't afford " << weaponsList[selection-1].getItem() << endl;
		} else {
			cout << "Ready to purchase " << weaponsList[selection-1].getItem() << "? Your new balance will be: " << p1.getBal() - weaponsList[selection-1].getCost() << ". Enter Y/N: ";
			cin >> acknowledge;
			acknowledge = tolower(acknowledge);
			//The user has acknowledge that the purchase is valid. Change the player damage, and change the player's weapon name 
			//Also modify the user's balance
			if (acknowledge == 'y') {
				//If the object is a pottion (i.e. If damage incurred is 0)
				if (weaponsList[selection-1].getDMG() == 0) {
					p1.modHealth(weaponsList[selection-1].getHP());
					if (p1.getHP() <= 0) {
						cout << "We're sorry, you have died!" << endl;
						cout << "The game has now ended, but you can always restart!" << endl;
						cout << "PRINT ENEMIES DEFEATED FUNCTION GOES HERE\n";
						//FUNCTION TO PRINT STACK GOES HERE
						//FUNCTION TO CLEAR STACK GOES HERE
						//2. Create an operator overload of the operator<< to print the names and level of all the
						//enemy objects in the entire stack.
						//3. Create a function to clear the whole stack.This function should be called at the end of
						//the program
						loop = false;
					}
					p1.modMaxHP(weaponsList[selection-1].getMaxHP());
				} else {
					p1.setDMG(weaponsList[selection-1].getDMG());
					p1.setWeapon(weaponsList[selection-1].getItem());
				}
				p1.modBal(-weaponsList[selection-1].getCost());
				cout << "You've brought " << weaponsList[selection-1].getItem() << "!" << endl;
			} else {
				cout << "Alright, we won't make that purchase." << endl;
			}

		}

		cout << "Here goes the shop tracker thing that we need to do for task 5" << endl;
	}



	
}