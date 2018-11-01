#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

        /* Display background and two bodies */
        void display_all(Physics* phys);

        /* Display text at given place */
        void display_text(std::string s, int x, int y);

        /* Return string version of a variable (helper function for display_all) */
        std::string return_string(double x);

    private:
        /* Window width */
        int win_w;

        /* Window height */
        int win_h;

        /* Window title */
        std::string win_title;

        /* Pointers to the SDL window, renderer, font and textures  */
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Texture* first_body_texture;
        SDL_Texture* second_body_texture;
        SDL_Texture* background_texture;
        SDL_Texture* text_texture;

        /* Universal Rects for drawing */
        SDL_Rect rect;
        SDL_Rect text_rect;
        SDL_Rect background_rect;

        /* Stringstream used for outputting text */
        std::stringstream ss;
};

#endif