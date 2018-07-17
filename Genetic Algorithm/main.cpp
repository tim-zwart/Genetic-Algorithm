#include "libraries.h"
#include "framework.h"
#include "dot.h"
#include "brain.h"
#include "population.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Event event;

int main( int argc, char* args[] )
{
    srand(time(NULL));

    bool quit = false;

    SDL_Surface* screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, "Genetic Algorithm");
    SDL_Surface* background = NULL;
    SDL_Surface* goal = NULL;

    if(screen == NULL)
    {
        return 1;
    }

    background = loadImage("background2.png");
    goal = loadImage("goal.png");

    apply_surface(0, 0, background, screen);

    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }
    int g = goal->h;
    int generation=0;
    #define tl 0
    #if tl
    coord goalL = convertC(0, 480);
    box goalLoc;
    goalLoc.bl = convertC(0, 480-goal->h);
    goalLoc.tr = convertC(goal->w, 480);
    #else
    coord goalL = convertC(320-floor(goal->w/2+1), 480);
    box goalLoc;
    goalLoc.bl = convertC(320-floor(goal->w/2), 480-goal->h);
    goalLoc.tr = convertC(320+floor(goal->w/2), 480);
    #endif
    image(goalL.x, goalL.y, goal, background);

    Population pop(1000 ,convertC(320, 3).convert());

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        apply_surface(0, 0, background, screen);

        if(pop.allDead())
        {
            pop.naturalSelection(goalLoc);
            pop.update(screen, goalLoc);
        }
        else
        {
            pop.update(screen, goalLoc);
        }
        SDL_Flip(screen);

        Sleep(10);
    }

    return 0;
}
