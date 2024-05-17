//Ian Leuty ileuty@pdx.edu May 5 2024 CS162-001
//This file contains the main calling routine for the lunchbox inventory system program

#include "boxlunch.h"

using namespace std;


//Main calling routine
int main(){
    int item_num{0}; //tracks, counts, and passes number of idexes used
    lunch inv[ITEMS]; //inventory struct of type lunch

    load(inv, item_num); //load in from external file first
    welcome(); //welcome the user and explain the program
    while(menu(inv, item_num)); //null loop just runs the menu until quit returns false
    save(inv, item_num); //save if user chooses to quit

    return 0;
}
