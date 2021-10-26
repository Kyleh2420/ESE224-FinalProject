#include "enemy.h"
#include "fileOperations.h"
#include "Weapon.h"
#include "floor.h"
#include "randomEvents.h"
//player.h and scoreboard.h don't need to be called, since they are already called in fileOperations.h
//If called again, it will result in a redefinition error
using namespace std;


//Enter Combat. WIll only exit when one of the following conditions are met:
//1. The player Runs away
//2. The player runs out of HP
//3. The enemy runs out of hp
void enterCombat(player& p1, enemy& e1, scoreboard& p1Scoreboard) {
	cout << "Entering combat with " << e1 << endl;
	cout << "Your stats: " << p1 << endl;
}

//The player will have 4 options
//1. Examine themselves (Return HP/MaxHP, damage, and name)
//	1a. Change weapon (Only in the beginning of the encounter) [At least that's what I want it to be]
//2. Examine the enemy (Return Name, HP/Max HP, damage)
//3. Attack 
//4. Run Away
void playerCombat(player&, weapon[4][4], enemy&, scoreboard&) {

}

//The enemy will attack.
//Decrease player's HP according to enemy's level and AD
//Check if player is dead
bool enemyCombat(enemy&, player&, scoreboard&) {
	return false;
}

//This function is essentially a pause menu. The player has the following options:
//1. Examine themselves
//2. See the scorboard
//3. Save and Quit
void playerOptions(player& p1, fileOperations& files, scoreboard& p1Scoreboard) {
	int selection;
	bool loop = true;
	while (loop) {
		cout << "Pause menu\n---------------\n"
			<< "Please enter a number\n"
			<< "1 - Examine Yourself\n"
			<< "2 - See the Scoreboard\n"
			<< "3 - Exit the menu\n"
			<< "4 - Save and quit\nYour selection: ";
		cin >> selection;
		switch (selection) {
		case 1:
			cout << "\nYou selected 'Examine Yourself'" << endl;
			cout << p1 << endl;
			loop = false;
			break;
		case 2:
			cout << "\nYou selected 'See the scoreboard'" << endl;
			cout << p1Scoreboard << endl;
			loop = false;
			break;
		case 3:
			cout << "\nYou selected 'Exit the menu'" << endl;
			loop = false;
			break;
		case 4:
			cout << "\nYou selected 'Save and Quit'" << endl;
			files.save2File(p1);
			files.save2File(p1Scoreboard);
			files.closeFile();
			exit (0);
			loop = false;
			break;
		default:
			cout << "That wasn't an option!" << endl;
		}
	}
}

//Changes weapon
void chooseWeapon(weapon[4][4], int, player&) {

}

int main() {
	player p1;
	scoreboard p1Scoreboard;
	fileOperations files;
	
    //The following will loop through the player's starting options 
	//The User will select whether or not a new file is created or loaded.
	//If a new file is created, it will Ask for the players name and difficulty, then save those to 
	//player p1 and scoreboard p1Scoreboard, respectively. It will then jump to
	//playerOptions (The glorified pause menu) for file saving
	char selection;
    bool loop = true;
    while (loop) {
			cout << "Would you like to create a new file or load a save file? "
				<< "\nN - Create a new save file \nL - Load a save file \nYour answer: ";
			cin >> selection;
			selection = tolower(selection); //Lowercase everything to limit the number of cases
			switch(selection) {
				case 'l':
					p1Scoreboard.setFloor(0);
					p1Scoreboard.setPos(2);
					loop = false;
					break;
				case 'n': //New File is to be created. We must gather information about the user.
					cout << "Please enter your player name: ";
					p1.setName(cin);
					while (loop) {
						cout << "Please enter your difficulty level\nE - easy\nM - Medium\nH - Hard\nYour selection: ";
						cin >> selection;
						selection = tolower(selection);
						switch(selection){
							case 'e':
								cout << "Difficulty set to easy" << endl;
								p1Scoreboard.setDiff("Easy");
								loop = false;
								break;
							case 'm':
								cout << "Difficulty set to medium" << endl;
								p1Scoreboard.setDiff("Medium");
								loop = false;
								break;
							case 'h':
								cout << "Difficulty set to hard" << endl;
								p1Scoreboard.setDiff("Hard");
								loop = false;
								break;
							default:
								cout << "Please enter a valid response" << endl;
								break;
						}
					}
					p1Scoreboard.setFloor(0);
					p1Scoreboard.setPos(0);
					cout << "Please enter a save file name: ";
					files.setPName(cin);
					//cout << "Please enter a scoreboard file name with a .txt extention: ";
					//p1Scoreboard.setName(cin);
					files.save2File(p1);
					files.save2File(p1Scoreboard);
				break;
				default:
					cout << "Please enter a valid response" << endl;
			}
    }
	cout << "Now entering Game Portion";

	loop = true;
	//While we are in the game
	//Each floor is a repeat with different probabilities, therefore this code reuses the same thing for every floor
	///THIS IS THE MAIN GAME LOOP
	//Each time this loop is run, we construct different objects depending on what we read from p1Scoreboard
	while (loop) {
		//Creates a new class playGame with the current floor
		gameFloor playGame(p1Scoreboard.getFloor(), p1Scoreboard.getPos());
		//Opens a file for the randomEvents that may occur (With tile 2)
		randomEvents event(p1Scoreboard.getFloor());
		//Primes the random event selector with the selector
		cout << "The current floor is: " << p1Scoreboard.getFloor() << endl;
		//We stay in this while loop as long as the usre has not reached the maximum position 
		//Anotherwards, repeat the following loop until we run out of positions to advance to
		while (playGame.getCurrentPos() < playGame.getTotalPos()-1) {
			//User Input. Gets whether the user would like to take a step or pause
			cout << "\nThe current position is " << playGame.getCurrentPos() << "/" << playGame.getTotalPos() << endl;
			cout << "Press [t] to take a step, or press [m] to access menu options. \nYou entered: ";
			cin >> selection;
			selection = tolower(selection);
			switch(selection) {
				case 't': //The user takes a step
					playGame.takeStep();
					//Now that the user has taken a step, we need to see what tile the user has landed on. Use playGame.getRandomEvent to see the tile
					//After the user takes a step, we need to see if a random encounter has occurred
					//Depending on what tile the user lands on, we must respond differently
					//As a reminder:
					//0 - Do Nothing
					//1 - Enter combat
					//2 - Random Event
					//Default: Something wrong occurred. Treat this as a do nothing 
					 switch(playGame.getRandomEvent()) {
					 	case 1: {
						 	cout << "You encounter an enemy" << endl;
					// 		//The following function requires weapons and an enemy to fight against
					// 		//My goal is to have the enemy randomly generated out of a file, according to 
					// 		//a preset list. 
					// 		//Ex: Fl1Enemies.txt and Fl1Weapons.txt both contain info about what is available on each floor	
							enemy e1;
							e1.randomEnemySelector(p1Scoreboard.getFloor());
					 		enterCombat(p1, e1, p1Scoreboard);
					 		break;
						}//These brackets are here to ger around the 
						 //"Transfer of control bypasses intitalization of variable e1"
						 //This error is caused by the case not being in it's own scope, which is solved with {}
					 	case 2:
						 	//cout << "A random event occurs" << endl;
							//The following gets a random event out of the file according to the floor
							//Generates a random line out of the list
							event.getRandom();
							//The following affects the users stats
							p1.modHealth(event.getHPChange());
							p1.modBal(event.getBalChange());
							//The following is user interface
							cout << event.getEvent() << endl;
							if (event.getHPChange() != 0) 
								(event.getHPChange() < 0) ? cout << "You have lost " << event.getHPChange() << "Hp"<< endl: cout << "You have gained " << event.getHPChange() << "Hp" << endl;
							if (event.getBalChange() != 0)
								(event.getBalChange() < 0) ? cout << "You have lost " << event.getBalChange() << "coins"<< endl: cout << "You have gained " << event.getBalChange() << "coins" << endl;
					 		break;
					 	case 0:
					 	default:
					// 		//QuIrKy comments need to be read from a file as well
					 		cout << "Quirky comment here" << endl;
					// 		break;
					}
					break;
				case 'm': //The user access a pause menu
					p1Scoreboard.setPos(playGame.getCurrentPos());
					playerOptions(p1, files, p1Scoreboard);
					break;
				default:
					cout << "That wasn't a valid option, please try again.";
			}

		}
		//Once we exit the above loop, we know that the user has completed the floor (Has advanced as far as they can on the floor)




		//Increases the floor count by 1
		p1Scoreboard.setFloor(p1Scoreboard.getFloor()+1);
		//Resets the player's position on the floor back to the beginning
		p1Scoreboard.setPos(0);
		//We can check if the user has reached the last floor. If they have, then we can exit the main game loop
		//If the user has reached the last floor, we can confirm the user has completed the game!
		if (p1Scoreboard.getFloor() == 4) {
			loop = false;
			cout << "Congrats, you've passed the game!"<< endl;
			break;
		}
		

	}
	
	//Tests
	//enemy Alex("Alex", 30, 30, 5, 1);
	//cout << Alex << endl;
	//weapon sword;

}
