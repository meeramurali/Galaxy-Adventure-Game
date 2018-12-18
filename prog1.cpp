//Filename: prog1.cpp

//Name:     Meera Murali
//Email:    mmurali@pdx.edu
//Class:    202
//Program:  1
//Date:     07/14/2017

//This program manages the planet class.........

#include "galaxy.h"


//Prototypes
void display_menu(char & choice);   //Displays textbased menu and reads user choice
void get_data(char * & dest);       //Gets data from the user and sizes
                                    //the argument array just right

//main function
int main()
{
    char menu_choice = 'a';  //user choice for menu operation
    int result = 0;          //Value returned by member function
    char name1[] = "Earth";
    char name2[] = "Jupiter";
    char name3[] = "Mars";
    char name4[] = "Uranus";
    char sun1[] = "Sun";

    terr_planet A(name1, sun1);
    gas_planet B(name2, sun1);
    planet * C_ptr;
    planet * D_ptr;

    //Display planets
    cout << "\n\nTerrestrial planet: " << endl;
    if (!A.display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << A.allow_landing() << endl;
    if (A.check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    cout << "\n\nGas planet: " << endl;
    if (!B.display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << B.allow_landing() << endl;
    if (B.check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    C_ptr = new terr_planet(name3, sun1);
    D_ptr = new gas_planet(name4, sun1); 

    //Display planets
    cout << "\n\nTerrestrial planet: " << endl;
    if (!C_ptr->display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << C_ptr->allow_landing() << endl;
    if (C_ptr->check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;

    cout << "\n\nGas planet: " << endl;
    if (!D_ptr->display())
        cout << "Cannot display!" << endl;
    cout << "Landing allowed? " << D_ptr->allow_landing() << endl;
    if (D_ptr->check_habitability())
        cout << "HABITABLE!!!" << endl;
    else
        cout << "NOT Habitable!" << endl;


    delete C_ptr;
    delete D_ptr;
/*
    //Repeat until user wants to quit, i.e. menu choice is 'h'
    do 
    {  
        //Display menu and get user choice 
        display_menu(menu_choice);
        
        //If choice is 'a', load data from file
        //Prompt user accordingly based on result
        if (menu_choice == 'a')
        {
            //Load data from file 
            if (test_graph.load_file(FILENAME))
                cout << "\n*** Data loaded from file: " << FILENAME << " ***" <<  endl;
            else
                cout << "\n*** File not found! ***" << endl;
        } 
        
        //If choice is 'b', insert new vertex into graph
        //Prompt user accordingly based on result
        else if (menu_choice == 'b')
        {
            //Read in name of vertex to insert
            cout << "Enter name of trailhead/trail intersection "
                 << "(e.g. Trailhead - Ridge Trail): ";
            get_data(new_vertex_name);
            

            //Insert new vertex into graph
            result = test_graph.insert_vertex(new_vertex_name);
            if (!result)
                cout << "\n*** Unable to insert!! ***" << endl;
            else
                cout << "\n*** Vertex inserted in graph ***" << endl;
            
            //Destroy temporary variables
            delete [] new_vertex_name;
        }
        
        //If choice is 'c', insert a new edge between two vertices
        //Prompt user accordingly based on result
        else if (menu_choice == 'c')
        {
            //Read in names of vertices to add edge between
            cout << "Enter name of first vertex (e.g. Trailhead - Ridge Trail): ";
            get_data(vertex_1);
            cout << "\nEnter name of second vertex (e.g. Trailhead - Newton Road): ";
            get_data(vertex_2);

            //Read in trail name, miles and comments
            cout << "\nEnter trail name (e.g. Ridge trail): ";
            get_data(trail);
            cout << "\nEnter length of trail segment in miles (e.g. 1.5): ";
            get_data(mileage);
            cout << "\nEnter any additional information (e.g. Dog-friendly): ";
            get_data(trail_comments);
            
            //Add edge between the two vertices
            result = test_graph.insert_edge(vertex_1, vertex_2, trail, 
                                            mileage, trail_comments);
            if (result == -1)
                cout << "\n*** No matches found! ***" << endl;

            else if (result > 0)
            {
                result = test_graph.insert_edge(vertex_2, vertex_1, trail, 
                                                mileage, trail_comments);
                cout << "\n*** Edge inserted between " << vertex_1 << " and " 
                     << vertex_2 << " ***" << endl;
            }

            //Destroy temporary variables
            delete [] vertex_1;
            delete [] vertex_2;
            delete [] trail;
            delete [] mileage;
            delete [] trail_comments;
        }
        
        //If choice is 'd', display all vertices
        //Prompt user accordingly based on result
        else if (menu_choice == 'd')
        {
            //Display all vertices
            result = test_graph.display_vertices();
            if (!result)
                cout << "\n*** Empty graph! Nothing to display! ***" << endl;

            else
                cout << "\n*** " << result << " vertice(s) in graph ***" << endl;
        }
        
        //If choice is 'e', display all paths leading from a specific vertex
        //Prompt user accordingly based on result
        else if (menu_choice == 'e')
        {
            //Read in name of vertex
            cout << "Enter name of vertex to display connecting vertices for "
                 << "(e.g. Trailhead - Ridge Trail): ";
            get_data(key_name);
            
            //Display all events sorted by name
            cout << "\nPaths: " << endl;
            result = test_graph.display_paths(key_name);
            
            if (result == -1)
                cout << "None" << "\n\n*** No such vertex found! ***" << endl;

            else
                cout << "\n*** " << result << " connecting path(s) found! ***" << endl;

            //Destroy temporary variables
            delete [] key_name;
            key_name = NULL;
        }

        //If choice is 'f', display all connecting vertices for a specific vertex
        //Prompt user accordingly based on result
        else if (menu_choice == 'f')
        {
            //Read in name of vertex
            cout << "Enter name of vertex to display connecting vertices for "
                 << "(e.g. Trailhead - Ridge Trail): ";
            get_data(key_name);
            
            //Display all events sorted by name
            cout << "\nConnected to: " << endl;
            result = test_graph.display_adjacent(key_name);
            
            if (result == -1)
                cout << "None" << "\n\n*** No such vertex found! ***" << endl;

            else
                cout << "\n*** " << result << " connecting vertice(s) found! ***" << endl;

            //Destroy temporary variables
            delete [] key_name;
            key_name = NULL;
        }

        //If choice is 'g', display all vertices and their respective connections
        //Prompt user accordingly based on result
        else if (menu_choice == 'g')
        {
            //Display all vertices and connections
            result = test_graph.display_all();
            if (!result)
                cout << "\n*** Empty graph! Nothing to display! ***" << endl;

            else
                cout << "\n*** " << result << " vertice(s) in graph ***" << endl;
        }
    }
    while (menu_choice != 'h'); //Stop if choice is 'h'
*/
    return 0;
}



//Display menu and get user choice
//INPUT: 1 argument: user choice (char array passed by reference)
//OUTPUT: Argument userchoice modified
void display_menu(char & choice)
{
    //Repeat until user chooses a valid menu option
    do
    {
        //Display menu of operations to user
        cout << "\n\nSelect operation:" << endl;
        cout << "a. Load galaxy from file" << endl
             << "b. Display galaxy" << endl
             << "c. Display all unvisited solar systems" << endl
             << "d. Display all habitable planets" << endl
             << "h. Quit" << endl
             << "Enter a letter from 'a' to 'h': ";

        //Read in user response
        cin >> choice;
        cin.ignore(100, '\n');

        //Convert to lowercase
        choice = tolower(choice);
        
        //If choice is invalid, prompt user
        if (!(choice >= 'a' && choice <= 'h'))
            cout << "\n\n***Invalid entry! Try again...***" << endl;
    }
    while (!(choice >= 'a' && choice <= 'h'));

    return;
}



//Gets data from the user and sizes the argument array just right
//INPUT: 1 argument: a char pointer passed by reference
//OUTPUT: modified argument array, return nothing
void get_data(char * & dest)
{
    char temp [100];    //Temporary array to read in data and size
                        //argument array just right

    //Read in data from user into temp
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');

    //Allocate memory sized just right, based on contents of temp
    dest = new char [strlen(temp) + 1];

    //Copy data from temp
    strcpy(dest, temp);

    return;
}
