#include <chrono>
#include "physics.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include "readcfg.hpp"

int main()
{

    std::map<std::string, std::string>* cfg = new std::map<std::string, std::string> {
        {"window_width", "1-"},
        {"window_height", "12"},
        {"window_name", ""},
        {"gravity_constant", ""},
        {"first_body_name", ""},
        {"first_body_x", ""},
        {"first_body_y", ""},
        {"first_body_x_velocity", ""},
        {"first_body_y_velocity", ""},
        {"first_body_x_acceleration", ""},
        {"first_body_y_acceleration", ""},
        {"first_body_radius_px", ""},
        {"first_body_mass_kg", ""},
        {"second_body_name", ""},
        {"second_body_x", ""},
        {"second_body_y", ""},
        {"second_body_x_velocity", ""},
        {"second_body_y_velocity", ""},
        {"second_body_x_acceleration", ""},
        {"second_body_y_acceleration", ""},
        {"second_body_radius_px", ""},
        {"second_body_mass_kg", ""}
    };
    
    if (!readcfg(*cfg)) return 1;
    
    Graphics* graphics = new Graphics(cfg);
    Physics* physics = new Physics(cfg);

    while (handle_events())
    {
        /* Fixed ~50 FPS. Changing will affect physics state update speed */
        auto now = std::chrono::high_resolution_clock::now();
        physics->update();
        graphics->display_all(physics);
        int exec_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count();
        int sleep_time = (1000 / 50) - exec_time;
        if (sleep_time > 0)
        {
            SDL_Delay(sleep_time);
        }
    }

    free(graphics);
    free(physics);
    free(cfg);

    return 0;
}