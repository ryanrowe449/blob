#include "blob.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
//constructors
Blob::Blob(){
    xCoord = rand() % 10 + 1;
    yCoord = rand() % 10 + 1;
    Health = 100;
    Color = 'B';
    Power = 10;
    isAlive = true;
}
 
Blob::Blob(int x){
    xCoord = x;
    yCoord = rand() % 10 + 1;
    Health = 100;
    Color = 'B';
    Power = 10;
    isAlive = true;
}
 
Blob::Blob(int x, int y){
    xCoord = x;
    yCoord = y;
    Health = 100;
    Power = 10;
    Color = 'B';
    isAlive = true;
}
 
Blob::Blob(int x, int y, int hp){
    xCoord = x;
    yCoord = y;
    Health = hp;
    Power = 10;
    Color = 'B';
    isAlive = true;
}
 
Blob::Blob(int x, int y, int hp, int p){
    xCoord = x;
    yCoord = y;
    Health = hp;
    Power = p;
    Color = 'B';
    isAlive = true;
}
 
Blob::Blob(int x, int y, int hp, int p, char team){
    xCoord = x;
    yCoord = y;
    Health = hp;
    Power = p;
    Color = team;
    isAlive = true;
}
 
//getters
int Blob::GetXCoord(){
    return xCoord;
}
 
int Blob::GetYCoord(){
    return yCoord;
}
 
int Blob::GetHealth(){
    return Health;
}
 
int Blob::GetPower(){
    return Power;
}
 
char Blob::GetTeam(){
    return Color;
}
 
bool Blob::GetState(){
    return isAlive;
}
 
//setters
void Blob::SetTeam(char t){
    Color = t;
}
 
void Blob::SetNewCoords(){
    xCoord = rand() % 10 + 1;
    yCoord = rand() % 10 + 1;
}
 
void Blob::SetXCoord(int x){
    xCoord = x;
}
 
void Blob::SetYCoord(int y){
    yCoord = y;
}

void Blob::SetPower(int p){
    Power = p;
}
 
//other
void Blob::MoveUp(){
    yCoord++;
}
 
void Blob::MoveDown(){
    yCoord--;
}
 
void Blob::MoveLeft(){
    xCoord--;
}
 
void Blob::MoveRight(){
    xCoord++;
}
 
int Blob::isOccupied(Blob blobs[], int x, int y){
    for (int i = 0; i < 8; i++){
        if (blobs[i].GetState() == true && blobs[i].GetXCoord() == x && blobs[i].GetYCoord() == y){
            return i;
        }
    }
    return -1;
}
 
bool Blob::isFriendly(char team, Blob blob){
    if (blob.GetTeam() == team){
        return true;
    }
    else return false;
}
 
void Blob::printBlobs(Blob blobs[]){
    //int size = sizeof(blobs);
    cout << "Team Blue\n";
    for (int i = 0; i < 4; i++){
        cout << "Blob " << i + 1 << ": " <<  blobs[i];
    }
    cout << "Team Red\n";
    for (int i = 4; i < 8; i++){
        cout << "Blob " << i + 1 << ": " <<  blobs[i];
    }
}
 
bool Blob::canAttack(Blob aggressor, Blob defender){
    int y = aggressor.GetYCoord() - defender.GetYCoord();
    int x = aggressor.GetXCoord() - defender.GetXCoord();
    if (aggressor.GetTeam() != defender.GetTeam()){
        if (aggressor.GetXCoord() == defender.GetXCoord()){
            if (y == 1 || y == -1) return true;
        }
        if (aggressor.GetYCoord() == defender.GetYCoord()){
            if (x == 1 || x == -1) return true;
        }
    }
    return false;
}
 
void Blob::attack(Blob& target){
    target.Health -= Power;
    if (target.Health <= 0){
        target.isAlive = false;
    }
}
 
//friends
//change the + operator to use DMA
void operator+(Blob& x, Blob& y){
    if (x.Power > y.Power){
        x.Power += 2;
        x.Health += y.Health;
        y.isAlive = false;
    }
    else{
        y.Power += 2;
        y.Health += x.Health;
        x.isAlive = false;
    }
}
 
ostream& operator<<(ostream& o, Blob x){
    if (x.isAlive == true){
        o << "(" << x.GetXCoord() << ", " << x.GetYCoord() << "): team " << x.GetTeam() << ", health " << x.GetHealth() << ", power " << x.GetPower() << endl;
    }
    else o << "dead" << endl;
    return o;
}