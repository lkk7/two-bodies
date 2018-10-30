#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "physics.hpp"

class Graphics
{
    public:
        /* State of the graphic engine after init */
        bool error;

        /* Sets essential parameters of graphics */                                                  
        Graphics(std::map<std::string, std::string>* cfg);

        ~Graphics();

        /* SDL and resources initiation */    
        bool init_self();

        /* Create a texture from a PNG */
        SDL_Texture* create_texture(const std::string& png_path);

        /* Render a body */
        void render_body(const Body* b, SDL_Texture* t);

        /* Display all drawable objects */
        void display_all(Physics* phys);

    private:
        /* Window width */
        int win_w;

        /* Window height */
        int win_h;

        /* Window title */
        std::string win_title;

        /* Pointers to the SDL window, renderer and textures  */
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* first_body_texture;
        SDL_Texture* second_body_texture;
        SDL_Texture* background_texture;

        /* Universal Rects for drawing */
        SDL_Rect rect;
        SDL_Rect background_rect;
};

#endif