//Ian Leuty CS162 May 3 2024 ileuty@pdx.edu
/*This program is designed to read in and store up to 20 items of collectible 
merchandise. It will accomplish this using several functions, and will also feature
a menu to allow the user to navigate the options. The sub-tasks involved in this project 
are: 
1. Reading in user input of items and storing them in a structure 
consisting of: 
    a. The name of the item (array, 51 characters) 
    b. The "universe" it is from (array, 51 characters)
    c. A brief description (array, 151 characters)
    d. Price (float) 
    e. The colors of the item (array 51 characters)
    f. The star rating of the item (int)
    g. 
2. Menu navigation consisting of:
    a. Read in an item
    b. Search for an item
    c. Display all items
    d. Quit
3. Load and save functions that will allow the use to read out to and in from a file
4. Functions:   
    a. read in from file 
    b. output to file
    c. display all
    d. search and display match
    e. read in from user an item
    f. read in from user items
    g. general array getting function
    h. general integer getting function
*/


#include <iostream>
#include <iomanip> //for float output manipulation
#include <cctype>
#include <cstring>
#include <fstream>
#include <cmath>


const int DESC{151};
const int NAME{51};
const int ITEMS{20};

//struct to hold all the information about an item in BoxLunch's inventory
struct lunch{
    char item[NAME];
    char describe[DESC]; //brief 150 character description of the item.
    char verse[NAME]; //Fictional character universe(i.e. Star Wars, D.C., Marvel, Halo, etc. )
    float price{0.00};
    char colors[DESC];
    char popular{}; //Yes or no, when getting this input, a markup can be applied if popular
    int condition{0}; //1-5 condition rating for re-selling

};

//User functions (found in user.cpp)
void welcome();
bool menu(lunch inventory[], int &item_num);

//Program Specific Functions (found in machines.cpp)
void get_item(lunch &one_item, lunch inventory[], int &item_num);
void get_items(lunch inventory[], int &item_num);
void display_item(lunch &one_item);
void search(lunch inventory[], int &item_num);
void display_all(lunch inventory[], int &item_num);
void alpha_sort(lunch inventory[], int &item_num);
bool binary_search(lunch inventory[], int &end, char target[], int &target_index);
void save(lunch inventory[], int &num_items);
void load(lunch inventory[], int &num_items);

//Tools (found in tools.cpp)
void clear();
void array_get(char characters[], const int size);
void lower_chars(char chars[]);
void rm_punct(char chars[], char new_word[]);
void capitalize(char chars[]);
void capitalize_all(char chars[]);
void rmspace(char arrayin[], char arrayout[]);
void get_float(float &number);
bool yn(char &yes_no);
void onefive(int &number);

