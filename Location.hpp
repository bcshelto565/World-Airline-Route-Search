#include <string.h>
#include <stdio.h>
using namespace std;

class Location{
    private:
        string name;
        
    public:
        Location();                         // Constructor function
        ~Location();                        // Destructor function
        Location* destinations[];           // array for the linked destinations, I'm not sure if the idea of an array is the best but im pretty sure we want to use pointers to point to other locations
        Location* departures[];             // array for the linked departures, I'm not sure if the idea of an array is the best but im pretty sure we want to use pointers to point to other locations

}