#include <SDL2/SDL_image.h>
#include "graphics.hpp"

Graphics::Graphics(std::map<std::string, std::string>* cfg)
    : win_w(stoi((*cfg)["window_width"])), 
      win_h(stoi((*cfg)["window_height"])),
      win_title((*cfg)["window_name"])
{
    /* Check if SDL inits correctly */
    if (!init_self())
    {
        error = 1;
        return;
    }

    error  = 0;
}

Graphics::~Graphics()
{
    /* Destroy SDL objects and quit it */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_Quit();
}

bool Graphics::init_self()
{
    /* Init the SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL: init error! " << SDL_GetError() << "\n" << std::flush;
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "SDL_IMG: PNG module init error! " << IMG_GetError() << "\n" << std::flush;/* Main loop with a set *average* framerate */
        return 0;
    }

    /* Initialize the window */
    window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN);
    if (window == NULL)/* Main loop with a set *average* framerate */
        {
            std::cout << "SDL: window creation error! " << SDL_GetError() << "\n" << std::flush;
            return 0;
        }

    /* Initialize the renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "SDL: renderer creation error! " << SDL_GetError() << "\n" << std::flush;
        return 0;
    }

    /* Create the texture of particles */
    first_body_texture = create_texture("resources/first_body.png");;
    second_body_texture = create_texture("resources/second_body.png");
    background_texture = create_texture("resources/background.png");
    SDL_SetRenderTarget(renderer, background_texture);

    /* Background color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* Init and create font, set sstream formatting */
    if (TTF_Init() != 0)
    {
        std::cout << "TTF: TTF_Init error! " << TTF_GetError() << "\n" << std::flush;
        return 0;
    }
    font = TTF_OpenFont("resources/font/SometypeMono-Regular.ttf", 12);
    if (font == NULL)
    {
         std::cout << "TTF: OpenFont error! " << TTF_GetError() << "\n" << std::flush;
    }
    ss.setf(std::ios::scientific);
    ss.precision(2);
    
    /* Set background rect */
    rect.x = rect.y = rect.w = rect.h = background_rect.x = background_rect.y = 0;
    background_rect.w = win_w;
    background_rect.h = win_h;
    
    return 1;
}

SDL_Texture* Graphics::create_texture(const std::string& png_path)
{
    SDL_Surface* surface = IMG_Load(png_path.c_str());
    if (surface == NULL)
    {
        std::cout << "SDL_IMG: unable to find " << png_path << " " << SDL_GetError() << "\n" << std::flush;
        return 0;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        std::cout << "SDL: error while creating texture from surface " << " " << SDL_GetError() << "\n" << std::flush;
        return 0;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void Graphics::render_body(const Body* b, SDL_Texture* t)
{
    rect.x = b->x - b->radius;
    rect.y = b->y - b->radius;
    rect.w = rect.h = 2 * b->radius;

    SDL_RenderCopy(renderer, t, NULL, &rect);
}

void Graphics::display_all(Physics* phys)
{
    const Body *a = phys->get_b1();
    const Body *b = phys->get_b2();


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);

    render_body(a, first_body_texture);
    render_body(b, second_body_texture);

    display_text(a->name, 0, 0);
    display_text("x: " + return_string(a->x), 0, 12);
    display_text("y: " + return_string(a->y), 0, 24);
    display_text("vx: " + return_string(a->v_x), 0, 36);
    display_text("vy: " + return_string(a->v_y), 0, 48);
    display_text("ax: " + return_string(a->a_x), 0, 60);
    display_text("ay: " + return_string(a->a_y), 0, 72);
    double energy1 = a->mass_kg * ((a->v_x * a->v_x) + (a->v_y * a->v_y)) / 2;
    display_text("1/2 mv^2: " + return_string(energy1), 0, 84);

    display_text(b->name, 0, 100); 
    display_text("x: " + return_string(b->x), 0, 112);
    display_text("y: " + return_string(b->y), 0, 124);
    display_text("vx: " + return_string(b->v_x), 0, 136);
    display_text("vy: " + return_string(b->v_y), 0, 148);
    display_text("ax: " + return_string(b->a_x), 0, 160);
    display_text("ay: " + return_string(b->a_y), 0, 172);
    double energy2 = b->mass_kg * ((b->v_x * b->v_x) + (b->v_y * b->v_y)) / 2;
    display_text("1/2 mv^2: " + return_string(energy2), 0, 184);

    display_text("r: " + return_string(phys->get_r()), 0, 200);
    double potential = -phys->get_fg() * phys->get_r();
    display_text("-GMm/r: " + return_string(potential), 0, 212);
    
    SDL_RenderPresent(renderer);
}

void Graphics::display_text(std::string s, int x, int y)
{
    SDL_Color color = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, s.c_str(), color);
    text_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
    text_rect.x = x;
    text_rect.y = y;

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_FreeSurface(surface);
}

std::string Graphics::return_string(double x)
{
    ss.str(std::string());
    ss << x;
    return ss.str();
}