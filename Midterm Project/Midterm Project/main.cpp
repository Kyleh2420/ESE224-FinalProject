#include "enemy.h"
#include "fileOperations.h"
#include "Weapon.h"
#include "floor.h"
#include "randomEvents.h"
#include "randomComment.h"
#include "weaponsShop.h"
#ifndef TEMPLATESTACK
#define TEMPLATESTACK
#include "templateStack.h"
#endif
#include <string>
#include <vector>
#include <iomanip>
#include <stack>
#include <queue>
#include<list>
#include <utility>
fstream myFile;
//scoreboard.h don't need to be called, since they are already called in fileOperations.h
// player.h is called in enemy.h
//If called again, it will result in a redefinition error
using namespace std;

stack<int> combatloghealthstack;
stack<string> combatlognamestack;
stack<pair<string,int>> enemeystack;
//stack<int> enemeystacklevel;
queue<string> questCompleted;

void addtoenemystack(enemy& e1) //function to add enemy to enemystack
{
	enemeystack.push(make_pair(e1.getName(), e1.getLvl()));
}

void reverseStack(stack<pair<string, int>>& st)
{
	pair<string, int> item;
	stack<pair<string, int>> tmpStack;

	while (st.empty() == false)
	{
		item = st.top();
		st.pop();
		tmpStack.push(item);
	}

	st = tmpStack;
	return;
}

void reverseStacknum(stack<int> &st) //function to reverse any stack that has numbers
{
	int item;
	stack<int> tmpStack;

	while (st.empty() == false)
	{
		item = st.top();
		st.pop();
		tmpStack.push(item);
	}

	st = tmpStack;
	return;
}

void reverseStackname(stack<string>& st) //function to reverse any stack that has strings
{
	string item;
	stack<string> tmpStack;

	while (st.empty() == false)
	{
		item = st.top();
		st.pop();
		tmpStack.push(item);
	}

	st = tmpStack;
	return;
}

void printenemiesdefeated() //function to print out stack containing list of defeated enemies
{
	reverseStack(enemeystack);
	//reverseStackname(enemeystack);
	//reverseStacknum(enemeystacklevel);
	cout << "Enemies defeated: \n";
	while (!enemeystack.empty()) {
		//cout << enemeystack.top() << " Level: " << enemeystacklevel.top() << '\n';
		//enemeystack.pop();
		//enemeystacklevel.pop();

		cout << enemeystack.top().first << " Level: " << enemeystack.top().second << '\n';
		enemeystack.pop();
	}
	cout << endl;
}

void printcombatlog() //function to print combat log 
{
	reverseStacknum(combatloghealthstack);
	reverseStackname(combatlognamestack);
	cout << "Combat log: \n";
	while (!combatloghealthstack.empty()) {
		cout << combatlognamestack.top() << ": " << combatloghealthstack.top() << '\n';
		combatlognamestack.pop();
		combatloghealthstack.pop();
	}
	cout << endl;
}

void addtocombatlogplayer(player& p1) //function to add player info to combat log stack
{
	combatlognamestack.push(" " + p1.getName());
	combatloghealthstack.push(p1.getHP());
}

void addtocombatlogenemy(enemy& e1) //function to add enemy info to combat log stack
{
	combatlognamestack.push(e1.getName());
	combatloghealthstack.push(e1.getHP());
}



//The enemy will attack.
//Decrease player's HP according to enemy's level and AD
//Check if player is dead
bool enemyCombat(enemy& e1, player& p1, scoreboard& p1Scoreboard) {
	cout << "The enemy attacked you. " << -e1.getDMG()*e1.getLvl() << " HP." << endl;
	p1.modHealth(-e1.getDMG() * e1.getLvl());
	//If the user has died, then return false
	if (p1.getHP() <= 0) {
		combatlognamestack.push(" " + p1.getName());
		combatloghealthstack.push(0);
		printcombatlog();
		return false;
	}
	else {
		//The user is not dead yet. Keep the battle going
		addtocombatlogplayer(p1);
		return true;
	}
}


//The player will have 4 options
//1. Examine themselves (Return HP/MaxHP, damage, and name)
//	1a. Change weapon (Only in the beginning of the encounter) [At least that's what I want it to be]
//2. Examine the enemy (Return Name, HP/Max HP, damage)
//3. Attack 
//4. Run Away
//Enter Combat. WIll only exit when one of the following conditions are met:
//1. The player Runs away
//2. The player runs out of HP
//3. The enemy runs out of hp
void playerCombat(player& p1, enemy e1, scoreboard& p1Scoreboard) {
	bool loop = true;
	int tmp(-1);
	char selection;
	cout << "\n-----------------\nEntering combat with " << e1 << endl;
	cout << "Your stats: \n" << p1 << endl;
	while (loop) {
		cout << "Please make a selection" 
		<< "\n1 - Examine yourself"
		<< "\n2 - Examine the enemy"
		<< "\n3 - Attack"
		<< "\n4 - Run Away"
		<< "\nYour selection: ";
		cin >> selection;
		switch (selection) {
			case '1':
				cout << "\nExamine Yourself. Your stats: \n--------------" << p1 << endl;
				break;
			case '2': 
				cout << "\nExamine the enemy. " << e1.getName() << "'s stats: \n-----------------\n" << e1 << endl;
				break;
			case '3':
			//The player attacks the enemy.
				cout << "Attack" << endl;
				//Since we are adding coins ad scores according to the damage that the player does,
				//We need an ifstatement to see if the damage that the player does is way above the enemys HP.
				//If it is, then only add the rest of the player's HP and kill the enemy
				if (e1.getHP() <= p1.getDMG()) {
					p1.modBal(e1.getMaxHP());
					p1Scoreboard.addScore(1);
					cout << "The enemy has died!"
						<< "\nYou have earned " << e1.getMaxHP() << " coins." << endl;
					addtoenemystack(e1);
					//1. Create an insert function to add enemies to the top of the stack.
					combatlognamestack.push(e1.getName());
					combatloghealthstack.push(0);
					printcombatlog();
					loop = false;
				} else {
					//p1.modBal(p1.getDMG());
					cout << "You attacked the enemy, -" << p1.getDMG() << endl;
					addtocombatlogenemy(e1);
					loop = enemyCombat(e1, p1, p1Scoreboard);
				}
				e1.modHealth(-p1.getDMG());
				//Each time the user attacks, they have another chance at trying to run away.
				tmp = -1;
				break;
			case '4': 
				if (tmp >= 0) {
					cout << "The enemy has prevented you from running away. " << endl;
				}
				else {
					srand(time(0));
					tmp = rand() % 100;
					if (tmp < 60) {
						cout << "Run Away." << endl;
						printcombatlog();
						loop = false;
					}
					else {
						cout << "Run away has failed. The enemy has trapped you" << endl;
					}
				}
				break;
			default:
				cout << "That wasn't a selection! Please try again!" << endl;
		}
	}
	
}



//This function is essentially a pause menu. The player has the following options:
//1. Examine themselves
//2. See the scorboard
//3. Save and Quit
void playerOptions(player& p1, fileOperations& files, scoreboard& p1Scoreboard) {
	shop store(p1, p1Scoreboard.getFloor());
	char selection;
	bool loop = true;
	while (loop) {
		cout << "Pause menu\n---------------\n"
			<< "Please enter a number\n"
			<< "1 - Examine Yourself\n"
			<< "2 - See the Scoreboard\n"
			<< "3 - Enter the shop\n"
			<< "4 - Exit the menu\n"
			<< "5 - Save and quit\nYour selection: ";
		cin >> selection;
		switch (selection) {
		case '1':
			cout << "\nYou selected 'Examine Yourself'" << endl;
			cout << p1 << endl;
			loop = false;
			break;
		case '2':
			cout << "\nYou selected 'See the scoreboard'" << endl;
			cout << p1Scoreboard << endl;
			loop = false;
			break;
		case '3':
			cout << "\nYou selected 'Enter the shop'" << endl;
			loop = false;
			store.runShop(p1);
			break;
		case '4':
			cout << "\nYou selected 'Exit the menu'" << endl;
			loop = false;
			break;
		case '5':
			cout << "\nYou selected 'Save and Quit'" << endl;
			cout << "Quests Completed:" << endl;
			while (!questCompleted.empty())
			{
				cout << questCompleted.front()<<endl;
				questCompleted.pop();
			}
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

void checkQuest(player& p1, scoreboard& p1Scoreboard)
{
	//This function runs at the start of each floor.
	//Checks the quest completion of the previous floor and pushes the name into the queue.
	//Adds bonus points to the players score.
	//For the last 2 side quests, the bonus points are dependant on how well the player did to pass the quest
	switch (p1Scoreboard.getFloor())
	{
		//Floor 0 doenst get a case b/c floor 0 is the first level the player completes meaning there was no side quest before it.
	case 1:
		//Floor 0 requires the player to beat the floor wihtout buying a weapon from the shop.
		if (p1.getWeapon() == "Hand")
		{
			questCompleted.push("Don't Need a Weapon");
			p1Scoreboard.addBonus(2);//temp value
			cout << "Congratulations, you've completed (Don't need a weapon). You've earned 2 bonus points!" << endl;
			p1Scoreboard.addBonus(2);
		}
		break;
	case 2:
		//Floor 1 requires the player to beat the level with at least 10 coins in their balance
		if (p1.getBal() >= 10)
		{
			questCompleted.push("Money in the Bank");
			p1Scoreboard.addBonus(10);//temp value
			cout << "Congratulations, you've completed (Money in the Bank). You've earned 10 bonus points!" << endl;
			p1Scoreboard.addBonus(10);
		}
		break;
	case 3:
		//Floor 2 rrquires the player to beat the level with their damage higher than their max hp
		if (p1.getDMG() > p1.getMaxHP())
		{
			questCompleted.push("Glass Cannon");
			p1Scoreboard.addBonus(p1.getDMG());//temp value
			cout << "Congratulations, you've completed (Glass Canon). You've earned "<< p1.getDMG() << " bonus points!" << endl;
			p1Scoreboard.addBonus(p1.getDMG());
		}
		break;
	case 4:
		//Floor 3 requires the player to beat the level with at least 20% of their mac hp remaining
		if ((p1.getHP() / p1.getMaxHP()) >= 0.2)
		{
			questCompleted.push("Just a Scratch");
			p1Scoreboard.addBonus(p1.getHP());//temp value
			cout << "Congratulations, you've completed (Glass Canon). You've earned " << p1.getHP() << " bonus points!" << endl;
			p1Scoreboard.addBonus(p1.getHP());
		}
		break;
	default:
		break;
	}
}

void game(player& p1, scoreboard& p1Scoreboard, fileOperations& files) {
	bool loop;
	bool dead = false;
	char selection;
	//cout << "Now entering Game Portion";
	//Storytime!
	cout << "You are a skeleton who has been condemned to the depths of hell."
		<< "\nHowever, hell just isn't to your satisfaction, so you're escaping back to earth."
		<< "\nExplore the path, defeat enemies, collect organs, and set yourself up to become a real person again."
		<<"\nSucceed, and live a life of comfort back on earth."
		<<"\nFail, and become an unsuccessful ghost, forever stuck in the land of inbetween, neither satisfied on hell or reborn on earth."
		<<"\nYou must defeat at least 10 enemies in order to proceed to earth" <<  endl;
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
		//Opens the randomComments file
		randomComment quirkyComment(p1Scoreboard.getFloor());
		//Primes the random event selector with the selector
		cout << "The current floor is: " << p1Scoreboard.getFloor() << endl;

		//The following switch statment tells the user what side quest they have depending on what floor they are on.
		//It also checks if the previous floor's side quest was completed
		switch (p1Scoreboard.getFloor())
		{
		case 0:
			cout << "Current Side Quest: (Don't Need a Weapon) Don't buy a weapon, Pass this floor with only the default weapon." << endl;
			break;
		case 1:
			checkQuest(p1, p1Scoreboard);
			cout << "Current Side Quest: (Money in the Bank) Save at least 10 coins." << endl;
			break;
		case 2:
			checkQuest(p1, p1Scoreboard);
			cout << "Current Side Quest: (Glass Cannon) Get damage higher than max HP." << endl;
			break;
		case 3:
			checkQuest(p1, p1Scoreboard);
			cout << "Current Side Quest: (Just a Scratch) Survive with at least 20% HP remaining." << endl;
			break;
		case 4:
			checkQuest(p1, p1Scoreboard);
			break;
		}
		//We stay in this while loop as long as the usre has not reached the maximum position 
		//Anotherwards, repeat the following loop until we run out of positions to advance to
		while ((playGame.getCurrentPos() < playGame.getTotalPos()-1) && loop == true) {
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
							enemy e1(p1Scoreboard.getFloor());

					 		playerCombat(p1, playGame.getCurrentEnemy(), p1Scoreboard);
							if (p1.getHP() <= 0) {
								cout << "We're sorry, you have died!" << endl;
								cout << "The game has now ended, but you can always restart!" << endl;
								printenemiesdefeated();
								//FUNCTION TO PRINT STACK GOES HERE
								//FUNCTION TO CLEAR STACK GOES HERE
								//2. Create an operator overload of the operator<< to print the names and level of all the
								//enemy objects in the entire stack.
								//3. Create a function to clear the whole stack.This function should be called at the end of
								//the program
								loop = false;
								dead = true;
							}
							//enemyList.pop();
					 		break;
						}//These brackets are here to ger around the 
						 //"Transfer of control bypasses intitalization of variable e1"
						 //This error is caused by the case not being in it's own scope, which is solved with {}
					 	case 2:
						 	//cout << "A random event occurs" << endl;
							//The following gets a random event out of the file according to the floor
							//Generates a random line out of the list
							event.getRandom();
							cout << event.getEvent() << endl;
							//The following is user interface
							if (event.getHPChange() != 0)
								(event.getHPChange() < 0) ? cout << "You have lost " << event.getHPChange() << "Hp" << endl : cout << "You have gained " << event.getHPChange() << "Hp" << endl;
							if (event.getBalChange() != 0)
								(event.getBalChange() < 0) ? cout << "You have lost " << event.getBalChange() << "coins" << endl : cout << "You have gained " << event.getBalChange() << "coins" << endl;
							//The following affects the users stats
							//The user cannot die from a random event. Thus, if the HP change read is negative 
							//And is not greater 
							if ((event.getHPChange() >= 0) || (event.getHPChange() < 0 && !(abs(event.getHPChange()) > p1.getHP()))) {
								loop = p1.modHealth(event.getHPChange());
							} else {
								p1.setHP(1);
							}
							//The following will check if the user has died or not, and exit the floor
							if (!loop) {
								break;
							}
							p1.modBal(event.getBalChange());
							break;
					 	case 0:
					 	default:
					// 		//QuIrKy comments need to be read from a file as well
					 		//cout << "Quirky comment here" << endl;
							quirkyComment.getRandom();
							cout << quirkyComment.getEvent() << endl;
					// 		break;
					}
					break;
				case 'm': //The user access a pause menu
					p1Scoreboard.setPos(playGame.getCurrentPos());
					playerOptions(p1, files, p1Scoreboard);
					if (p1.getHP() <= 0) {
						loop = false;
						dead = true;
					}
					break;
				default:
					cout << "That wasn't a valid option, please try again.";
			}

		}
		//Once we exit the above loop, we know that the user has completed the floor (Has advanced as far as they can on the floor)
		//Or the user has died, and we just exited the loop. Check p1.health's status to determine which one
		
		//user has died
		if (p1.getHP() <= 0) {
			if (dead == false) {
				cout << "We're sorry that the game is over for you. You're more than able go and restart it!" << endl;
				printenemiesdefeated();
			}
		}
		else {
			//Increases the floor count by 1
			p1Scoreboard.setFloor(p1Scoreboard.getFloor() + 1);
			//Resets the player's position on the floor back to the beginning
			p1Scoreboard.setPos(0);
			//Clear the screen and introduce the new level
			cout << "\033[2J\033[1;1H";
			
			//We can check if the user has reached the last floor. If they have, then we can exit the main game loop
			//If the user has reached the last floor, we can confirm the user has completed the game!
			if (p1Scoreboard.getFloor() == 4) {
				loop = false;
				if (p1Scoreboard.getScore() > 10) {
					//We clear the screen
					cout << "\033[2J\033[1;1H";
					cout << "A booming voice around you tells \" Congratulations, you have collected enough organs to become a person again! Go enjoy your life\"" << endl;
					printenemiesdefeated();
				}
				else {
					//We clear the screen
					cout << "\033[2J\033[1;1H";
					cout << "A booming voice around you yells \"It looks like you haven't collected enough organs. I will now strip you of all your organs so that you will never be able to live again. \"" << endl;
					p1Scoreboard.setFloor(0);
					p1.setBal(0);
					p1.setHP(1);
					p1.setMaxHP(1);
					p1.setDMG(0);
					game(p1, p1Scoreboard, files);
				}
				break;
			}
			else {
				//We clear the screen
				cout << "\033[2J\033[1;1H";
				cout << "A booming voice around you yells \"Congratulations, you have passed this level!\"" << endl;
			}
		}
	}
	
	//Tests
	//enemy Alex("Alex", 30, 30, 5, 1);
	//cout << Alex << endl;
	//weapon sword;

}

void alphabeticalScore(fileOperations& files, player& p1, scoreboard& p1Scoreboard) {
	vector<string> names;
	vector<string> scores;
	names = files.getNames(p1Scoreboard, p1);
	scores = files.getScores(p1Scoreboard, p1);
	int min_idx;
	for (int i = 0; i < (names.size() - 1); i++) {
		min_idx = i;
		for (int j = i + 1; j < names.size(); j++)
			if (names[j] < names[min_idx])
				min_idx = j;
		string stemp = scores[min_idx];
		string ntemp = names[min_idx];
		scores[min_idx] = scores[i];
		names[min_idx] = names[i];
		scores[i] = stemp;
		names[i] = ntemp;
	}
	cout << "Scoreboard: \n";
	for (int i=0; i < names.size(); i++) {
		cout << "Name: " << setw(16) << left << names[i]
			 << "Score: " << setw(10) << left << scores[i] << endl;
	}
}

//Create a function to read the scoreboard file and to then create scoreboard objects for
//each player score in the scoreboard file.This function should load all the objects into a
//list.
void scoreboardList(std::list<scoreboard>& list) {
	//Read Scored Board
	myFile.open("scoreboard.txt", ios::in);
	if (myFile.fail()) {
		cerr << "Error saving the file! Please try again7!" << endl;
		exit(1);
	}
	vector<string> names;
	vector<string> scores;
	while (myFile) {
		string label;
		string name;
		string score;

		myFile >> label;
		if (myFile.eof())
			break;
		myFile >> name;
		names.push_back(name);
		myFile >> label;
		myFile >> score;
		scores.push_back(score);
	}
	//Create Objects for each score and plasce into list
	for (int i = 0; i < names.size(); i++) {
		scoreboard p1Scoreboard;
		p1Scoreboard.setName(names[i]);
		int x = stoi(scores[i]);
		p1Scoreboard.setScore(x);
		list.push_back(p1Scoreboard);
	}
}
//Create a function to ask the user for a nameand to then search for that name in the list.
//All players with that name should be outputted with their scores to the console screen.
//Use any search method that you prefer.
void askName(std::list<scoreboard>& list) {
	cout << "\n Enter a name to search for in the Scoreboard (Note: case Sensitive: ";
	string name;
	cin >> name;
	bool nameFound = false;

	for (auto v : list) {
		if (name.compare(v.getName()) == 0) {
			nameFound = true;
			cout << "Name: " << setw(16) << left << v.getName()
				<< "Score: " << setw(10) << left << v.getScore() << "\n";
		}
	}
	if (!nameFound) {
		cout << "Name not found.\n";
	}

}

/*Create a new list for averaged scores from the scoreboard.
Create a function to search the whole scoreboard list created previously for any names that
repeat.If any names repeat, then take the average of all the scores.Then add this averaged
score to the new scoreboard.
Insert the averaged score into the proper place, so that the list is sorted already from highest to
lowest.If a name doesn�t repeat, then also add that score to the list as well.*/
void averageScoreboard(std::list<scoreboard>& list1, std::list<scoreboard>& newlist) {
	int sum = 0;
	int count = 0;
	int average;
	string name;
	list <scoreboard> temp = list1;

	while (!temp.empty()) {
		name = temp.front().getName();
		for (auto v : list1) {
			if (name.compare(v.getName()) == 0) {
				sum += v.getScore();
				count++;
				temp.remove(v);
			}
		}
		average = sum / count;
		scoreboard p1Scoreboard;
		p1Scoreboard.setScore(average);
		p1Scoreboard.setName(name);
		if (newlist.empty()) {
			newlist.push_back(p1Scoreboard);
		}
		else {
			bool added = false;
			std::list<scoreboard>::iterator it;
			for (it = newlist.begin(); it != newlist.end(); it++) {
				if (average > it->getScore()) {
					newlist.insert(it, p1Scoreboard);
				}
			}
		}
	}
}


//should maybe keep the main program and then make another bigger menu program for all the menu stuff that has the scoreboard, search by name, enter game, quit, etc
int main() {
	player p1;
	scoreboard p1Scoreboard;
	fileOperations files;

	list <scoreboard> list1;
	scoreboardList(list1);

	//Ask for a name
	askName(list1);

	list1.sort();
	for (auto v : list1) {
		cout << "Name: " << setw(16) << left << v.getName()
			<< "Score: " << setw(10) << left << v.getScore() << "\n";
	}



	//Average score board
	list <scoreboard> avg;
	averageScoreboard(list1, avg);
	cout << "Average: \n";
	for (auto v : avg) {
		cout << "Name: " << setw(16) << left << v.getName()
			<< "Score: " << setw(10) << left << v.getScore() << "\n";
	}
	//The following will loop through the player's starting options 
	//The User will select whether or not a new file is created or loaded.
	//If a new file is created, it will Ask for the players name and difficulty, then save those to 
	//player p1 and scoreboard p1Scoreboard, respectively. It will then jump to
	//playerOptions (The glorified pause menu) for file saving
	char selection;
	string entry;
	bool loop = true;
	while (loop) {
		cout << "Would you like to create a new file or load a save file? "
			<< "\nN - Create a new save file \nL - Load a save file \nYour answer: ";
		cin >> selection;
		selection = tolower(selection); //Lowercase everything to limit the number of cases
		switch (selection) {
		case 'l':
			cout << "Please enter the savefile name: ";
			files.setPName(cin);
			files.chooseFile(p1Scoreboard, p1);

			loop = false;
			break;
		case 'n': //New File is to be created. We must gather information about the user.
			cout << "Please enter your player name: ";
			cin.ignore();
			std::getline(cin, entry);
			p1.setName(entry);
			/*
			while (loop) {
				cout << "Please enter your difficulty level\n1 - easy\n2 - Medium\n3 - Hard\nYour selection: ";
				cin >> selection;
				selection = tolower(selection);
				switch(selection){
					case '1':
						cout << "Difficulty set to easy" << endl;
						p1Scoreboard.setDiff(1);
						loop = false;
						break;
					case '2':
						cout << "Difficulty set to medium" << endl;
						p1Scoreboard.setDiff(2);
						loop = false;
						break;
					case '3':
						cout << "Difficulty set to hard" << endl;
						p1Scoreboard.setDiff(3);
						loop = false;
						break;
					default:
						cout << "Please enter a valid response" << endl;
						break;
				}
			}
			*/
			loop = false;
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
	//We clear the screen
	cout << "\033[2J\033[1;1H";
	game(p1, p1Scoreboard, files);
	files.save2File(p1Scoreboard, p1);
	while (!questCompleted.empty())
	{
		cout << questCompleted.front() << endl;
		questCompleted.pop();
	}
	beginning:cout << "OPTION: Would you like to view the scoreboard in alphabetical order?(Y/N)\n";
	char choice;
	cin >> choice;
	switch (choice) {
		case 'n':
			cout << "End of game. Thank you for playing.";
			break;
		case 'y':
			alphabeticalScore(files, p1, p1Scoreboard);
			break;
		default:
			cout << "That wasn't an option!" << endl;
			goto beginning;
	}
}
