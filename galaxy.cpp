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



//Copy constructor
//INPUT: 1 argument: a node to copy
//OUTPUT: no return type
node::node(const node & to_copy)
{
    if (!to_copy.a_planet)
        a_planet = NULL;

    else
    {
        //Check if planet to copy is terrestrial or gas
        if (to_copy.a_planet->allow_landing() == 1)
            a_planet = new terr_planet(to_copy.a_planet);

        else 
            a_planet = new gas_planet(to_copy.a_planet);
    }
    
    next = prev = NULL;
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
} 



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


//Copy constructor
solar_system::solar_system(const solar_system & to_copy)
{
    if (copy_solar_system(to_copy) == -1)
        sun = NULL;
        head = tail = NULL;
}



//Copied argument solar system into current object
//INPUT: 1 argument: solar system to copy
//OUTPUT: return type: int (-1 - failure unable to copy,
//0 - sun copied, no planets to copy, positive value - number of planets copied)
int solar_system::copy_solar_system(const solar_system & to_copy)
{
    if (!to_copy.sun)
        return -1;

    //Delete existing sun if any
    if (sun)
    {
        delete [] sun;
        sun = NULL;
    }

    //Copy sun from argument object
    sun = new char [strlen(to_copy.sun) + 1];
    strcpy(sun, to_copy.sun);

    //Delete any existing planets
    if (head)
    {
        //Remove all planets
        if (remove_all(head))
            tail = NULL;
    }

    //Copy DLL of planets from argument object
    return copy_dll(head, tail, to_copy.head);
    
}



//Recursive function - copies DLL
int solar_system::copy_dll(node * & dest, node * & dest_tail, node * src)
{
    int copied = 0;

    //base case - src is null
    if (!src)
    {
        dest = NULL;
        dest_tail = NULL;

        return 0;
    }

    //copy src
    dest = new node(* src);
    ++copied; 
 
    //Recursive call to next node
    copied += copy_dll(dest->go_next(), dest_tail, src->go_next());
    
    //If last node, update tail
    if (copied == 1)
        dest_tail = dest;

    else if (copied > 1)
        (dest->go_next())->connect_prev(dest);

    return copied;
}



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



//Adds a new planet to the DLL
//INPUT: 1 argument: a planet to add
//OUTPUT: return type: int (0 -
int solar_system::add_planet(planet * to_add)
{
    int new_dist = 0;   //new planet's distance from sun

    //Null argument - flag failure
    if (!to_add)
        return 0;

    //Get distance for planet to add
    new_dist = to_add->get_dist();

    //Call recursive function to add new node with new planet in sorted order
    return add_planet(head, tail, to_add, new_dist);
}



int solar_system::add_planet(node * & head, node * & tail, planet * to_add, int new_dist)
{

    node * temp = NULL;
    int success = 0;

    //Base case - head is null
    if (!head)
    {
        //Create new node at head
        head = new node(to_add);
  
        //Set next, prev and tail pointers 
        head->connect_next(NULL);

        //If empty list
        if (!tail)
        {
            head->connect_prev(NULL);
            tail = head;
        }

        //Inserting at end of list
        else
        {
            head->connect_prev(tail);
            tail = head;
        }

        success = 1;
    }

    //Check if its time to insert - is current distance
    //greater than new distance?
    else if (head->get_dist() > new_dist)
    {
        //Create new node using temp 
        temp = new node(to_add);
        
        //Connect up temp node before head
        temp->connect_next(head);
        temp->connect_prev(head->go_prev());
        head = temp;
        (temp->go_next())->connect_prev(temp);
        
        success = 1;
    }

    //recursive call
    else
        success = add_planet(head->go_next(), tail, to_add, new_dist);

    return success;
}



//Displays the sun and all planets in order of distance from sun
//INPUT: no arguments
//OUTPUT: return type: int (total number of planets)
int solar_system::display(void)
{
    if (!sun)
        return -1;

    //Display sun
    cout << "\nSun: " << sun << endl;

    //Display all planets
    return display_all_planets();
}



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
    if (head->check_habitability() == 1)
    {
        if (head->display_planet())
            ++habitable;
    }

    //Recursive call to next node
    habitable += display_habitable_planets(head->go_next());

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



//OUTPUT: return type: int (-2: null argument, -1: no planets in list, 
//0: no match found, 1: match found, unable to land (gas planet),
//2: match found, landed successfully (terr planet), not habitable,
//3: match found, landed successfully (terr planet), habitable!
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
        result = 1;
        //Try landing and check for habitability
        //Flag accordingly
        if (current->land_on_planet())        
        {
            result = 2;

            if (current->check_habitability())
                result = 3;
        }
    }

    //If planet not found
    else
        result = 0;       

    return result; 
}



//Default constructor - initializes all data members to zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
galaxy::galaxy(): galaxy_array(NULL), galaxy_array_size(0), num_solar_sys(0) {}



//Constructor with argument
//INPUT: 1 argument: size of array
//OUTPUT: no return value
galaxy::galaxy(int array_size)
{
    //Create an array of argument size (if valid size)
    if (galaxy_array_size > 0)
    {
        galaxy_array_size = array_size;
        galaxy_array = new solar_system[galaxy_array_size];
    }

    //If invalid size, initialize to zero equivalent
    else
    {
        galaxy_array_size = 0;
        galaxy_array = NULL;
    }
    
    //Initialize remaining data members
    num_solar_sys = 0;
}



//Copy constructor
//INPUT: 1 argument: a galaxy object to copy
//OUTPUT: no return value
galaxy::galaxy(const galaxy & to_copy)
{
    num_solar_sys = 0;

    //Copy galaxy array size and number of solar systems
    //if valid
    if (galaxy_array_size > 0)
    {
        //Create array of size
        galaxy_array_size = to_copy.galaxy_array_size;
        galaxy_array = new solar_system [galaxy_array_size];

        //Copy each solar system from galaxy to copy
        for (int i = 0; i < to_copy.num_solar_sys; ++i)
        {
            if (galaxy_array[i].copy_solar_system(to_copy.galaxy_array[i]))
                ++num_solar_sys;
        }
    }
}



//Destructor - releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
galaxy::~galaxy()
{
    //If at least one solar system
    if (galaxy_array)
    {
        //Delete galaxy array
        delete [] galaxy_array;
        galaxy_array = NULL;
    }

    //Reset other data members to 0
    galaxy_array_size = num_solar_sys = 0;
}



//Adds a new solar system into first available spot in array
//INPUT: 1 argument: solar system object to add
//OUTPUT: return type: int (-1 - failure, array is full, 
//0 or positive values - no. of planets copied)
int galaxy::add_solar_system(const solar_system & to_add)
{
    //Check if array is full
    if (num_solar_sys == galaxy_array_size)
        return -1;

    //Copy argument solar system into array
    //num_solar_sys is the next non-empty index
    if (galaxy_array[num_solar_sys].copy_solar_system(to_add) > -1)
        ++num_solar_sys;

    return num_solar_sys;
} 

















