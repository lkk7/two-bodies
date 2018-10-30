#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <map>
#include <vector>


struct Body
{
    /* Position, velocities, radius and mass */
    double x, y, v_x, v_y, a_x, a_y, radius, mass_kg;
    std::string name;
};


class Physics
{
    public:
        /* State of the Physics after init */
        bool error;

        /* Sets necessary parameters of Physics */
        Physics(std::map<std::string, std::string>* cfg);

        ~Physics();

        /* Body getter */
        const Body* get_b1() {return b1;}
        const Body* get_b2() {return b2;}

        /* Update state of physics */
        void update();

    private:
        /* Gravity constant */
        double G;
        
        /* Two bodies */
        Body* b1;
        Body* b2;
};

#endif