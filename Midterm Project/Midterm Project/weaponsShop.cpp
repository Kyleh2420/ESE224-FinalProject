#include "weaponsShop.h"
/*
//Here, the user will be able to spend their coins on getting upgraded weapons.
//This code uses a vector with the class Weapon to store all the information read from the file
void weaponsShop::weaponShop(player& p1) {
	//Every time we enter the weapons shop, take a look through the file as to what is available
	//THis allows for the possiblity of a new weapon's shop on every floor.
	//Thus, it is highly possible that an item that can be brought at a lower level (With more money than is available)
	//is more op than one brought at a later leve. Kinda reminds me of SAO
	//Take in the weapon choices from the file to a vector
	//Format is
//This starts the buying process from the user.
    shopStartup(p1);
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

void weaponsShop::shopStartup(player& p1) {
//Open the file, reset back to hand if file cannot be opened.
	weaponFile.open(weaponFileName);
	if (weaponFile.fail()) {
		cerr << "We couldn't open the weapons file. You'll have to stick with your fist" << endl;
		p1.setWeapon("Hand");
		p1.setDMG(2);
		return;
	}
    //Loads everything into the vectors we have setup.
	//Damage, cost, string.
	while (!weaponFile.eof()) {
		weaponFile >> cost >> dmg >> maxHP >> HP;
		weaponFile.seekg(1, std::ios_base::cur);
		getline(weaponFile, item);
		weaponsList.push_back(weapon(item, dmg, cost, maxHP, HP));
	}
}

*/
//Below this point is used for weaponShopv2, the second iteration of weaponsShop


//WeaponsShop.cpp/h now has 2 classes within it, the class that creates the doubly linked list (weaponsShopv2), and the driver class itself that runs it (shop)

//Sets up the linked list
weaponsShopv2::weaponsShopv2() {
    head = NULL;
    tail = NULL;
    current = NULL;
}

//Adds a new weapon to the end of the doubly linked list
void weaponsShopv2::addWeapon(weaponNode* weapon) {
    if (head == NULL) {
        head = current = tail = weapon;
    } else {
        tail->setNext(weapon);
        tail->getNext()->setPrev(tail);
        tail = tail->getNext();
    }
}

//ALlows the player to move the current selection forward
void weaponsShopv2::moveToNext() {
    if (current->getNext() == NULL) {
        cout << "We can't move to the next!" << endl;
    } else {
        current = current -> getNext();
    }
}

//Allows the player to move the current selection backward
void weaponsShopv2::moveToPrev() {
    if (current->getPrev() == NULL) {
        cout << "We can't move to the previous!" << endl;
    } else {
        current = current -> getPrev();
    }
}

//Moves to the head of the lsit
void weaponsShopv2::moveToHead() {
    current = head;
}

//Moves to the tail of the list
void weaponsShopv2::moveToTail() {
    current = tail;
}


//The print all function, used to display the contents of the list when the shop is called.
void weaponsShopv2::printAll() {
	//We start from the very very beginning, the head.
	weaponNode* tmp = head;

	//If the pokenode is still null, then we haven't added any pokemon
	if (tmp == NULL) {
		cout << "There are no weapons" << endl;
		return;
	}
    cout <<setw(4) << right << "Cost"
        <<setw(11) << right << "Effect"
        <<setw(10) << right << "Item" << endl;
	
	//Loops through the whole thing until tmp is Null (Or rather, when the next one does not exist)
	while (tmp != NULL) {
		if (tmp->getItem().compare(current->getItem()) == 0)
			cout << "*";
		tmp->print();
		tmp = tmp->getNext();
	}
}

//Will delete and free up the memory space from the doubly linked list.
//Will be called when we change floors
void weaponsShopv2::deleteAll() {
    moveToHead();
    while (current->getNext() != NULL) {
        current = current->getNext();
        free(current->getPrev());
    }
    free(current);
}

//Will be called to allow the user to purcahse a product
weaponNode* weaponsShopv2::purchaseProduct(player & p1) {
    char selection;
    //See if the player can afford said product. If so, then do it.
    if (p1.getBal() < current->getCost()) {
        cout << "Sorry, you can't afford " << current->getItem() << endl;
    } else {
        //Confirm that the user wants to purchase the product
        cout << "Ready to purcahse " << current->getItem() << "? Your new balance will be "
            << p1.getBal() - current->getCost() << ". Enter Y/N: ";
        cin >> selection;
        //Lowercase to limit the number of cases
        selection = tolower(selection);
        //If they do, then alter their stats accordingly.
        if (selection == 'y') {
            //If the damage is 0, then it is a potion
            if (current->getDMG() == 0) {
                p1.modHealth(current->getHP());
                p1.modMaxHP(current->getMaxHP());
            } else {
                p1.setDMG(current->getDMG());
                p1.setWeapon(current->getItem());
            }
            p1.modBal(-current->getCost());
            cout << "You brought " << current->getItem() << "!" << endl;
            //Return the item that was brought for the stack
            return current;
        } else {
            cout << "Alright, we won't buy that item" << endl;
        }
    }
    //If we exit the function this way, the user hasn't brought anything.
    //Return NULL so that we don't add a random value to the stack
    return NULL;
}
//Sets up the shop by reading in a file and creating the doubly linked list required.
shop::shop(player& p1, int floor) {
    //According to the floor, will select a different weapons file.
    switch(floor) {
        case 0:
            weaponFileName = "F0Weapons.txt";
            break;
        case 1:
            weaponFileName = "F1Weapons.txt";
            break;
        case 2:
            weaponFileName = "F2Weapons.txt";
            break;
        case 3:
            weaponFileName = "F3Weapons.txt";
            break;
        default:
            cout << "We couldn't find that floor!" << endl;
    }
    weaponFile.open(weaponFileName);
    if (weaponFile.fail()) {
        cerr << "We couldn't open the weapons file. You'll have to stick with your fist" << endl;
        //If there is an error loading the file, this flag is here to prevent the shop from running
        flag = true;
        p1.setWeapon("Hand");
        p1.setDMG(2);
        return;
    }

    //Read in from the file the stats and items that go in the shop
    while(!weaponFile.eof()) {
        weaponFile >> cost >> dmg >> maxHP >> HP;
        weaponFile.seekg(1, std::ios_base::cur);
        getline(weaponFile, name);

        //Add it to the linked list
        listOfWeapons.addWeapon(new weaponNode(name, dmg, cost, maxHP, HP));
    }
}

//The main running code to run this here shop
void shop::runShop(player& p1) {
    char selection;
    //This flag is here to ensure that there is a linked list loaded for the user to purchase from
    if (!flag) {
        listOfWeapons.moveToHead();
        while (true) {
            //User Interface
            cout << "Your Options: \n";
            listOfWeapons.printAll();
            cout << "You currently have " << p1.getBal() << " coins" << endl;
            cout << "A: Exit the shop" 
                << "\nS: Move to next"
                << "\nW: Move to previous"
                << "\nD: Purchase the product" << endl;
            cout << "Your selection: ";
            cin >> selection;
            //tolower to limit the number of selections
            selection = tolower(selection);
            //I chose wasd because it was the most familiar and elegant. ws to go up or down, d to proceed, or a to go back
            switch (selection) {
                //If we go back, empty the stack and print out the user's purchases
                case 'a':
                    while (!itemStack.empty()) {
                        tmp = itemStack.top();
                        itemStack.pop();

                        cout << "You purchased: ";
                        tmp->print();
                    }
                    return;
                case 's':
                    listOfWeapons.moveToNext();
                    break;
                case 'w':
                    listOfWeapons.moveToPrev();
                    break;
                case 'd':
                    tmp = listOfWeapons.purchaseProduct(p1);
                    //If the product was null (Nothing was purchased), then dont' add it to the stack
                    if (tmp != NULL) {
                        itemStack.push(tmp);
                    }
                    break;
                default:
                    cerr << "That wasn't an option" << endl;
            }
        }
    } else {
       cerr << "There was an error loading the weapons" << endl;
    }
}
