#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
class Blob {
    //friends
    friend void operator+(Blob&, Blob&);
    friend ostream& operator<<(ostream&, Blob);
    private:
        int Health;
        int Power;
        char Color;
        int xCoord;
        int yCoord;
        bool isAlive;
    public:
        Blob();
        Blob(int);
        Blob(int, int);
        Blob(int, int, int);
        Blob(int, int, int, int);
        Blob(int, int, int, int, char);
        //getters
        int GetXCoord();
        int GetYCoord();
        int GetHealth();
        int GetPower();
        char GetTeam();
        bool GetState();
        //setters
        void SetTeam(char);
        void SetNewCoords();
        void SetXCoord(int);
        void SetYCoord(int);
        void SetPower(int);
        //other
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        int isOccupied(Blob[], int, int);
        bool isFriendly(char, Blob);
        void printBlobs(Blob[]);
        bool canAttack(Blob, Blob);
        void attack(Blob&);
};