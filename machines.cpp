//Ian Leuty ileuty@pdx.edu May 5 2024 CS162-001

/*This file contains all of the program-specific functions like displaying the stuct, 
searching the list, and getting user entry, etc.
*/

#include "boxlunch.h" 

using namespace std;

/*Function to get user entery, uses the more general array_get to perform error checking and has error 
checking for the float and int members of the struct.*/
void get_items(lunch inventory[], int &index){
    char another{'\0'};
    do{
        get_item(inventory[index], inventory, index);
        ++index;
        cout << "\nEnter another item?\n" << '>';
        cin >> another; 
        cin.ignore(100, '\n');
    }while('Y' == toupper(another));    
}


/*gets the info about one item, storing into a struct in the array. 
calls other functions for error checking:
    -formating name (no punctuation, same case)
    -length of entries
    -yes/no
    -enter only 1-5
    -duplicates already exist?

Inventory array also has to be passed in to check for duplicates.
*/
void get_item(lunch &one_item, lunch inventory[], int &item_num){
    char temp[NAME];
    int target_index{0};
    cout << "\nEnter the item name.\n" << '>';
    array_get(temp, NAME);
    rm_punct(temp, one_item.item);
    capitalize_all(one_item.item); //ensure consistent name format
    //search exiting inventory for a duplicate, prevent user from entering
    while(binary_search(inventory, item_num, one_item.item, target_index)){
        cout << "\nThat item already exists! Enter something different.\n" << '>';
        array_get(temp, NAME);
        rm_punct(temp, one_item.item);
        capitalize_all(one_item.item);
    }
    cout << "\nEnter a brief description of the item.\n" << '>';
    array_get(one_item.describe, DESC); //description
    cout << "\nEnter the fictional universe the item is from (i.e. Marvel, D.C.)\n" << '>';
    array_get(one_item.verse, NAME); //(marvel/D.C./other)
    cout << "\nEnter the price of the item in dollars and cents (i.e. 35.99)\n" << ">$";
    get_float(one_item.price); //price
    cout << "\nEnter the main colors of the item.\n" << '>';
    array_get(one_item.colors, DESC); //colors
    cout << "\nIf the item is in demand/popular, do you want to markup the price 10%? (y/n)\n" 
         << '>'; 
    if(yn(one_item.popular)) //markup if popular, yn gets and checks y/n input
        one_item.price = one_item.price * 1.10;

    cout << "\nEnter a rating of the condition of the item (1-5).\n" 
         << "1. Used, Poor\n"
         << "2. Used, Fair\n"
         << "3. Used, Good\n" 
         << "4. New, Open Package/No Tags\n"
         << "5. New, in Package/With Tags\n"
         << '>';
    onefive(one_item.condition); //condition, 1-5. onefive error checks 
}



//outputs a the info for one item from the lunch struct
//set precision used to format price 
void display_item(lunch &item){
    cout << item.item << endl 
         << "Description: " << item.describe << endl
         << "Fictional Universe: " << item.verse << endl 
         << "Price: $" << setprecision(2) << fixed << item.price << endl 
         << "Colors: " << item.colors << endl
         << "Adjusted for Demand (y/n): " << item.popular << endl
         << "Condition: ";
    switch(item.condition){ //Translate the 1-5 condition into a condition description.
        case 1:
            cout << "Used, Poor";
            break;
        case 2:
            cout << "Used, Fair";
            break;
        case 3: 
            cout << "Used, Good";
            break;
        case 4:
            cout << "New, Open Package";
            break;
        case 5:
            cout << "New, in Packaging";
            break;
    }
    cout << endl;
    
}

/*calls the display item function for the array of lunch structs as long as there are items to display
uses the item_num int variable to keep track of items in the system to display.*/
void display_all(lunch inventory[], int &num_items){
    int i{0};
    for(i = 0; i < num_items; ++i)
        alpha_sort(inventory, num_items); //always sort before displaying
    for(i = 0; i < num_items; ++i){
        cout << "\nItem: " << i + 1 << endl;
        display_item(inventory[i]);
    }
}



//uses insertion sorting to alphabetize the array of structs based on the 'item' member
void alpha_sort(lunch inventory[], int &item_num){
    int i{1};
    lunch temp;
    while(i < item_num){
        temp = inventory[i]; //put item at [i] into temp struct
        while(strcmp(inventory[i-1].item, inventory[i].item) > 0){
            inventory[i] = inventory[i-1]; //while prev. should be lower, move i-1 'down' 1
        }
        if(strcmp(temp.item, inventory[i-1].item) < 0) //if temp should be higher, move 'up' 1
            inventory[i-1] = temp; 
        ++i; //increment i
    } 
}



/* allows user to enter a search term. relies on the alpha sort function and binary search 
function to find structs which have a matchine name member. */
void search(lunch inventory[], int &item_num){
    char target[NAME];
    //int start{0};
    char edit{'\0'};
    int target_index{0};
    int i{0};
    for(i = 0; i <= item_num; ++i) //sort the list as many times as there are items
        alpha_sort(inventory, item_num); //ensure sorted
    cout << "Enter an item to search for.\n" << '>'; //get the item name to search for
    cin.get(target, NAME, '\n');
    cin.ignore(100, '\n');
    capitalize_all(target); //match case
    if(binary_search(inventory, item_num, target, target_index)){
        cout << "\nDo you want to edit this item?\n" << '>';
        yn(edit);
        cout << edit;
        if(toupper(edit) == 'Y')
            get_item(inventory[target_index], inventory, item_num); //enter changes if desired
    }
    else
        cout << "\nItem not in inventory." << endl;
}

/*binary search function looks though the list for matching item by
picking a test midpoint, comparing with the target.
If there is a match, inform user, return true. If not, return false. 
pass target index by reference so item can be changed if desired.
relies upon the list being in alphabetical order. Which is taken care of before this is called. 
*/
bool binary_search(lunch inventory[], int &item_num, char target[], int &target_index){
    bool match{false};
    int start{0};
    int test{0}; 
    int end{0};
    end = item_num;
    while(start <= end && match == false){ //loop while start doesn't exceed end
        test = start + (end - start) / 2; //split the list - add (last-first) / 2 to start index
        if(strcmp(target, inventory[test].item) == 0){ //target is test
            target_index = test;
            cout << "\nItem Found!" << endl;
            display_item(inventory[test]);
            match = true;
        }
        if(strcmp(target, inventory[test].item) > 0){ //target is lower down the list than test
            start = test + 1;
        } 
        if(strcmp(target, inventory[test].item) < 0){ //target is heigher up the list
            end = test -1;
        }
    }
    return match; 
}



//This was an experiment using recursion, but I decided it was too soon to try this

/*void binary_search(lunch inventory[], int &end, int &start, char target[]){
    int test{0};
    test = (end+1)/2;
    if(//need a condition to ensure loop end!!!)
        cout << "No matches found\n" << endl;
    else{
        if(strcmp(target, inventory[test].item) == 0){
            cout << "\nMatch Found!" << endl;
            display_item(inventory[test]);
        }

        else if(strcmp(target, inventory[test].item) > 0){
            ++test;
            binary_search(inventory, end, test, target);
        }

        else(strcmp(target, inventory[test].item) < 0){
            --test;
            binary_search(inventory, test, start, target);
        }
    }
}
*/

