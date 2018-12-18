//Filename: prog1.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "galaxy.h"



//Constants
const char FILENAME[] = "galaxy.txt";



//Prototypes
void display_menu(char & choice);   //Displays textbased menu and reads user choice
void get_data(char * & dest);       //Gets data from the user and sizes

                                    //the argument array just right

//main function
int main()
{
    char menu_choice = 'a';  //user choice for menu operation
    int result = 0;          //Value returned by member function

    char name1[] = "Earth";
    char name2[] = "Jupiter";
    char name3[] = "Mars";
    char name4[] = "Uranus";
    char sun1[] = "Sun";

    terr_planet A(name1, sun1);
    gas_planet B(name2, sun1);
    planet * C_ptr;
    planet * D_ptr;
    solar_system SS1(sun1);
    galaxy milky_way(2);

    //Load file
    int num_loaded = milky_way.load_file(FILENAME);
    cout << num_loaded << " solar systems loaded from file" << endl;

    //Display galaxy
    int plan = milky_way.display_all();
    cout << plan << " planets total!" << endl << endl;  
    int hab = milky_way.display_all_hab_planets();
    cout << hab << " planets habitable total!" << endl << endl;  

    return 0;
}



//Display menu and get user choice
//INPUT: 1 argument: user choice (char array passed by reference)
//OUTPUT: Argument userchoice modified
void display_menu(char & choice)
{
    //Repeat until user chooses a valid menu option
    do
    {
        //Display menu of operations to user
        cout << "\n\nSelect operation:" << endl;
        cout << "a. Load galaxy from file" << endl
             << "b. Display galaxy" << endl
             << "c. Display all unvisited solar systems" << endl
             << "d. Display all habitable planets" << endl
             << "h. Quit" << endl
             << "Enter a letter from 'a' to 'h': ";

        //Read in user response
        cin >> choice;
        cin.ignore(100, '\n');

        //Convert to lowercase
        choice = tolower(choice);
        
        //If choice is invalid, prompt user
        if (!(choice >= 'a' && choice <= 'h'))
            cout << "\n\n***Invalid entry! Try again...***" << endl;
    }
    while (!(choice >= 'a' && choice <= 'h'));

    return;
}



//Gets data from the user and sizes the argument array just right
//INPUT: 1 argument: a char pointer passed by reference
//OUTPUT: modified argument array, return nothing
void get_data(char * & dest)
{
    char temp [100];    //Temporary array to read in data and size
                        //argument array just right

    //Read in data from user into temp
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');

    //Allocate memory sized just right, based on contents of temp
    dest = new char [strlen(temp) + 1];

    //Copy data from temp
    strcpy(dest, temp);

    return;
}
