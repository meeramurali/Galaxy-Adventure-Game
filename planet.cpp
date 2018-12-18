//Filename: planet.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  2
//Date:     07/21/2017

//This program implements the member functions of the planet class and its derived types.
//The 'planet' is an abstract base class from which the planet types (terrestrial, 
//gas planets) have been derived.
//Two types of planets have been implemented:
//TERRESTRIAL planets - Allow landing since they have solid surfaces, have zero or few
//moons, a smaller range of size (radius), and closer to the sun
//GAS planets - Do not allow landing since they are gaseous, have a large number of
//moons, larger range of size (radius), amd further away from the sun



#include "planet.h"



//Constants
const int TERR_MIN_SIZE = 1;        //Terrestrial planet min radius (thousand miles)
const int TERR_MAX_SIZE = 5;        //Terrestrial planet max radius (thousand miles)
const int GAS_MIN_SIZE = 10;        //Gas planet minimum radius (thousand miles)
const int GAS_MAX_SIZE = 50;        //Gas planet minimum radius (thousand miles)

const int TERR_MIN_DIST = 20;       //Terrestrial planet min distance from sun (million miles)
const int TERR_MAX_DIST = 300;      //Terrestrial planet max distance from sun (million miles)
const int GAS_MIN_DIST = 500;       //Gas planet min distance from sun (million miles)
const int GAS_MAX_DIST = 1000;      //Gas planet max distance from sun (million miles)

const int TERR_MIN_MOONS = 0;       //Terrestrial planet min number of moons
const int TERR_MAX_MOONS = 3;       //Terrestrial planet max number of moons
const int GAS_MIN_MOONS = 15;       //Gas planet max number of moons
const int GAS_MAX_MOONS = 80;       //Gas planet max number of moons

const int ATMOS_MIN_SIZE = 2;       //Min size of planet for atmosphere to exist (thousand miles)
const int ATMOS_MIN_DIST = 30;      //Min distance from sun for atmosphere to exist (million miles)

const int HABIT_MIN_DIST = 60;      //Optimal distance for habitability - lower limit
const int HABIT_MAX_DIST = 200;     //Optimal distance for habitability - upper limit

const float SIZE_FACTOR = 0.15;        //To calculate fuel cost to visit a planet
const float MOONS_FACTOR = 5;         //To calculate fuel cost to visit a planet



//Default constructor - initializes all data members to their
//zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
planet::planet()
{
    //Initialize all data members
    name = sun = NULL;
    size = dist = num_moons = 0; 
    
    //Set orbit position
    orbit_pos = set_orbit_pos();
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

    //Set orbit position
    orbit_pos = set_orbit_pos();

    //Set remaining data members to their zero equivalent
    size = dist = num_moons = 0; 
}



//Copy constructor - copies data members of argument object
//INPUT: 1 argument: A planet class object to copy
//OUTPUT: no return value
planet::planet(const planet & to_copy)
{
    
    //Copy argument data members (if not NULL) into name and sun 
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

    //Copy size (radius), distance from sun and number of moons
    size = to_copy.size;
    dist = to_copy.dist;
    num_moons = to_copy.num_moons;
    orbit_pos = to_copy.orbit_pos;
}



//Destructor - Releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
planet::~planet()
{
    //Release allocated memory for name and sun
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
    size = dist = num_moons = orbit_pos = 0; 
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
    cout << "\n\tPlanet name: " << name << endl;

    //Determine planet type 
    if (allow_landing())
        cout << "\tType: Terrestrial" << endl;
    else
        cout << "\tType: Gas" << endl;
 
    cout << "\tSun: " << sun << endl
         << "\tSize: " << size << " thousand miles radius" << endl
         << "\tDistance from sun: " << dist << " million miles" << endl
         << "\tNumber of moons: " << num_moons << endl
         << "\tOrbit position: " << orbit_pos << " degrees" << endl;

    //Display habitability
    if (check_habitability())
        cout << "\tHabitable!" << endl;
    else
        cout << "\tNot habitable!" << endl;
    
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
//INPUT: name to match
//OUTPUT: true/false (match/no match)
bool planet::find_planet(char * to_match)
{
    bool result = false;                //value to return
    int to_match_len = strlen(to_match);//length of name to match
    int name_len = strlen(name);        //length of current name
    char * to_match_lower = new char[to_match_len + 1]; //to convert to lower case
    char * name_lower = new char[name_len + 1];         //to convert to lower case

    //convert to lower case
    for (int i = 0; i < to_match_len; ++i)
        to_match_lower[i] = tolower(to_match[i]);
    to_match_lower[to_match_len] = '\0';

    for (int i = 0; i < name_len; ++i)
        name_lower[i] = tolower(name[i]);
    name_lower[name_len] = '\0';

    //Flag if planet name matches argument
    if (to_match && strcmp(to_match_lower, name_lower) == 0)
        result = true;

    //Deallocate temporary variable
    if (to_match_lower)
    {
        delete [] to_match_lower;
        to_match_lower = NULL;
    }

    if (name_lower)
    {
        delete [] name_lower;
        name_lower = NULL;
    }

    return result;
}



//Sets random position in range 0 - 359 degrees angle
//INPUT: no arguments
//OUTPUT: return type: int (orbit position)
int planet::set_orbit_pos(void)
{
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random size in range 0 - 359 degrees
    return rand() % (360);
}



//Returns orbit position value
//INPUT: no arguments
//OUTPUT: return type: int (orbit position)
int planet::get_orbit_pos(void)
{
    return orbit_pos;
}



//Returns fuel cost to visit planet based on size and number of moons
//INPUT: no arguments
//OUTPUT: fuel cost (int)
int planet::calculate_fuel_cost(void)
{
    //Fuel cost is a function of size (gravitational pull) and
    //number of moons (nearby moons also exert gravitational pull)
    return (SIZE_FACTOR * size) + (MOONS_FACTOR * num_moons);
}



//Displays name of planet
//INPUT: no arguments
//OUTPUT; 0/1 (failure/success)
int planet::display_name(void)
{
    //null data member
    if (!name)
        return 0;

    //display name
    cout << "\t" << name << endl;
    return 1;
}



//Default constructor - implicitly invokes base class default constructor
//INPUT: no arguments
//OUTPUT: no return value
terr_planet::terr_planet() 
{
    //Randomly generate values for size, distance from sun and number of moons
    //based on the type (terrestrial)
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
    //Randomly generate values for size, distance from sun and number of moons
    //based on the type (terrestrial)
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}




//Copy constructor - copies data members of argument object into current object
//INPUT: 1 argument: A terr_planet class object to copy
//OUTPUT: no return value
terr_planet::terr_planet(const terr_planet & to_copy): planet(to_copy) {}



//Copy constructor
terr_planet::terr_planet(const planet * to_copy): planet(* to_copy) {}

    

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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

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
    //Randomly generate values for size, distance from sun and number of moons
    //based on the type (gas)
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
    //Randomly generate values for size, distance from sun and number of moons
    //based on the type (gas)
    size = set_size();
    dist = set_distance();
    num_moons = set_moons();
}




//Copy constructor - copies data members of argument object into current object
//INPUT: 1 argument: A gas_planet class object to copy
//OUTPUT: no return value
gas_planet::gas_planet(const gas_planet & to_copy): planet(to_copy) {}



//Copy constructor - copies argument planet
//INPUT: 1 argument: a planet pointer set to any type of planet
//OUTPUT: no return value
gas_planet::gas_planet(const planet * to_copy): planet(* to_copy) {}



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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

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
    struct timeval to_seed;     //To get microseconds field of current time
                                //to seed rand()

    //Seed rand with usec field of time
    gettimeofday(&to_seed, NULL);
    srand(to_seed.tv_usec);

    //Generate random num_moons in range GAS_MIN_MOONS - GAS_MAX_MOONS
    return rand() % (GAS_MAX_MOONS - GAS_MIN_MOONS + 1) + GAS_MIN_MOONS;
}
