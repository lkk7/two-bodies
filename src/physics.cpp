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
    b1->a_x = stod((*cfg)["first_body_x_acceleration"]);
    b1->a_y = stod((*cfg)["first_body_y_acceleration"]);
    b1->radius = stod((*cfg)["first_body_radius_px"]);
    b1->mass_kg = stod((*cfg)["first_body_mass_kg"]);
    b2->name = (*cfg)["second_body_name"];
    b2->x = stod((*cfg)["second_body_x"]);
    b2->y = stod((*cfg)["second_body_y"]);
    b2->v_x = stod((*cfg)["second_body_x_velocity"]);
    b2->v_y = stod((*cfg)["second_body_y_velocity"]);
    b2->a_x = stod((*cfg)["second_body_x_acceleration"]);
    b2->a_y = stod((*cfg)["second_body_y_acceleration"]);
    b2->radius = stod((*cfg)["second_body_radius_px"]);
    b2->mass_kg = stod((*cfg)["second_body_mass_kg"]);

    std::cout << "G constant: " << G << "\n";
}

Physics::~Physics()
{
    free(b1);
    free(b2);
}

void Physics::update()
{
    double r_x = abs(b1->x - b2->x);
    double r_y = abs(b1->y - b2->y);
    double f_x = G * b1->mass_kg * b2->mass_kg / (r_x * r_x);
    double f_y = G * b1->mass_kg * b2->mass_kg / (r_y * r_y);

    
}