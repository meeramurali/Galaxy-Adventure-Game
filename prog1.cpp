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
    int num_loaded = 0;
    int total_planets = 0;
    int total_sol_sys = 0;
    int total_hab = 0;
    int result = 0;          //Value returned by member function

    galaxy milky_way(2);

    //Repeat until user wants to quit, i.e. menu choice is 'd'
    do 
    {  
        //Display menu and get user choice 
        display_menu(menu_choice);
        
        //If choice is 'a', load data from file
        //Prompt user accordingly based on result
        if (menu_choice == 'a')
        {
            //Load file
            num_loaded = milky_way.load_file(FILENAME);
            if (num_loaded)
                cout << "\n*** " << num_loaded << " solar system(s) loaded from file: " 
                     << FILENAME << " ***" <<  endl;
            else
                cout << "\n*** File not found! ***" << endl;
        } 
        
        //If choice is 'b', display all solar systems
        //Prompt user accordingly based on result
        else if (menu_choice == 'b')
        {
            //Display all solar systems
            total_planets = milky_way.display_all(total_sol_sys);
            cout << endl << total_sol_sys << " solar systems!";  
            cout << endl << total_planets << " planets total!" << endl << endl;  
        }
        
        //If choice is 'c', display all habitable planets
        //Prompt user accordingly based on result
        else if (menu_choice == 'c')
        {
            //Display all habitable planets
            total_hab = milky_way.display_all_hab_planets();
            cout << endl << total_hab << " habitable planets total!" << endl << endl;  
        }
    }
    while (menu_choice != 'd'); //Stop if choice is 'd'

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
             << "c. Display all habitable planets" << endl
             << "d. Quit" << endl
             << "Enter a letter from 'a' to 'd': ";

        //Read in user response
        cin >> choice;
        cin.ignore(100, '\n');

        //Convert to lowercase
        choice = tolower(choice);
        
        //If choice is invalid, prompt user
        if (!(choice >= 'a' && choice <= 'd'))
            cout << "\n\n***Invalid entry! Try again...***" << endl;
    }
    while (!(choice >= 'a' && choice <= 'd'));

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
