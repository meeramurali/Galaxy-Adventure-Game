//Filename: galaxy.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  2
//Date:     07/21/2017

//This program implements the member functions of classes,
//'node', 'solar_system', 'galaxy' and 'spaceship'. The galaxy has been implemented 
//as a dynamically allocated array of solar system objects. Each solar
//system contains a sun and a circular linked list (CLL) of planets arranged
//in sorted order of the planets' orbital position around the sun. The 'node' class
//manages a single node of the CLL, which contains a pointer to a 'planet'.
//Since 'planet' is an abstract base class from which the planet types (terrestrial, 
//gas planets) have been derived, each node's pointer can be set to point to
//any type of planet. The 'spaceship' is derived from the galaxy class and manages
//a 'fuel' data member based on planets visited

#include "galaxy.h"



//Default constructor - Sets all data members to zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
node::node(): a_planet(NULL), next(NULL) {}



//Constructor with a planet object as argument
//INPUT: 1 argument: a planet object
//OUTPUT: no return value
node::node(planet * to_copy)
{
    //Check if planet to copy is terrestrial or gas
    //Create new planet accordingly
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



//Copy constructor - copies argument node object
//INPUT: 1 argument: a node to copy
//OUTPUT: no return type
node::node(const node & to_copy)
{
    //If node to copy has no planet
    if (!to_copy.a_planet)
        a_planet = NULL;

    else
    {
        //Check if planet to copy is terrestrial or gas
        //Create new planet in node accordingly
        if (to_copy.a_planet->allow_landing() == 1)
            a_planet = new terr_planet(to_copy.a_planet);

        else 
            a_planet = new gas_planet(to_copy.a_planet);
    }
   
    //Initialize next pointer to null 
    next = NULL;
}



//Destructor - releases all dynamic memory
//INPUT: no arguments
//OUTPUT: no return value
node::~node()
{
    //Delete planet in node
    if (a_planet)
    {
        delete a_planet;
        a_planet = NULL;
    }
} 



//Returns the node's next pointer by reference
//INPUT: no arguments
//OUTPUT: node's next pointer by reference
node *& node::go_next(void)
{
    return next;
}



//Sets next pointer to point to same node as argument
//INPUT: 1 argument: location to set next pointer to 
//OUTPUT: no return value
void node::connect_next(node * connection)
{
    next = connection;   
    return;  
}



//Display planet details
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - unable to display,
//1 - success)
int node::display_planet(void)
{
    //If planet pointer is null, flag failure
    if (!a_planet)
        return -1;

    //Otherwise display planet
    else
        return a_planet->display();
} 



//Try landing on the planet
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - landing not allowed
//(gas planet), 1 - success (terrestrial planet))
int node::land_on_planet(void)
{
    //If planet pointer is null, flag failure
    if (!a_planet)
        return -1;

    //Otherwise, check if planet allows landing
    else
        return a_planet->allow_landing();
}



//Check habitability of planet
//INPUT: no arguments
//OUTPUT: return type: int (-1 - planet pointer null, 0 - not habitable
//(gas planet), 1 - habitable)
int node::check_habitability(void)
{
    //If planet pointer is null, flag failure
    if (!a_planet)
        return -1;

    //Otherwise, check planet's habitability
    else
        return a_planet->check_habitability();
}



//Get distance of planet from sun
//INPUT: no arguments
//OUTPUT: return type: int (0 - planet pointer null, positive value - distance from sun)
int node::get_dist(void)
{
    //If planet pointer is null, flag failure
    if (!a_planet)
        return 0;

    //Otherwise get planet's distance from sun
    else 
        return a_planet->get_dist();
}



//Find planet (matches argument with planet name)
//INPUT: 1 argument: name to match
//OUTPUT: return type: int (-1 - planet pointer null, 0 - no match, 1 - match found)
int node::find_planet(char * to_match)
{
    //If planet pointer is null, flag failure
    if (!a_planet)
        return -1;

    //Otherwise check if planet's name matches argument
    else
        return a_planet->find_planet(to_match);
}
        


//Compares orbit position with that of argument node's planet
//INPUT: 1 argument: a node object
//OUTPUT: return type: int (1 - current planet's position is greater than
//or equal to argument's position, 0 - otherwise)
int node::is_greater_or_equal_orbit_pos(const node & to_compare)
{
    //Get orbit position of the planet to compare
    int to_compare_pos = to_compare.a_planet->get_orbit_pos();
   
    //If current planet's value is greater than that of argument planet
    //return 1 
    if (a_planet->get_orbit_pos() >= to_compare_pos)
        return 1;

    //Otherwise return 0
    else
        return 0;
}



//Returns fuel cost to visit planet in node
//INPUT: no arguments
//OUTPUT: return type: int (fuel cost)
int node::calculate_fuel_cost(void)
{
    return a_planet->calculate_fuel_cost();
}



//Displays planet's name
//INPUT: no arguments
//OUTPUT: return type: int (0/1 - failure/success)
int node::display_planet_name(void)
{
    return a_planet->display_name();
}



//Default constructor - initializes all data members to null
//INPUT: no arguments
//OUTPUT: no return value
solar_system::solar_system(): sun(NULL), rear(NULL) {}



//Constructor with argument sun name
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

    //Initialize rear to NULL
    rear = NULL;
}


//Copy constructor - copies argument solar system object
//INPUT: 1 argument: a solar system object to copy
//OUTPUT: no return value
solar_system::solar_system(const solar_system & to_copy)
{
    //Copy argument solar system's data members into current
    //If copy unsuccessful, set data members to null
    if (copy_solar_system(to_copy) == -1)
    {
        sun = NULL;
        rear = NULL;
    }
}



//Copied argument solar system into current object
//INPUT: 1 argument: solar system to copy
//OUTPUT: return type: int (-1 - failure unable to copy,
//0 - sun copied, no planets to copy, positive value - number of planets copied)
int solar_system::copy_solar_system(const solar_system & to_copy)
{
    int copied = 0;         //number of nodes copied
    node * head = NULL;     //temporary pointer to first node in list

    //Flag failure if argument object has no sun name or planets
    if (!to_copy.sun || !to_copy.rear)
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
    if (rear)
    {
        //Remove all planets
        if (remove_all(rear->go_next(), rear))
            rear = NULL;
    }

    //Copy CLL of planets from argument object
    return copy_cll(head, head, (to_copy.rear)->go_next(), to_copy.rear, copied);
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

    //Remove all nodes in cll
    if (rear)
    {
        if (remove_all(rear->go_next(), rear))
            rear = NULL;
    }
}



//Removes all nodes in dll - recursive
//INPUT: 2 arguments: pointer to a node (for recursive
//call, actual rear pointer (for stopping condition)
//OUTPUT: return type: int (number of nodes removed)
int solar_system::remove_all(node * & head, node * & fix_rear)
{
    int removed = 0;    //number of nodes removed

    //Base case
    if (!fix_rear)
        return 0;

    //If at last node
    if (head == fix_rear)
    {
        //Remove last node
        delete head;
        head = NULL;
        fix_rear = NULL;
        
        return 1;
    }

    //Recursive call to next node
    removed += remove_all(head->go_next(), fix_rear);

    //Delete head
    delete head;
    head = NULL;

    return ++removed;
}    



//Recursive function - copies CLL of planets
//INPUT: 3 arguments - destination DLL head and tail, source DLL head
//OUTPUT: return type: int (number of nodes copied)
int solar_system::copy_cll(node * & head, node * & fix_head, node * src_head, node * src_rear, int & copied)
{
    //base case
    if (!src_head)
    {
        rear = NULL;
        return 0;
    }

    //last node
    if (src_head == src_rear)
    {
        //copy last node
        head = new node (* src_head);
        head->go_next() = fix_head;

        //Update rear
        rear = head;

        return ++copied;
    }

    //Copy current node
    head = new node (* src_head);
    head->go_next() = NULL;

    //Update fix_head after copying first node
    if (!copied)
        fix_head = head;

    ++copied;

    //Recursive call to copy next node
    return copy_cll(head->go_next(), fix_head, src_head->go_next(), src_rear, copied);
}



//Wrapper - Adds a new planet to the CLL
//INPUT: 1 argument: a planet to add
//OUTPUT: return type: int (0/1 - failure/success)
int solar_system::add_planet(planet * to_add)
{
    //Null argument - flag failure
    if (!to_add)
        return 0;

    //Empty list
    if (!rear)
    {
        rear = new node(to_add);
        rear->connect_next(rear);
        return 1;
    }

    //Call recursive function to add new node with new planet in sorted order
    return add_planet(rear->go_next(), to_add);
}



//Adds a new planet to the CLL - recursively
//INPUT: 4 arguments: DLL head and tail, a planet to add, distance from sun of new planet
//OUTPUT: return type: int (0/1 - failure/success)
int solar_system::add_planet(node * & head, planet * to_add)
{

    node * temp = NULL;     //Temporary node pointer to create new node
    int success = 0;        //Value to return

    //Create new node using temp 
    temp = new node(to_add);

    //Base case - last node
    if (head == rear)
    {
        //If last node's orbit pos is greater than or equal to new node's
        //insert before last node
        if (head->is_greater_or_equal_orbit_pos(* temp))
        {
            temp->connect_next(rear);
            head = temp;
        }

        //If last node's orbit pos is lesser than new node's
        //insert after last node, and update rear pointer
        else
        {
            temp->connect_next(rear->go_next());
            rear->connect_next(temp);
            rear = temp;
        }

        success = 1;

        return success;
    }

    //Check if its time to insert - is current orbit position
    //greater than new orbit position?
    if (head->is_greater_or_equal_orbit_pos(* temp))
    {
        
        //Connect up temp node before head
        temp->connect_next(head);
        head = temp;
        
        success = 1;
    }

    //recursive call
    else
    {
        delete temp;
        success = add_planet(head->go_next(), to_add);
    }

    return success;
}



//Displays the sun and all planets in order of distance from sun
//INPUT: no arguments
//OUTPUT: return type: int (total number of planets)
int solar_system::display(void)
{
    //Flag failure if no sun name
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
    if (!rear)
        return 0;

    return display_all_planets(rear->go_next()); 
}



//Displays all planets in order of orbit position - recursively
//INPUT: 1 argument: head pointer 
//OUTPUT: return type: int (total number of planets)
int solar_system::display_all_planets(node * head)
{
    int displayed = 0;

    //Base case
    if (head == rear)
    {
        if (head->display_planet())
        return ++displayed;
    }

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
    if (!rear)
        return 0;

    return display_habitable_planets(rear->go_next()); 
}



//Displays all habitable planets - recursively
//INPUT: 1 argument: head pointer 
//OUTPUT: return type: int (number of habitable planets)
int solar_system::display_habitable_planets(node * head)
{
    int habitable = 0;      //Total number of habitable planets

    //Base case
    if (head == rear)
    {
        if (head->check_habitability() == 1)
        {
            if (head->display_planet())
                ++habitable;
        }
        return habitable;
    }

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
    //If null argument
    if (!sun_to_match)
        return -1;

    bool result = false;            //Value to return 
    int sun_to_match_len = strlen(sun_to_match);    //length of sun name to match
    int sun_len = strlen(sun);                      //length of current sun name
    char * sun_to_match_lower = new char[sun_to_match_len + 1]; //To convert to lowercase
    char * sun_lower = new char[sun_len + 1];       //to convert to lower case

    //convert to lower case
    for (int i = 0; i < sun_to_match_len; ++i)
        sun_to_match_lower[i] = tolower(sun_to_match[i]);
    sun_to_match_lower[sun_to_match_len] = '\0';

    for (int i = 0; i < sun_len; ++i)
        sun_lower[i] = tolower(sun[i]);
    sun_lower[sun_to_match_len] = '\0';

    //Flag if sun matches argument
    if (sun_to_match && strcmp(sun_to_match_lower, sun_lower) == 0)
        result = true;

    //Deallocate temporary variable
    if (sun_to_match_lower)
    {
        delete [] sun_to_match_lower;
        sun_to_match_lower = NULL;
    }
    if (sun_lower)
    {
        delete [] sun_lower;
        sun_lower = NULL;
    }

    return result;
}



//Explores a specific planet that matches name
//INPUT: 1 argument: planet name to match
//OUTPUT: return type: int (-2: null argument, -1: no planets in list, 
//0: no match found, 1: match found, unable to land (gas planet),
//2: match found, landed successfully (terr planet), not habitable,
//3: match found, landed successfully (terr planet), habitable!
int solar_system::explore_planet(char * planet_name, int & fuel_cost)
{
    node * current = NULL;      //To traverse DLL of planets
    bool planet_found = false;  //Flag if match is found
    int result = 0;             //Value to return

    //If null argument, flag failure
    if (!planet_name)
        return -2;

    //If no planets in list, flag failure
    if (!rear)
        return -1;

    //Otherwise, start traversing at head
    current = rear->go_next();
   
    //Repeat until a match is found or end of list 
    while (current != rear && !planet_found)
    {
        //If its a match, flag as found
        if (current->find_planet(planet_name))
            planet_found = true;

        //Otherwise go to next node
        else
            current = current->go_next();
    }

    //Last node
    if (!planet_found)
    {
        //If its a match, flag as found
        if (rear->find_planet(planet_name))
            planet_found = true;
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

        //Update fuel cost
        fuel_cost = current->calculate_fuel_cost();
    }

    //If planet not found
    else
        result = 0;       

    return result; 
}



//Displays only planet names
//INPUT: no arguments
//OUTPUT: return type: int (number of planets displayed)
int solar_system::display_planet_names(void)
{
    //Empty list
    if (!rear)
        return 0;

    return display_planet_names(rear->go_next());
}



//Displays all planets names in order of orbit position - recursively
//INPUT: 1 argument: head pointer 
//OUTPUT: return type: int (total number of planets)
int solar_system::display_planet_names(node * head)
{
    int displayed = 0;  //total number of planets

    //Base case
    if (head == rear)
    {
        if (head->display_planet_name())
        return ++displayed;
    }

    //Display current planet
    if (head->display_planet_name())
        ++displayed;

    //Recursive call to next node
    displayed += display_planet_names(head->go_next());

    return displayed;
}



//Displays sun name
//INPUT: no arguments
//OUTPUT: return type: int (0/1 - failure/success)
int solar_system::display_sun(void)
{
    //Null data member
    if (!sun)
        return 0;

    //Display sun name
    cout << "\t" << sun << endl;
    return 1;
}



//Default constructor - initializes all data members to zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
galaxy::galaxy(): galaxy_array(NULL), galaxy_array_size(0), num_solar_sys(0) {}



//Constructor with argument array size
//INPUT: 1 argument: size of array
//OUTPUT: no return value
galaxy::galaxy(int array_size)
{
    //Create an array of argument size (if valid size)
    if (array_size > 0)
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



//Copy constructor - copies argument galaxy object
//INPUT: 1 argument: a galaxy object to copy
//OUTPUT: no return value
galaxy::galaxy(const galaxy & to_copy)
{
    num_solar_sys = 0;      //Total number of solar systems copied

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
//OUTPUT: return type: int (0 - failure, array is full, 
//1 - success
int galaxy::add_solar_system(const solar_system & to_add)
{
    //Check if array is full
    if (num_solar_sys == galaxy_array_size)
        return 0;

    //Copy argument solar system into array
    //num_solar_sys is the next non-empty index
    if (galaxy_array[num_solar_sys].copy_solar_system(to_add) > -1)
        ++num_solar_sys;

    return 1;
} 



//Displays all solar systems and their planets
//INPUT: no arguments
//OUTPUT: return type: int (total number of planets)
int galaxy::display_all(void)
{
    int displayed = 0;      //Total number of planets

    //For each solar system, display all planets
    for (int i = 0; i < num_solar_sys; ++i)
        displayed += galaxy_array[i].display();

    return displayed;
}



//Displays all solar systems and their planets
//INPUT: 1 argument: total planets (by reference)
//OUTPUT: return type: int (total number of planets)
int galaxy::display_all(int & num_sol_sys)
{
    int displayed = 0;  //Total number of planets

    //Update argument
    num_sol_sys = num_solar_sys;

    //For each solar system, display all planets
    for (int i = 0; i < num_solar_sys; ++i)
        displayed += galaxy_array[i].display();

    return displayed;
}



//Displays all habitable planets in all solar systems
//INPUT: no arguments
//OUTPUT: return type: int (total number of habitable planets)
int galaxy::display_all_hab_planets(void)
{
    int displayed = 0;  //Total habitable planets

    //For each solar system, display all habitable planets
    for (int i = 0; i < num_solar_sys; ++i)
        displayed += galaxy_array[i].display_habitable_planets();

    return displayed;
}



//Loads galaxy from file
//INPUT: 1 argument: filename to load from
//OUTPUT: return type: int (number of solar systems loaded) 
int galaxy::load_file(const char filename[])
{
    solar_system * new_sol_sys;     //Temporary pointer to read each solar system
    char sun_name[101];             //Temporary variable to read in sun name
    char all_planets[801];          //Temporary variable to read in planet name
    int sol_sys_added = 0;          //Value to return
    ifstream in_file;               //File variable for input
  
    //Flag failure if galaxy array not yet set
    if (!galaxy_array)
        return -1;
 
    //Connect to particular file
    in_file.open(filename);

    //If unable to find file
    if (!in_file)
        return 0;

    //If connected...
    else
    {
        //Attempt to read first piece of data (event name) 
        in_file.get(sun_name, 101, '|');
        in_file.ignore(1000, '|');

        //Repeat until end of file or not connected to file
        while (in_file && !in_file.eof())
        {
            //Read in all planets...
            in_file.get(all_planets, 801, '\n');
            in_file.ignore(1000, '\n');

            //Create solar system with read in details
            new_sol_sys = new solar_system(sun_name);

            //Extract individual planets separated by comma 
            //and insert into solar system
            if (extract_planets(sun_name, all_planets, new_sol_sys))
            {
                //Add solar system into galaxy
                if (add_solar_system(* new_sol_sys))
                    //Increment number of solar systems loaded
                    ++sol_sys_added;
            }

            //Reset solar system
            delete new_sol_sys;
            new_sol_sys = NULL;

            //Prime the pump for next read in
            in_file.get(sun_name, 101, '|');
            in_file.ignore(100, '|');
        }
        
        //Close file and clear file variable
        in_file.close();
        in_file.clear();
    }
    
    return sol_sys_added;
}



//Extracts planet names and builds solar system
//INPUT: 3 arguments: sun name, char array to extract planet names from, solar
//system to build
//OUTPUT: return type: int (number of planets added) 
int galaxy::extract_planets(char * sun_name, char * all_planets, solar_system * sol_sys)
{
    planet * new_planet = NULL;    //Temporary pointer to add each planet to solar system
    char planet_name[100];         //Extracted planet name
    char * dest = planet_name;     //to traverse extracted planet name
    int size = 0;           //Length of all_planets array
    int index = 0;          //Loop variable -  array index
    int num_planets = 0;      //Number of planets extracted
    int timer = 0;          //To extract planet type at beginning of each name
    int type = 0;           //Type of planet (0 - terrestrial, 1 - gas)
  
    //Flag failure if null arguments 
    if (!all_planets||!sol_sys||!sun_name)
        return 0;

    //Find length of all planets array
    size = strlen(all_planets);

    //Traverse each character of array 
    while (index <= size)
    {
        //Copy character if not comma or terminating null
        if (all_planets[index] != ',' && all_planets[index] != '\0')
        {
            //Get type of planet
            if (!timer)
            {
                if (all_planets[index] == '0')
                    type = 0;
                else if (all_planets[index] == '1')
                    type = 1;
                
                ++index;
                ++timer;
            }

            //copy character into destination array
            else
            {
                * dest = all_planets[index];
                ++dest;
                ++index;
                ++timer;
            }
        }

        //If comma - end of word
        else 
        {
            //terminate word with null character
            * dest = '\0';

            //Increment index
            ++index;

            //Reset timer
            timer = 0;        

            //Create planet with extracted name and type
            if (type == 0)
                new_planet = new gas_planet(planet_name, sun_name);
            else if (type == 1)
                new_planet = new terr_planet(planet_name, sun_name);

            //Add planet to solar system
            if (sol_sys->add_planet(new_planet))
                ++num_planets;

            //Reset planet name
            strcpy(planet_name, "");
            dest = planet_name;

            //Reset temporary planet
            delete new_planet;
            new_planet = NULL;
        }
    }
    
    return num_planets;
}



//Displays sun name for each solar system        
//INPUT: no arguments
//OUTPUT: return type: int (total number of solar systems)
int galaxy::display_all_suns(void)
{
    int displayed = 0;      //Total number of solar systems

    //For each solar system, display all planets
    for (int i = 0; i < num_solar_sys; ++i)
        displayed += galaxy_array[i].display_sun();

    return displayed;
}



//Default constructor - initializes all data members to zero equivalent
//INPUT: no arguments
//OUTPUT: no return value
spaceship::spaceship(): fuel(0), current_solar_sys(-1) {}



//Constructor with arguments
//INPUT: 1 arguments (intial fuel value, total number of solar systems)
//OUTPUT: no return value
spaceship::spaceship(int full_fuel, int num_sol_sys): galaxy(num_sol_sys), fuel(full_fuel), current_solar_sys(-1) {}



//Sets new value for current solar system index
//INPUT: 1 argument: a sun name to match
//OUTPUT: return type: int (-1 - null argument, 0/1 - failure/success)
int spaceship::select_solar_sys(char * sun_name_to_match)
{
    bool found = false;     //Flag if match is found
    int index = -1;         //Index of matching solar system

    //Null argument - flag failure
    if (!sun_name_to_match)
        return -1;

    //Repeat for each solar system until match found or end of array
    for (int i = 0; i < num_solar_sys && !found; ++i)
    {
        //If match, flag as found and get index number
        if (galaxy_array[i].find_sun(sun_name_to_match) == 1)
        {
            index = i;
            found = true;
        }
    }

    //Set current solar system index
    current_solar_sys = index;

    return found;
}



//Explores a selected planet if fuel > 0 in current solar system
//and supplies updates fuel level through argument
//INPUT: 1 argument: current fuel to update
//OUTPUT: return type: int
//(-6: no existing solar systems, -5: current solar system not set
//-4: out of fuel
//-2: null argument, -1: no planets in list, 
//0: no match found, 1: match found, unable to land (gas planet),
//2: match found, landed successfully (terr planet), not habitable,
//3: match found, landed successfully (terr planet), habitable!
//4: failure)
int spaceship::explore_a_planet(int & current_fuel)
{
    int planet_fuel_cost = 0;                   //Cost to visit matching planet
    char planet_name_to_explore [50] = {'\0'};  //to read in name to match
    int result = 4;                             //value to return

    //check if any existing solar systems
    if (!num_solar_sys)
        return -6;

    //Check current solar system
    if (current_solar_sys == -1)
        return -5;

    //Check fuel
    if (!(fuel > 0))
        return -4;

    //Display planet names to choose from
    if (galaxy_array[current_solar_sys].display_planet_names())
    {
        //Read in planet name to visit
        cout << "Enter name of planet to visit: ";
        cin.get(planet_name_to_explore, 100, '\n');
        cin.ignore(100, '\n');

        //Explore planet
        result = galaxy_array[current_solar_sys].explore_planet(planet_name_to_explore, planet_fuel_cost);

        //Update fuel - deduct fuel consumed for visiting planet
        current_fuel = consume_fuel(planet_fuel_cost);
    }

    //Return result and current fuel level
    return result;
}



//Updates fuel - deducts argument value
//INPUT: 1 argument: value to deduct 
//OUTPUT: return type: int (current fuel value after deduction)
int spaceship::consume_fuel(int deduct)
{
    fuel -= deduct;
    return fuel;
}


