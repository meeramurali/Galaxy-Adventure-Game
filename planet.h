//Filename: planet.h

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;



//Class Interfaces
class planet     //Abstract base class from which 'terrestrial_planet' and 'gas_planet' are derived
{
    public:
        planet();                                       //Default constructor
        planet(char * planet_name, char * sun_name);    //Constructor with arguments
        planet(const planet & to_copy);                 //Copy constructor
        virtual ~planet();                              //Destructor - Releases all dynamic memory

        int display(void);                //Displays all planet information
        bool check_atmos(void);           //Determines existence of atmosphere (based on values of
                                          //distance from sun and size)
        bool check_habitability(void);    //Determines if planet is habitable (based on distance
                                          //from sun and existence of atmosphere)
                                          //and 'gas planets' never allow landing (return false)
        int get_dist(void);               //Returns distance from sun value
        bool find_planet(char * to_match);//Compares argument with planet name
        virtual bool allow_landing(void) = 0; //'Terrestrial planets' always allow landing (return true)
//        int calc_grav_pull();             //Calculates gravitational pull (function of size and no.
                                          //of moons)
//        int calc_escape_vel();            //Calculates required escape velocity for spaceship to 
                                          //take off (based on gravitational pull)

    protected:
        char * name;                    //Name of the planet
        char * sun;                     //Name of the sun that its orbiting
        int size;                       //Size in number of thousand miles radius
        int dist;                       //Distance from sun in number of million miles
        int num_moons;                  //Number of moons

        virtual int set_size() = 0;     //Sets random size in a specific range based on derived
                                        //'terrestrial planets' are smaller than 'gas planets'
        virtual int set_distance() = 0; //Sets random distance from sun in specific range based on 
                                        //derived - 'gas planets' are at greater distance from sun
                                        //than 'terrestrial planets'
        virtual int set_moons() = 0;    //Sets random number of moons in specific range based on
                                        //derived - 'terrestrial planets' have no or few moons and
                                        //'gas planets' have large number of moons
};



class terr_planet: public planet     //Manages a terrestrial planet ("is a" planet)
{
    public:
        terr_planet();                                       //Default constructor
        terr_planet(char * planet_name, char * sun_name);    //Constructor with arguments
        terr_planet(const terr_planet & to_copy);            //Copy constructor
        terr_planet(const planet * to_copy);                 //Copy constructor

        bool allow_landing(void);   //Always returns true to allow landing

    protected:
        int set_size(void);         //Sets random size in range 1-5 (thousand miles radius)
        int set_distance(void);     //Sets random distance from sun in range 20-300 (million miles)
        int set_moons(void);        //Sets random number of moons in range 0-3
};
   

 
class gas_planet: public planet     //Manages a gas planet ("is a" planet)
{
    public:
        gas_planet();                                       //Default constructor
        gas_planet(char * planet_name, char * sun_name);    //Constructor with arguments
        gas_planet(const gas_planet & to_copy);             //Copy constructor
        gas_planet(const planet * to_copy);                //Copy constructor

        bool allow_landing(void);   //Always returns false to not allow landing

    protected:
        int set_size(void);         //Sets random size in range 10-50 (thousand miles radius)
        int set_distance(void);     //Sets random distance from sun in range 500-1000 (million miles)
        int set_moons(void);        //Sets random number of moons in range 15-80
};
