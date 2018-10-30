#include "events.hpp"

namespace events
{
    /* Object for storing SDL events */
    SDL_Event ev;
}

bool handle_events()
{
    /* Check clicked keys */
    while (SDL_PollEvent(&events::ev))
    {
        if (events::ev.type == SDL_QUIT)
        {
            return false;
        }
        else if (events::ev.type == SDL_KEYDOWN)
        {
            if (events::ev.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
        }
    }

    return true;
}
