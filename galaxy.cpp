//Filename: galaxy.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "galaxy.h"



//Default constructor - initializes all data members to null
//INPUT: no arguments
//OUTPUT: no return value
solar_system::solar_system(): sun(NULL), head(NULL), tail(NULL) {}



//Constructor with argument
//INPUT: 1 argument: name of sun
//OUTPUT: no return value
solar_system::solar_system(char * sun_name)
{
    //Copy argument sun name
    if (sun_name)
    {
        sun = new char [strlen(sun_name) + 1];
        strcpy(sun, sun_name);
    }

    else
        sun = NULL;

    //Initialize head and tail to NULL
    head = tail = NULL;
}



solar_system::solar_system(const solar_system & to_copy)
{
    //Copy sun from argument object
    if (to_copy.sun)
    {
        sun = new char [strlen(to_copy.sun) + 1];
        strcpy(sun, to_copy.sun);
    }

    else
        sun = NULL;

    //Copy DLL
}



//Destructor - release all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
solar_system::~solar_system()
{
    //Release memory for sun name
    if (sun)
    {
        delete [] sun;
        sun = NULL;
    }

    //Remove all planets
    if (remove_all(head))
        tail = NULL; 
}



//Removes all nodes in dll - recursive
//INPUT: 1 argument: head pointer to DLL
//OUTPUT: return type: int (number of nodes removed)
int solar_system::remove_all(planet * & head)
{
    int removed = 0;

    //Base case
    if (!head)
        return 0;

    //Recursive call to next node
    removed += remove_all(head->go_next());

    //Delete head
    delete head;
    head = NULL;

    return ++removed;
}    

