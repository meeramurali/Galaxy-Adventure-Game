//Filename: planet.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........



#include "planet.h"



//Constants
const int TERR_MIN_SIZE = 1;
const int TERR_MAX_SIZE = 5;
const int GAS_MIN_SIZE = 10;
const int GAS_MAX_SIZE = 50;

const int TERR_MIN_DIST = 20;
const int TERR_MAX_DIST = 300;
const int GAS_MIN_DIST = 500;
const int GAS_MAX_DIST = 1000;

const int TERR_MIN_MOONS = 0;
const int TERR_MAX_MOONS = 3;
const int GAS_MIN_MOONS = 15;
const int GAS_MAX_MOONS = 80;

const int ATMOS_MIN_SIZE = 2;
const int ATMOS_MIN_DIST = 30;

const int HABIT_MIN_DIST = 60;
const int HABIT_MAX_DIST = 200;



//Default constructor - initializes all data members to their
//zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
node::node(): next(NULL), prev(NULL) {}



//Destructor - releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
node::~node()
{
    next = NULL;
    prev = NULL;
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







//Default constructor - initializes all data members to their
//zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
planet::planet()
{
    //Initialize all data members
    name = sun = NULL;
    size = dist = num_moons = 0; 
}



//Constructor with arguments - initialize data members with
//argument value
//INPUT: 2 arguments: name of planet, name of sun
//OUTPUT: no return value
planet::planet(char * planet_name, char * sun_name)
{
    //Copy arguments (if not NULL) into name and sun 
    if (planet_name)
    {
        name = new char [strlen(planet_name) + 1];
        strcpy(name, planet_name);
    }
    else
        name = NULL;
    
    if (sun_name)
    {
        sun = new char [strlen(sun_name) + 1];
        strcpy(sun, sun_name);
    }
    else
        name = NULL;

    //Set remaining data members to their zero equivalent
    size = dist = num_moons = 0; 
}



//Copy constructor - copies data members of argument object
//INPUT: 1 argument: A planet class object to copy
//OUTPUT: no return value
planet::planet(const planet & to_copy)
{
    if (to_copy.name)
    {
        name = new char [strlen(to_copy.name) + 1];
        strcpy(name, to_copy.name);
    }
    else
        name = NULL;
    
    if (to_copy.sun)
    {
        sun = new char [strlen(to_copy.sun) + 1];
        strcpy(sun, to_copy.sun);
    }
    else
        sun = NULL;

    size = to_copy.size;
    dist = to_copy.dist;
    num_moons = to_copy.num_moons;
}



//Destructor - Releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
planet::~planet()
{
    if (name)
    {
        delete [] name;
        name = NULL;
    }

    if (sun)
    {
        delete [] sun;
        sun = NULL;
    }
    
    //Set remaining data members to their zero equivalent
    size = dist = num_moons = 0; 
}



//Displays all planet details
//INPUT: no arguments
//OUTPUT: return type: int (0 - failure, null data members, 1 - success)
int planet::display(void)
{
    //If null data members, flag failure
    if (!name || !sun)
        return 0;

    //Display all data member values
    cout << "Planet name: " << name << endl
         << "Sun: " << sun << endl
         << "Size: " << size << " thousand miles radius" << endl
         << "Distance from sun: " << dist << " million miles" << endl
         << "Number of moons: " << num_moons << endl;
    
    return 1;
}



//Checks if atmosphere exists based on size and distance from sun
//INPUT: no arguments
//OUTPUT: return type: bool (true - atmosphere exists, false - no atmosphere)
bool planet::check_atmos(void)
{
    //If size and distance from sun are above optimal threshold values
    //Flag as atmosphere exists
    if (size >= ATMOS_MIN_SIZE && dist >= ATMOS_MIN_DIST)
        return true;

    //Otherwise flag no atmosphere
    else
        return false;
}



//Checks if planet is habitable
//INPUT: no arguments
//OUTPUT: return type: bool (true - habitable, false - not habitable)
bool planet::check_habitability(void)
{
    //If atmosphere exists and distance from sun is within optimal range
    //Flag as habitable
    if (check_atmos() && dist >= HABIT_MIN_DIST && dist <= HABIT_MAX_DIST)
        return true;

    //Otherwise flag as not habitable
    else
        return false;
}



//Returns distance from sun value
//INPUT: no arguments
//OUTPUT: return type: int (distance from sun)
int planet::get_dist(void)
{
    return dist;
}


//Compares argument with planet name
bool planet::find_planet(char * to_match)
{
    if (to_match && strcmp(to_match, name) == 0)
        return true;

    else
        return false;
}



//Default constructor - implicitly invokes base class default constructor
//INPUT: no arguments
//OUTPUT: no return value
terr_planet::terr_planet() 
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}



//Constructor with arguments - passes argument values to base class
//constructor through initialization list
//INPUT: 2 arguments: name of planet, name of sun
//OUTPUT: no return value
terr_planet::terr_planet(char * planet_name, char * sun_name): planet(planet_name, sun_name)
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}




//Copy constructor - copies data members of argument object into current object
//INPUT: 1 argument: A terr_planet class object to copy
//OUTPUT: no return value
terr_planet::terr_planet(const terr_planet & to_copy): planet(to_copy)
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}


    

//Checks if planet allows landing 
//INPUT: no arguments
//OUTPUT: return type: bool - always returns true for terrestrial planets
bool terr_planet::allow_landing(void)
{
    return true;
}



//Sets random size in range TERR_MIN_SIZE - TERR_MAX_SIZE (thousand miles radius)
//INPUT: no arguments
//OUTPUT: return type: int (size in units of 'thousand miles radius')
int terr_planet::set_size(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random size in range TERR_MIN_SIZE - TERR_MAX_SIZE
    return rand() % (TERR_MAX_SIZE - TERR_MIN_SIZE + 1) + TERR_MIN_SIZE;
}



//Sets random dist in range TERR_MIN_DIST - TERR_MAX_DIST (thousand miles radius)
//INPUT: no arguments
//OUTPUT: return type: int (dist in units of 'thousand miles radius')
int terr_planet::set_distance(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random dist in range TERR_MIN_DIST - TERR_MAX_DIST
    return rand() % (TERR_MAX_DIST - TERR_MIN_DIST + 1) + TERR_MIN_DIST;
}



//Sets random number of moons in range TERR_MIN_MOONS - TERR_MAX_MOONS
//INPUT: no arguments
//OUTPUT: return type: int (number of moons)
int terr_planet::set_moons(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random num_moons in range TERR_MIN_MOONS - TERR_MAX_MOONS
    return rand() % (TERR_MAX_MOONS - TERR_MIN_MOONS + 1) + TERR_MIN_MOONS;
}



//Default constructor - implicitly invokes base class default constructor
//INPUT: no arguments
//OUTPUT: no return value
gas_planet::gas_planet()
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}



//Constructor with arguments - passes argument values to base class
//constructor through initialization list
//INPUT: 2 arguments: name of planet, name of sun
//OUTPUT: no return value
gas_planet::gas_planet(char * planet_name, char * sun_name): planet(planet_name, sun_name)
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}




//Copy constructor - copies data members of argument object into current object
//INPUT: 1 argument: A gas_planet class object to copy
//OUTPUT: no return value
gas_planet::gas_planet(const gas_planet & to_copy): planet(to_copy)
{
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}



//Checks if planet allows landing 
//INPUT: no arguments
//OUTPUT: return type: bool - always returns false for gas planets
bool gas_planet::allow_landing(void)
{
    return false;
}



//Sets random size in range GAS_MIN_SIZE - GAS_MAX_SIZE (thousand miles radius)
//INPUT: no arguments
//OUTPUT: return type: int (size in units of 'thousand miles radius')
int gas_planet::set_size(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random size in range GAS_MIN_SIZE - GAS_MAX_SIZE
    return rand() % (GAS_MAX_SIZE - GAS_MIN_SIZE + 1) + GAS_MIN_SIZE;
}



//Sets random dist in range GAS_MIN_DIST - GAS_MAX_DIST (thousand miles radius)
//INPUT: no arguments
//OUTPUT: return type: int (dist in units of 'thousand miles radius')
int gas_planet::set_distance(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random dist in range GAS_MIN_DIST - GAS_MAX_DIST
    return rand() % (GAS_MAX_DIST - GAS_MIN_DIST + 1) + GAS_MIN_DIST;
}



//Sets random number of moons in range GAS_MIN_MOONS - GAS_MAX_MOONS
//INPUT: no arguments
//OUTPUT: return type: int (number of moons)
int gas_planet::set_moons(void)
{
    struct timeval to_seed;

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random num_moons in range GAS_MIN_MOONS - GAS_MAX_MOONS
    return rand() % (GAS_MAX_MOONS - GAS_MIN_MOONS + 1) + GAS_MIN_MOONS;
}
