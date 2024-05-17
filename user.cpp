//Ian Leuty ileuty@pdx.edu May 5 2024 CS162-001
/*This file contains the functions for the lunchbox inventory program that are used to interact with the user 
and improve the expereince of the user. These include welcome messages, and a menu. */

#include "boxlunch.h"
using namespace std;

//display a welcome message to the user and explain the rules of the game. 
void welcome(){
    cout << "Box Lunch Inventory System (B.L.I.S.) initialized!\n\n"
         << "This software is designed to perform basic inventory tracking for "
         << "up to twenty items. An item in the inventory system consists of "
         << "the item's name, description, character universe, price, colors, rating "
         << "and condition.\n" << endl;
}

/*display a menu of the program's capabilities 
allow the user to make a selection and excecute the desired proccess by making 
a call to the function(s)
Retrun false if user chooses to quit, so that menu can be offered in a loop from main.
*/
bool menu(lunch inventory[], int &item_num){
    char choice{'\0'};
    bool repeat{true};
    cout << "\nChoose from the following options by entering the first letter:\n\n"
         << "-(E)nter a new item\n"
         << "-(S)earch for an item by name\n"
         << "-(D)isplay all items in the inventory\n"
         << "-(Q)uit\n\n" << '>';
    cin >> choice;
    cin.ignore(100, '\n');

        if('E' == toupper(choice)){ //Enter an item
            get_items(inventory, item_num); //call get item
        }
        else if('S' == toupper(choice)){ //Search for an item
            search(inventory, item_num); //call search 
        }
        else if('D' == toupper(choice)){ //Display All
            display_all(inventory, item_num); //call display all
        }
        else if('Q' == toupper(choice)){ //Quit
            cout << "Goodbye." << endl;
            repeat = false;
        }
        else{ //Re-prompt for correct choice
            cout << "Please make a valid selection ('E', 'S', 'D', or 'Q')\n" << endl;
        } 
    return repeat;
}


