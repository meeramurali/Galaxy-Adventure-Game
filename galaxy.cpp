//Filename: galaxy.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "galaxy.h"



//Default constructor
//INPUT: no arguments
//OUTPUT: no return value
node::node(): a_planet(NULL), next(NULL), prev(NULL) {}



//Constructor with a planet object as argument
//INPUT: 1 argument: a planet object
//OUTPUT: no return value
node::node(planet * to_copy)
{
    //Check if planet to copy is terrestrial or gas
    if (to_copy)
    {
        if (to_copy->allow_landing())
            a_planet = new terr_planet(to_copy);

        else 
            a_planet = new gas_planet(to_copy);
    }

    else
        a_planet = NULL;

    //Initialize next pointer
    next = NULL;
}


/*
//Copy constructor
//INPUT: 1 argument: a node to copy
//OUTPUT: no return type
node::node(const node & to_copy)
{
    a_planet = NULL;

    //Check if planet to copy is terrestrial or gas
    if (to_copy.allow_landing())
        a_planet = new terr_planet(to_copy);

    else 
        a_planet = new gas_planet(to_copy);

    //Initialize next pointer
    next = NULL;
}


//Destructor - releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
node::~node()
{
    if (a_planet)
    {
        delete a_planet;
        a_planet = NULL;
    }

    if (next)
    {
        delete next;
        next = NULL;
    }
} 
*/



node *& node::go_next(void)
{
    return next;
}



//Returns previous pointer by reference
node *& node::go_prev(void)
{
    return prev;
}



//Sets next pointer to point to same node as argument
void node::connect_next(node * connection)
{
    next = connection;     
}



//Sets prev pointer to point to same node as argument
void node::connect_prev(node * connection)
{
    prev = connection;
}



//Display planet details
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - unable to display,
//1 - success)
int node::display_planet(void)
{
    if (!a_planet)
        return -1;

    else
        return a_planet->display();
} 



//Try landing on the planet
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - landing not allowed
//(gas planet), 1 - success (terrestrial planet))
int node::land_on_planet(void)
{
    if (!a_planet)
        return -1;

    else
        return a_planet->allow_landing();
}



//Check habitability of planet
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - not habitable
//(gas planet), 1 - habitable)
int node::check_habitability(void)
{
    if (!a_planet)
        return -1;

    else
        return a_planet->check_habitability();
}



//Get distance of planet from sun
//INPUT: no arguments
//OUTPUT: return type: int (0 - planet pointer null, positive value - distance from sun)
int node::get_dist(void)
{
    if (!a_planet)
        return 0;

    else 
        return a_planet->get_dist();
}



//Find planet (matches argument with planet name)
//INPUT: 1 argument: name to match
//OUTPUT: return type: int (-1 - planet pointer null, 0 - no match, 1 - match found)
int node::find_planet(char * to_match)
{
    if (!a_planet)
        return -1;

    else
        return a_planet->find_planet(to_match);
}



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


/*
//Copy constructor
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



//Recursive function - copies DLL
int solar_system::copy_dll(node * & dest, node * src)
{
    int copied = 0;

    //base case - src is null
    if (!src)
    {
        dest = NULL;
        return 0;
    }

    //copy src
    dest = new node;
   
    ++copied;
 
    //Recursive call to next node
    copied += copy_dll(dest->go_next(), src->go_next());

    return copied;
}
*/



//Destructor - Releases all dynamic memory
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

    //Remove all nodes in dll
    if (remove_all(head))
        tail = NULL;
}



//Removes all nodes in dll - recursive
//INPUT: 1 argument: head pointer to DLL
//OUTPUT: return type: int (number of nodes removed)
int solar_system::remove_all(node * & head)
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



/*
//Adds a new planet to the DLL
//INPUT: 1 argument: a planet to add
//OUTPUT: return type: int (
int solar_system::add_planet(planet * to_add)
{
    int new_dist = 0;   //new planet's distance from sun
    node * current = NULL;     //to traverse dll

    //Null argument - flag failure
    if (!to_add)
        return 0;

    //Get distance for planet to add
    new_dist = to_add->get_dist();

    //Empty list
    if (!head)
    {
        //Create new node at head
        head = new node;
  
        //Copy argument planet into node
        if (to_add->allow_landing)
            head->a_planet = new terr_planet(to_add);

        else 
            head->a_planet = new gas_planet(to_add);
 
        //Set next, prev and tail pointers 
        head->connect_next(NULL);
        head->connect_prev(NULL);
        tail = head;
    }

    //One or more items in list
    else
    {
        //Start traversing at head of DLL
        current = head;

        //Compare new distance with current planet's distance
        //If current distance is lesser, traverse to next node
        while (current->get_dist() <= new_dist)
            current = current->go_next();

                
}



int solar_system::add_planet(node * & head, node * & tail, planet * to_add, int new_dist)
{
    //base case
    if (!head)
    {
        //Create new node at head
        head = new node;
  
        //Copy argument planet into node
        if (to_add->allow_landing)
            head->a_planet = new terr_planet(to_add);

        else 
            head->a_planet = new gas_planet(to_add);
 
        //Set next, prev and tail pointers 
        head->connect_next(NULL);
        head->connect_prev(NULL);
        tail = head;

        return 1;
    }


    node * temp = NULL;
    int count = 0;

    //base case
    if (!head)
        return 0;

    //recursive call
    count = insert_before(head->next);

    //If 2 add new node after
    if (head->data == 2)
    {
        temp = new node;
        temp->data = 100;
        temp->next = head;
        temp->previous = head->previous;
        head = temp;
        temp->next->previous = temp;

        return count + 2;
    }

    else
        return count + 1;


}

*/


//Wrapper - Displays all planets in order of distance from sun
//INPUT: no arguments
//OUTPUT: return type: int (total number of planets)
int solar_system::display_all_planets(void)
{
    return display_all_planets(head); 
}


//Displays all planets in order of distance from sun - recursively
//INPUT: 1 argument: head pointer 
//OUTPUT: return type: int (total number of planets)
int solar_system::display_all_planets(node * head)
{
    int displayed = 0;

    //Base case
    if (!head)
        return 0;

    //Display current planet
    if (head->display_planet())
        ++displayed;

    //Recursive call to next node
    displayed += display_all_planets(head->go_next());

    return displayed;
}
        


//Wrapper - Displays all habitable planets
//INPUT: no arguments
//OUTPUT: return type: int (number of habitable planets)
int solar_system::display_habitable_planets(void)
{
    return display_habitable_planets(head);
}



//Displays all habitable planets - recursively
//INPUT: 1 argument: head pointer 
//OUTPUT: return type: int (number of habitable planets)
int solar_system::display_habitable_planets(node * head)
{
    int habitable = 0;

    //Base case
    if (!head)
        return 0;

    //Display current planet if its habitable
    if (head->check_habitability())
    {
        if (head->display_planet())
            ++habitable;
    }

    //Recursive call to next node
    habitable += display_all_planets(head->go_next());

    return habitable;
}



//Compares argument with sun name to check for match
//INPUT: 1 argument: sun name to match
//OUTPUT: return type: int (-1 - null argument, 0 - no match, 1 - match found)
int solar_system::find_sun(char * sun_to_match)
{
    if (!sun_to_match)
        return -1;

    if (sun && strcmp(sun_to_match, sun) == 0)
        return 1;
        
    else
        return 0;
}



int solar_system::explore_planet(char * planet_name)
{
    node * current = NULL;
    bool planet_found = false;
    int result = 0;             //Value to return

    //If null argument, flag failure
    if (!planet_name)
        return -2;

    //If no planets in list, flag failure
    if (!head)
        return -1;

    //Otherwise, start traversing at head
    current = head;
   
    //Repeat until a match is found or end of list 
    while (current && !planet_found)
    {
        //If its a match, flag as found
        if (current->find_planet(planet_name))
            planet_found = true;

        //Otherwise go to next node
        else
            current = current->go_next();
    }

    //If planet with matching name is found
    if (planet_found)
    {
        //Try landing and check for habitability
        //Flag accordingly
        if (current->land_on_planet())        
        {
            result = 1;

            if (current->check_habitability())
                result = 2;
        }
    }

    //If planet not found
    else
        result = 0;       

    return result; 
}



