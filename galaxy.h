//Filename: galaxy.h

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "planet.h"



//Class Interfaces
class solar_system
{
    public:
        solar_system();
        solar_system(char * sun_name);
        solar_system(const solar_system & to_copy);
        ~solar_system();

        int add_planet(const planet & to_copy);
        int display_all_planets(void);
        int display_habitable_planets(void);
        int explore_planet(char * planet_name);
        int find_sun(void);

    private:
        char * sun;
        planet * head;
        planet * tail;  


        int remove_all(planet * & head);
        int copy_all(planet * & dest, planet * src); //Recursive function - copies DLL
};
