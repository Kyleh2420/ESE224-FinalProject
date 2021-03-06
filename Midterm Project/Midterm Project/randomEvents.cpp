#include "randomEvents.h"
#include <iostream>
#include <cstdlib> //For srand and rand
#include <string>
using namespace std;



int randomEvents::getLineCount() {
	while (!eventsFile.eof()) {
		eventsFile >> hpChange >> balChange;
		//eventsFile.seekg(1, std::ios_base::cur);
		getline(eventsFile, line);
		lines.push_back(line);
		hpList.push_back(hpChange);
		balList.push_back(balChange);
	}
	line = "";
	//cout << "Line count is: " << lines.size() << endl;
	return lines.size();
}


randomEvents::randomEvents(int floorLevel) {
	//cout << "In randomEvents.cpp, the floor level is: " << floorLevel << endl;
	switch (floorLevel) {
		case 0:
			eventsFileName = "F0RandomEvents.txt";
			//cout << "Opening " << eventsFileName << endl;
			eventsFile.open(eventsFileName);
			if (eventsFile.fail()) {
				cerr << "Error: F0RandomEvents not found." << endl;
				exit(1);
			}
			break;
		case 1:
			eventsFileName = "F1RandomEvents.txt";
			//cout << "Opening " << eventsFileName << endl;
			eventsFile.open(eventsFileName);
			if (eventsFile.fail()) {
				cerr << "Error: F1RandomEvents not found." << endl;
				exit(1);
			}
			break;
		case 2:
			eventsFileName = "F2RandomEvents.txt";
			//cout << "Opening " << eventsFileName << endl;
			eventsFile.open(eventsFileName);
			if (eventsFile.fail()) {
				cerr << "Error: F2RandomEvents not found." << endl;
				exit(1);
			}
			break;
		case 3:
			eventsFileName = "F3RandomEvents.txt";
			//cout << "Opening " << eventsFileName << endl;
			eventsFile.open(eventsFileName);
			if (eventsFile.fail()) {
				cerr << "Error: F3RandomEvents not found." << endl;
				exit(1);
			}
			break;
		default:
			cout << "Well that wasn't supposed to happen. We couldn't find that floor!" << endl;
			break;
		}
		//Once we select the file, push everything back into a vector
		getLineCount();
}



//The following should return a random line from the file choosen
string randomEvents::getEvent() {
	//This is Kyle's attempt at generating a random line from the file chosen. It does not work.
	/*
	srand(time(0));
	for (int i = 0; i < (rand() % lineCount)-1; i++) {
		getline(eventsFile, line);
		cout << "Unused Line: " << line << endl;
	}
	cout << eventsFileName << endl;
	*/

	return lines[selector];
}

int randomEvents::getHPChange() {
	return hpList[selector];
}
int randomEvents::getBalChange() {
	return balList[selector];
}

void randomEvents::getRandom() {
	srand(time(0));
	selector = rand() % lines.size();
}