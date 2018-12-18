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
        node(const node & to_copy); 
        ~node();

        node *& go_next(void);
        node *& go_prev(void);
        void connect_next(node * connection);
        void connect_prev(node * connection);

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
        solar_system(const solar_system & to_copy); 
        ~solar_system();

        int add_planet(planet * to_add);     
        int display(void);
        int display_all_planets(void);
        int display_habitable_planets(void);
        int explore_planet(char * planet_name);
        int find_sun(char * sun_to_match);
        int copy_solar_system(const solar_system & to_copy);

    private:
        char * sun;
        node * head;
        node * tail;  

        int remove_all(node * & head);    //removes all nodes in dll - recursively
        int copy_dll(node * & dest, node * & dest_tail, node * src); //Recursive function - copies DLL
        int add_planet(node * & head, node * & tail, planet * to_add, int new_dist);
        int display_all_planets(node * head);
        int display_habitable_planets(node * head);
};



class galaxy
{
    public:
        galaxy();
        galaxy(int array_size);
        galaxy(const galaxy & to_copy);
        ~galaxy();

        int load_file(const char filename[]);
        int add_solar_system(const solar_system & to_add);
        int display_all(void);
        int display_all_hab_planets(void);
//        int explore_planet(char * sun_name, char * planet_name);

    private:
        solar_system * galaxy_array;    //Dynamic array of solar systems
        int galaxy_array_size;
        int num_solar_sys;

        int extract_planets(char * sun_name, char * all_planets, solar_system * sol_sys);
};
