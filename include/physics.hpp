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

        /* Getters */
        const Body* get_b1() {return b1;}
        const Body* get_b2() {return b2;}
        const double get_r() {return r;}
        const double get_fg() {return fg;}

        /* Update state of physics */
        void update();

        /* Return information vector about physics state */
        void update_info_vector();

        /* Return string info about given variable */
        std::string return_info(double x);

    private:
        /* Gravity constant */
        double G;

        /* Current force between two bodies */
        double fg;

        /*Current distance between two bodies */
        double r;
        
        /* Two bodies */
        Body* b1;
        Body* b2;
};

#endif