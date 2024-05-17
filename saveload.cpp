//Ian Leuty ileuty@pdx.edu May 5 2024 CS162-001
//This fle contains the necessary functions to save out to and load in from an external inventory file

#include "boxlunch.h"
using namespace std;

/*load in function. uses same arguments as the save out
recognizes the same delimiters in order to put the item info in the proper index and member.*/
void load(lunch inventory[], int &num_items){
    int i{0};
    char temp[NAME]; //temp array used to run formatting functions
    ifstream filein; //read in from file var
    filein.open("product.txt");
    if(filein){ //check for file
        filein.get(temp, NAME, '|');
        filein.ignore(100, '|');
        while(!filein.eof() && i < ITEMS){
            //formatting functions prepare list to be searched 
            rm_punct(temp, inventory[i].item);
            capitalize_all(inventory[i].item);

            filein.get(inventory[i].describe, DESC, '|');
            filein.ignore(100, '|');
            filein.get(inventory[i].verse, NAME, '|');
            filein.ignore(100, '|');
            filein >> inventory[i].price;
            filein.ignore(100, '|');
            filein.get(inventory[i].colors, DESC, '|');
            filein.ignore(100, '|');
            filein >> inventory[i].popular;
            filein.ignore(100,'|');
            if('Y' == toupper(inventory[i].popular)) //adjust price if specified
                inventory[i].price = inventory[i].price * 1.10;
            filein >> inventory[i].condition;
            filein.ignore(100, '\n');
            ++i;
            num_items = i; //adjust item tracker so we can add, search, display correctly
            filein.get(temp, NAME, '|'); //prime pump
            filein.ignore(100, '|');
        }
    filein.close(); //close the file
    }
    else 
        cout << "\nFile could not be found, but will be created upon exit." << endl;
}

/*save out function, uses the struct array and the item number counter as arguments. 
Inserts delimiters and new lines between items */
void save(lunch inventory[], int &num_items){
    int i{0};
    ofstream fileout; //output to file var
    fileout.open("product.txt");
    if(fileout){
        for(i = 0; i < num_items; ++i){
            if('Y' == toupper(inventory[i].popular))
                inventory[i].popular = 'A'; //if price was already adjusted, designate 'A'
            fileout << inventory[i].item << '|'
                    << inventory[i].describe << '|'
                    << inventory[i].verse << '|'
                    //ensure correct decimal format
                    << setprecision(2) << fixed << inventory[i].price << '|'
                    << inventory[i].colors << '|'
                    << inventory[i].popular << '|'
                    << inventory[i].condition << endl;
        }
        fileout.close();
    }
    else
        cout << "\nFile could not be found." << endl;
}

