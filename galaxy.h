//Filename: galaxy.h

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "planet.h"



//Class Interfaces
class node
{
    public:
        node();
        node(planet * to_copy);
//        node(const node & to_copy); 
//        ~node();

        node *& go_next(void);
        node *& go_prev(void);
        void connect_next(node * connection);
        void connect_prev(node * connection);
//        bool if_next(void);
//        bool if_prev(void);

        int display_planet(void);
        int land_on_planet(void);
        int check_habitability(void);
        int get_dist(void);
        int find_planet(char * to_match);

    protected:
        planet * a_planet;
        node * next;
        node * prev;
};



class solar_system
{
    public:
        solar_system();
        solar_system(char * sun_name);
//        solar_system(const solar_system & to_copy);  <<--- finish later
        ~solar_system();

//        int add_planet(planet * to_add);          <<--- finish later
        int display_all_planets(void);
        int display_habitable_planets(void);
        int explore_planet(char * planet_name);
        int find_sun(char * sun_to_match);

    private:
        char * sun;
        node * head;
        node * tail;  

        int remove_all(node * & head);    //removes all nodes in dll - recursively
//        int copy_dll(node * & dest, node * src); //Recursive function - copies DLL
        int display_all_planets(node * head);
        int display_habitable_planets(node * head);
};



class galaxy
{
    public:
        galaxy();
        galaxy(const galaxy & to_copy);
        ~galaxy();

    private:
        solar_system * galaxy_array;    //Dynamic array of solar systems
        int galaxy_array_size;
        int num_solar_sys;
};
