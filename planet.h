//Filename: planet.h

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  2
//Date:     07/21/2017

//This program manages the planet class and its derived types.
//The 'planet' is an abstract base class from which the planet types (terrestrial, 
//gas planets) have been derived.
//Two types of planets have been implemented:
//TERRESTRIAL planets - Allow landing since they have solid surfaces, have zero or few
//moons, a smaller range of size (radius), and closer to the sun
//GAS planets - Do not allow landing since they are gaseous, have a large number of
//moons, larger range of size (radius), amd further away from the sun


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
        planet();                                       //Default constructor - initializes data members to zero eq.
        planet(char * planet_name, char * sun_name);    //Constructor with planet name and sun as arguments
        planet(const planet & to_copy);                 //Copy constructor - copies argument planet object
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
        int get_orbit_pos(void);          //Returns orbit position value
        int display_name(void);           //Displays name of planet
        int calculate_fuel_cost(void);    //Returns fuel cost to visit planet based on size and 
                                          //number of moons

    protected:
        char * name;                    //Name of the planet
        char * sun;                     //Name of the sun that its orbiting
        int size;                       //Size in number of thousand miles radius
        int dist;                       //Distance from sun in number of million miles
        int num_moons;                  //Number of moons
        int orbit_pos;                  //position in orbit around sun in degrees
        virtual int set_size() = 0;     //Sets random size in a specific range based on derived
                                        //'terrestrial planets' are smaller than 'gas planets'
        virtual int set_distance() = 0; //Sets random distance from sun in specific range based on 
                                        //derived - 'gas planets' are at greater distance from sun
                                        //than 'terrestrial planets'
        virtual int set_moons() = 0;    //Sets random number of moons in specific range based on
                                        //derived - 'terrestrial planets' have no or few moons and
                                        //'gas planets' have large number of moons
        int set_orbit_pos(void);        //Sets random position in range 0 - 359 degrees angle
                                        //from line of reference 
};



class terr_planet: public planet     //Manages a terrestrial planet ("is a" planet)
{
    public:
        terr_planet();                                       //Default constructor - initializes all data members to zero eq.
        terr_planet(char * planet_name, char * sun_name);    //Constructor with planet and sun names as arguments
        terr_planet(const terr_planet & to_copy);            //Copy constructor - copies argument terr_planet object
        terr_planet(const planet * to_copy);                 //Copy constructor - copies argument planet object

        bool allow_landing(void);   //Always returns true to allow landing

    protected:
        int set_size(void);         //Sets random size in range 1-5 (thousand miles radius)
        int set_distance(void);     //Sets random distance from sun in range 20-300 (million miles)
        int set_moons(void);        //Sets random number of moons in range 0-3
};
   

 
class gas_planet: public planet     //Manages a gas planet ("is a" planet)
{
    public:
        gas_planet();                                       //Default constructor - initializes data members to zero eq.
        gas_planet(char * planet_name, char * sun_name);    //Constructor with planet and sun names arguments
        gas_planet(const gas_planet & to_copy);             //Copy constructor - copies argument gas planet object
        gas_planet(const planet * to_copy);                //Copy constructor - copies argument planet object

        bool allow_landing(void);   //Always returns false to not allow landing

    protected:
        int set_size(void);         //Sets random size in range 10-50 (thousand miles radius)
        int set_distance(void);     //Sets random distance from sun in range 500-1000 (million miles)
        int set_moons(void);        //Sets random number of moons in range 15-80
};
