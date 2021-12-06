#include <iostream>
#include <string.h>
using namespace std;

class scoreboard {
private:
    //Score of the player. Score should increase after the player defeats an enemy or through some custom meathod designed by you
    //Note: Higher level enemies should give more points
    int sbScore;
    int sbDifficulty;
    //Difficulty of the game
    //Keeps track of the area in the game wich the player is at 
    int sbFloor;
    //Keeps track of what position on the floor the player is at
    int sbPos;
    //Bonus points for side quests
    int sbBonus;

    string sbName;
public:
    //Default constructor
    scoreboard();

    //Setters!
    void setScore(int input);
    void setDiff(int input);
    void setFloor(int input);
    void setPos(int input);
    void setBonus(int input);
    void setName(string input);

    //Getters!
    int getScore();
    int getDiff();
    int getFloor();
    int getPos();
    int getBonus();
    int getTotal();
    string getName();

    bool operator == (const scoreboard& s) const;
    bool operator < (const scoreboard& s) const;
    bool operator() (const scoreboard& p1, const scoreboard& p2) const;

    void addScore(int input);
    void addBonus(int input);

    //Print scoreboard
    void sbOut();

    friend ostream& operator <<(ostream& os, const scoreboard& s);
};