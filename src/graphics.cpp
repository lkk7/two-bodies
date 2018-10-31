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
    
    if (TTF_Init() == -1)
    {
        std::cout << "TTF: TTF_Init error! " << TTF_GetError() << "\n" << std::flush;
    }

    error  = 0;
}

Graphics::~Graphics()
{
    /* Destroy SDL objects and quit it */
    SDL_DestroyWindow(window);
    window = NULL;
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

    /* Background color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* Create font */
    font = TTF_OpenFont("resources/font/SometypeMono-Regular.ttf", 16);

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
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
    render_body(phys->get_b1(), first_body_texture);
    render_body(phys->get_b2(), second_body_texture);
    SDL_RenderPresent(renderer);
}