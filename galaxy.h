//Filename: galaxy.h

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  2
//Date:     07/21/2017

//This program manages the classes, 'node', 'solar_system', 'galaxy', and
// 'spaceship'. The galaxy has been implemented
//as a dynamically allocated array of solar system objects. Each solar
//system contains a sun and a circular linked list (CLL) of planets arranged
//in sorted order of the planets' orbital position around the sun. The 'node' class
//manages a single node of the CLL, which contains a pointer to a 'planet'.
//Since 'planet' is an abstract base class from which the planet types (terrestrial, 
//gas planets) have been derived, each node's pointer can be set to point to
//any type of planet. The 'spaceship' is derived from the galaxy class and manages
//a 'fuel' data member based on planets visited

#include "planet.h"



//Class Interfaces
class node              //Manages a single node of a CLL - contains pointer to a planet
{
    public:
        node();                     //Default constructor - initializes data members to zero equivalent
        node(planet * to_copy);     //Constructor with a planet to copy
        node(const node & to_copy); //Copy constructor - copied argument node
        ~node();                    //Destructor - releases dynamic memory

        node *& go_next(void);      //Returns node's next pointer by reference
        void connect_next(node * connection);   //Sets next pointer to argument location

        int display_planet(void);           //Displays all planet details
        int land_on_planet(void);           //Allows landing or not based on planet type
        int check_habitability(void);       //Checks habitability of planet in node
        int get_dist(void);                 //Returns distance from sun of planet in node
        int find_planet(char * to_match);   //Compares planet name with argument
        int is_greater_or_equal_orbit_pos(const node & to_compare);    //Compares orbit positions of argument 
                                                          //planet with planet in node
        int calculate_fuel_cost(void);      //Calculates cost of fuel to visit planet
        int display_planet_name(void);      //Displays planet name        

    protected:
        planet * a_planet;      //pointer to a planet of any type
        node * next;            //Pointer to next node
};



class solar_system      //Manages a solar-system - contains a CLL of nodes which each point to a planet
{
    public:
        solar_system();                             //Default constructor - initializes data members to zero equivalent
        solar_system(char * sun_name);              //Constructor with sun name as argument
        solar_system(const solar_system & to_copy); //Copy constructor - copies argument solar system
        ~solar_system();                            //Destructor - release all dynamic memory

        int add_planet(planet * to_add);            //Adds a new planet to the CLL in sorted order of orbital position
        int display(void);                          //Displays sun and all planets
        int display_all_planets(void);              //Displays all planets
        int display_habitable_planets(void);        //Displays all habitable planets 
        int explore_planet(char * planet_name, int & fuel_cost);     //Explores planet with name matching arguments - checks landing
                                                    //and habitability
        int find_sun(char * sun_to_match);          //Compares sun name with argument
        int copy_solar_system(const solar_system & to_copy);    //Copies data members of argument solar system
        int display_sun(void);                      //Displays sun name
        int display_planet_names(void);             //Displays only planet names

    private:
        char * sun;    //Name of the sun
        node * rear;   //rear pointer to cll of planet nodes

        int remove_all(node * & rear, node * & fix_rear);            //Removes all nodes in CLL recursively
        int copy_cll(node * & head, node * & fix_head, node * src_head, node * src_rear, int & copied); //Copies CLL recursively
        int add_planet(node * & head, planet * to_add);        //Add new planet in sorted order
                                                                                     //to CLL - recursively
        int display_all_planets(node * head);                        //Displays all nodes in CLL - recursively
        int display_habitable_planets(node * head);                  //Displays all nodes with habitable planets - recursively
        int display_planet_names(node * head);                       //Displays all planets names 
};



class galaxy        //Manages an array of solar systems
{
    public:
        galaxy();                       //Default constructor - initializes all data members to zero equivalent
        galaxy(int array_size);         //Constructor - sets array of argument size
        galaxy(const galaxy & to_copy); //Copy constructor - copies argument galaxy object
        ~galaxy();                      //Destructor - releases dynamic memory

        int load_file(const char filename[]);               //Loads galaxy from file
        int add_solar_system(const solar_system & to_add);  //Adds new solar system to galaxy
        int display_all(void);                              //Displays all solar systems in galaxy
        int display_all(int & num_sol_sys);                 //Dislays all solar systems, supplies number of solar systems
                                                            //through argument
        int display_all_hab_planets(void);                  //Displays all habitable planets in all solar systems
        int display_all_suns(void);                         //Displays sun name for each solar system        

    protected:
        solar_system * galaxy_array;    //Dynamic array of solar systems
        int galaxy_array_size;          //size of array
        int num_solar_sys;              //Number of items currently in array

        int extract_planets(char * sun_name, char * all_planets, solar_system * sol_sys);   //Extracts planet names from argument char array
                                                                                            //and builds a solar system with the data
};



class spaceship: public galaxy  //Manages a 'spaceship' ("is a" galaxy)
{
    public:
        spaceship();                //Default constructor - initializes data member to zero
        spaceship(int full_fuel, int tot_sol_sys);  //Constructor with arguments
        
        int explore_a_planet(int & current_fuel);   //Explores selected planet in current solar system
                                                    //and uses up fuel accordingly. Only allow if fuel > 0.
        int select_solar_sys(char * sun_to_match);  //Sets new value for current solar system index
        
    protected:
        int fuel;                       //Reduces each time a planet is visited
        int current_solar_sys;          //current index number in galaxy array

        int consume_fuel(int deduct);   //Deducts argument value from fuel value
};

