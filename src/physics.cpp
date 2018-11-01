#include <cmath>
#include "physics.hpp"

Physics::Physics(std::map<std::string, std::string>* cfg) 
    : G(stod((*cfg)["gravity_constant"]))
{
    b1 = new Body;
    b2 = new Body;

    b1->name = (*cfg)["first_body_name"];
    b1->x = stod((*cfg)["first_body_x"]);
    b1->y = stod((*cfg)["first_body_y"]);
    b1->v_x = stod((*cfg)["first_body_x_velocity"]);
    b1->v_y = stod((*cfg)["first_body_y_velocity"]);
    b1->radius = stod((*cfg)["first_body_radius_px"]);
    b1->mass_kg = stod((*cfg)["first_body_mass_kg"]);
    b2->name = (*cfg)["second_body_name"];
    b2->x = stod((*cfg)["second_body_x"]);
    b2->y = stod((*cfg)["second_body_y"]);
    b2->v_x = stod((*cfg)["second_body_x_velocity"]);
    b2->v_y = stod((*cfg)["second_body_y_velocity"]);
    b2->radius = stod((*cfg)["second_body_radius_px"]);
    b2->mass_kg = stod((*cfg)["second_body_mass_kg"]);
}

Physics::~Physics()
{
    free(b1);
    free(b2);
}

void Physics::update()
{
    double r_x = b2->x - b1->x;
    double r_y = b2->y - b1->y;
    r = sqrt((r_x * r_x) + (r_y * r_y));
    double sina = (r_y / r);
    double cosa = r_x / r;
    fg = G * b1->mass_kg * b2->mass_kg / (r * r);

    if (r <= b1->radius + b2->radius)
    {
        b1->a_x = b1->a_y = b1->v_x = b1->v_y = b2->a_x = b2->a_y = b2->v_x = b2->v_y = 0;
        return;
    }

    b1->a_x = (fg * cosa) / b1->mass_kg;
    b2->a_x =  -(fg * cosa) / b2->mass_kg;

    b1->a_y = (fg * sina) / b1->mass_kg;
    b2->a_y = -(fg * sina) / b2->mass_kg;

    b1->v_x += b1->a_x;
    b2->v_x += b2->a_x;
    
    b1->v_y += b1->a_y;
    b2->v_y += b2->a_y;

    b1->x += b1->v_x;
    b2->x += b2->v_x;

    b1->y += b1->v_y;
    b2->y += b2->v_y;
}