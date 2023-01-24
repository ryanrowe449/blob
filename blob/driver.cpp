#include "blob.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
 
int main(){
    Blob blobs[8];
    //setting blobs 4-7 to team red
    for (int i = 4; i < 8; i++){
        blobs[i].SetTeam('R');
    }
 
    //checking to see if there are any blobs on the same coordinate
    for (int i = 0; i < 7; i++){
        int j = i + 1;
        while (j < 8){
            while (blobs[i].GetXCoord() == blobs[j].GetXCoord() && blobs[i].GetYCoord() == blobs[j].GetYCoord()){
                blobs[j].SetNewCoords();
            }
            j++;
        }
    }

    //printing the blob information
    blobs[0].printBlobs(blobs);

   //the game begins
   Blob * blobPointer;
   int dead = 0;
   int deadRed = 0;
   int blobnum;
   int target;
   int num;
   char direction;
   bool blueTurn = true;
   int occupy;
   while (dead < 4 && deadRed < 4){
    if (blueTurn){
        cout << "Team blue is up. Enter the number of the blob you'd like to use.\nIf you want to see the gameboard, enter a number out of range (e.g -1)\n";
        cin >> blobnum;
        while (blobnum < 1 || blobnum > 8){
            blobs[0].printBlobs(blobs);
            cout << "Enter the number of the blob you'd like to use.\nIf you want to see the gameboard, enter a number out of range (e.g -1)\n";
            cin >> blobnum;
        }
        //checking to see if the blob selected is valid
        if (blobs[blobnum - 1].GetState() == false){
            cout << "That blob is dead. Pick a different one\n";
            cin >> blobnum;
            while (blobs[blobnum - 1].GetState() == false){
                cout << "That blob is dead. Pick a different one\n";
                cin >> blobnum;
            }
        }
        if (blobs[blobnum - 1].GetTeam() == 'R'){
            cout << "That blob is not on your team. Pick one on team B\n";
            cin >> blobnum;
            while (blobs[blobnum - 1].GetTeam() == 'R'){
                cout << "That blob is not on your team. Pick one on team B\n";
                cin >> blobnum;
            }
        }
        //move or attack
        cout << "Enter 0 to move or 1 to attack\n";
        cin >> num;
        while (num != 0 && num != 1){
            cout << "Invalid input. Enter 0 to move or 1 to attack\n";
            cin >> num;
        }
        //move
        if (num == 0){
            cout << "Enter 'N' for north, 'E' for east, 'S' for south, or 'W' for west\n";
            cin >> direction;
            if (direction == 'N' || direction == 'n'){
                if (blobs[blobnum - 1].GetYCoord() != 10){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord(), blobs[blobnum-1].GetYCoord() + 1);
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'R'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveUp();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveUp();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = false;
            }
            if (direction == 'E' || direction == 'e'){
                if (blobs[blobnum - 1].GetXCoord() != 10){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord() + 1, blobs[blobnum-1].GetYCoord());
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'R'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveUp();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveRight();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = false;
            }
            if (direction == 'S' || direction == 's'){
                if (blobs[blobnum - 1].GetYCoord() != 0){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord(), blobs[blobnum-1].GetYCoord() - 1);
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'R'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveDown();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveDown();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = false;
            }
             if (direction == 'W' || direction == 'w'){
                if (blobs[blobnum - 1].GetXCoord() != 0){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord() - 1, blobs[blobnum-1].GetYCoord());
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'R'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveLeft();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveLeft();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = false;
            }
        }
        else {
            cout << "Which blob would you like to attack?\nThe target blob must be:\n\t1. Alive\n\t2. On the opposite team\n\t3. Within one space of your blob, but not diagonally\n";
            cin >> target;
            if (blobs[target-1].canAttack(blobs[blobnum-1], blobs[target-1])){
                blobPointer = &blobs[blobnum-1];
                blobPointer->attack(blobs[target-1]);
                if (blobs[target-1].GetHealth() <= 0){
                    dead++;
                }
                else blueTurn = false;
            }
            else {
                cout << "You failed haha. Your turn is over\n";
                blueTurn = false;
            }
        }
    }
    else {
        cout << "Team red is up. Enter the number of the blob you'd like to use.\nIf you want to see the gameboard, enter a number out of range (e.g -1)\n";
        cin >> blobnum;
        while (blobnum < 1 || blobnum > 8){
            blobs[0].printBlobs(blobs);
            cout << "Enter the number of the blob you'd like to use.\nIf you want to see the gameboard, enter a number out of range (e.g -1)\n";
            cin >> blobnum;
        }
        //checking to see if the blob selected is valid
        if (blobs[blobnum - 1].GetState() == false){
            cout << "That blob is dead. Pick a different one\n";
            cin >> blobnum;
            while (blobs[blobnum - 1].GetState() == false){
                cout << "That blob is dead. Pick a different one\n";
                cin >> blobnum;
            }
        }
        if (blobs[blobnum - 1].GetTeam() == 'B'){
            cout << "That blob is not on your team. Pick one on team R\n";
            cin >> blobnum;
            while (blobs[blobnum - 1].GetTeam() == 'B'){
                cout << "That blob is not on your team. Pick one on team R\n";
                cin >> blobnum;
            }
        }
        //move or attack
        cout << "Enter 0 to move or 1 to attack\n";
        cin >> num;
        while (num != 0 && num != 1){
            cout << "Invalid input. Enter 0 to move or 1 to attack\n";
            cin >> num;
        }
        //move
        if (num == 0){
            cout << "Enter 'N' for north, 'E' for east, 'S' for south, or 'W' for west\n";
            cin >> direction;
            if (direction == 'N' || direction == 'n'){
                if (blobs[blobnum - 1].GetYCoord() != 10){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord(), blobs[blobnum-1].GetYCoord() + 1);
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'B'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveUp();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveUp();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = true;
            }
            if (direction == 'E' || direction == 'e'){
                if (blobs[blobnum - 1].GetXCoord() != 10){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord() + 1, blobs[blobnum-1].GetYCoord());
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'B'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveUp();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveRight();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = true;
            }
            if (direction == 'S' || direction == 's'){
                if (blobs[blobnum - 1].GetYCoord() != 0){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord(), blobs[blobnum-1].GetYCoord() - 1);
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'B'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveDown();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveDown();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = true;
            }
             if (direction == 'W' || direction == 'w'){
                if (blobs[blobnum - 1].GetXCoord() != 0){
                    occupy = blobs[blobnum-1].isOccupied(blobs, blobs[blobnum-1].GetXCoord() - 1, blobs[blobnum-1].GetYCoord());
                    if (occupy != -1){
                        if (blobs[occupy].GetTeam() == 'B'){
                            cout << "You just bumped into an enemy blob! It's team Red's turn now!\n";
                        }
                        else{
                            blobs[occupy] + blobs[blobnum-1];
                            blobs[blobnum-1].MoveLeft();
                        }
                    }
                    else{
                        blobs[blobnum-1].MoveLeft();
                    }
                }
                else{
                    cout << "Ehhhh you can't go there. You have lost your turn\n";
                }
                blueTurn = true;
            }
        }
        else {
            cout << "Which blob would you like to attack?\nThe target blob must be:\n\t1. Alive\n\t2. On the opposite team\n\t3. Within one space of your blob, but not diagonally\n";
            cin >> target;
            if (blobs[target-1].canAttack(blobs[blobnum-1], blobs[target-1])){
                blobPointer = &blobs[blobnum-1];
                blobPointer->attack(blobs[target-1]);
                if (blobs[target-1].GetHealth() <= 0){
                    deadRed++;
                }
                else blueTurn = true;
            }
            else {
                cout << "You failed haha. Your turn is over\n";
                blueTurn = true;
            }
        }
    }
   }
   if (dead == 4){
    cout << "Blue team wins! Thank you for playing\n";
   }
   else {
    cout << "Red team wins! Thank you for playing\n";
   }
}