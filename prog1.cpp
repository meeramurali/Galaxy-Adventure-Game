//Filename: prog1.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "galaxy.h"


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

    //Display planets
    cout << "\n\nTerrestrial planet: " << endl;
    if (!A.display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << A.allow_landing() << endl;
    if (A.check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    cout << "\n\nGas planet: " << endl;
    if (!B.display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << B.allow_landing() << endl;
    if (B.check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    C_ptr = new terr_planet(name3, sun1);
    D_ptr = new gas_planet(name4, sun1); 

    //Display planets
    cout << "\n\nTerrestrial planet: " << endl;
    if (!C_ptr->display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << C_ptr->allow_landing() << endl;
    if (C_ptr->check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    cout << "\n\nGas planet: " << endl;
    if (!D_ptr->display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << D_ptr->allow_landing() << endl;
    if (D_ptr->check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;


    delete C_ptr;
    delete D_ptr;

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
