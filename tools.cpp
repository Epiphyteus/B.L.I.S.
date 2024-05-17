//Ian Leuty ileuty@pdx.edu May 5 2024 CS162-001

/*This file contains general tools for dealing with arrays of characters. 
These tools are designed to be re-usable with other programs, 
so this file doesn't contain any program specifics and 
may contain functions not to be used in this program */

#include "boxlunch.h"
using namespace std;

//gets an array of characters, uses the some constant size to check length, re-entry
void array_get(char characters[], const int size){
    cin.get(characters, size, '\n');
    while(cin.peek() != '\n'){
        cout << "Please enter less than " << size-1 << " characters." << '>';
        cin.ignore(100, '\n');
        cin.get(characters, size, '\n');
    }
    cin.ignore(100, '\n');
}

//gets and error checks a float entry, ensures not a char, allow re-entry
void get_float(float &number){
    bool again{false};
    do{
        again = false;
        cin >> number;
        cin.ignore(100, '\n');
        if(cin.fail()){
            again = true;
            cout << "You must enter a number. Try again.\n" << '>';
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while(again == true);
}

//gets and checks a character entry to make sure it's 'Y' or 'N', return true if yes.
bool yn(char &yes_no){
    bool again{false};
    bool popular{false};
    do{
        again = false;
        cin >> yes_no;
        cin.ignore(100, '\n');
        if('Y' == toupper(yes_no))
            popular = true; 
        else if('N' == toupper(yes_no));
        else{
            cout << "Please enter 'Y' or 'N'. Try again.\n" << '>';
            again = true;
        }
    }while(again == true);
    return popular;
}


//gets and error checks an int to make sure it's between 1 and 5, allow re-entry
void onefive(int &number){
    bool again{false};
    do{
        again = false;
        cin >> number;
        cin.ignore(100, '\n');
        if(number < 1 || number > 5){
            cout << "Please enter a value between 1 and 5.\n" << '>';
            again = true;
        }
    }while(again == true);
}

//capitalize the first character of every word in a phrase array
void capitalize(char chars[]){
    int length{0}, g{0};
    length = strlen(chars);
    for(g = 0; g < length; g++)
        chars[g] = tolower(chars[g]);
    
    for(g = 0; g < length; g++){
        if(isblank(chars[g]))
            chars[g+1] = toupper(chars[g+1]);  
    }
    chars[0] = toupper(chars[0]);
}

//capitalize all characters in an array
void capitalize_all(char chars[]){
    int length{0}, m{0};
    length = strlen(chars);
    for(m = 0; m < length; ++m)
        chars[m] = toupper(chars[m]);
}

//remove spaces from an array (not yet finished)
void rmspace(char arrayin[], char arrayout[]){
    int q{0}, r{0}, deslen{0};

    deslen = strlen(arrayin);

    for(q = 0; q < deslen; ++q){
        if(!isblank(arrayin[q])){
            arrayout[r] = arrayin[q];
            ++r;
        }
    }
}


//remove punctuation from a word
void rm_punct(char chars[], char new_word[]){
    int len_chars{0};
    int o{0}, k{0};
    len_chars = strlen(chars);

    for(k = 0, o = 0; k <= len_chars; ++k){
        if(ispunct(chars[k]) == false){
            new_word[o] = chars[k]; //similar proccess to separating words
            ++o;
            new_word[o+1] = '\0';
        }
    }
}

//convert a character array to lowercase
//easy, just covert everything one by one
void lower_chars(char chars[]){
    int len_chars{0}, n{0};
    len_chars = strlen(chars);

    for(n = 0; n < len_chars; ++n){
        chars[n] = tolower(chars[n]);
    }
}



//The following were not implemented in this program.


/*clear the screen (may only work on linux w/ g++ compliler)
void clear(){
    cout << "\033[2J\033[1;1H" << endl;
}



//separate the phrase into words base on spaces. returns index position after the found space
//takes a phrase, a starting index, and a blank array to hold the phrase
//pass the value of the supposed index of the next word by refrence
void extract_word(char phrase[], int & start, char pulled[]){
    char word[DESC]; //word array to start working with
    int len_phrase{0}; //length of the phrase
    int len_word{0}; //empty for now length of word
    int space{0}; //index locaton of the space
    int z{0}, u{start}; //separate variable to increment the word array we're pulling in to
                        //'u' grabs the starting index so it can be incremented while preserving that position
    len_phrase = strlen(phrase);
    //this runs the array until it hits a space or terminating character
    if(isblank(phrase[start]) == true)
        ++start;
    for(u = start; !isblank(phrase[u]) && phrase[u] != '\0'; ++u){
        word[z] = phrase[u];
        word[z+1] = '\0'; //always adds teminating character to the next position. overwritten until we hit the end of the word
        ++z;
    }

    len_word = strlen(word);
    start = start + len_word+1; //get the theoretical position of the first char in next word.
                                //might not always be true if extra spaces, still
                                //need to deal with this...
    lower_chars(word);   //lowecasercase the word
    rm_punct(word, pulled);  //remove the punctuation
}


//trial version of an improved matching algo
float percentmatched(char original[], char match[]){
    int o_start{0}, m_start{0}; //positions in the arrays
    int o_len{0}, m_len{0}; //length of the strings
    float match_percent{0}, matches{0}, words{0}; //hold percetage, matches, and words. could cast, but didn't
    char o_word[DESC], m_word[DESC]; //arrays to hold the words pulled
    o_len = strlen(original);
    m_len = strlen(match);

    while(o_start < o_len){ //improved matching algorithm, now allows for phrases of differing lengths, skipped words, etc

        cout << "\nAt indexes: "
             << o_start << ":\n";
  
        //pull one word at a time and check them against one another
        extract_word(original, o_start, o_word); //run the extract functions

        while(m_start < m_len){ //nested loop so first extract player 1's word, then search player 2's sentance for it

            //cout << m_start << ' ';

            extract_word(match, m_start, m_word);

            cout << "Words were: " << o_word << ":" << m_word
                 << endl;  //debugging feature but also cool to show the user UPDATE: removed in final version.
 

            if(strcmp(o_word,m_word) == 0){ //if match increment match counter
                ++matches;
                //cout << "MATCH FOUND" << endl;
            }
        }
        m_start = 0;
        ++ words;
    }
    cout << endl;
    match_percent = ((matches / words) * 100); //calculate and return percent match
    return match_percent;
}

*/

