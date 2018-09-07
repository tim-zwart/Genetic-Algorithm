#include "libraries.h"
#include "framework.h"
#include "dot.h"
#include "brain.h"
#include "population.h"

using namespace std;

// Display window constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Event event;

int main( int argc, char* args[] )
{
    srand(time(NULL));

    // Create world
    //World* w = new World(SCREEN_WIDTH, SCREEN_HEIGHT, convertC(0, 0), goalLoc);
    World* w = new World();

    vector<vector<char>> grid;
    vector<string> lines;
    ifstream file;

    file.open("world3.txt");
    if(!file.is_open())
    {
        return -1;
    }

    for(int i=0;!file.eof();i++)
    {
        string s;
        getline(file, s);
        cout << s;
        lines.push_back(s);
    }

    vector <char> v;
    grid.resize(lines[0].length());

    for(int y=0;y<(int)lines.size();y++)
    {
        for(int x=0;x<(int)lines[0].length();x++)
        {
            if(y==0)
            {
                grid[x].resize(lines.size());
            }
            grid[x][y] = lines[y][x];
        }
    }

    w->buildWorld(grid);

    // Set up SDL
    bool quit = false;

    SDL_Surface* screen = init(w->w(), w->h(), SCREEN_BPP, "Genetic Algorithm");
    SDL_Surface* background = NULL;
    SDL_Surface* goal = NULL;

    // Counter SDL's redirection of outputs to / inputs from the console
    freopen ("CON", "w", stdout);
    freopen ("CON", "r", stdin);
    freopen ("CON", "w", stderr);

    if(screen == NULL)
    {
        return 1;
    }

    background = loadImage("background2.png");


    //background = SDL_SetVideoMode(w->w(), w->h(), SCREEN_BPP, 0);

    goal = loadImage("goal.png");

    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }

    w->showObstacles(background);

    apply_surface(0, 0, background, screen);

    SDL_FreeSurface(goal);

    Population pop(10000, w->start());

    for(int i=0; !quit; i++)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        if(pop.allDead())
        {
            w->update();

            apply_surface(0, 0, background, screen);
            pop.showPos(screen);
            SDL_Flip(screen);

            pop.naturalSelection(w);
/*
            apply_surface(0, 0, background, screen);
            pop.showBest(screen);
            SDL_Flip(screen);*/
        }
        else
        {
            pop.update(w);
            if(i % 50 == 0)
            {
                apply_surface(0, 0, background, screen);
                pop.showPos(screen);
                SDL_Flip(screen);
            }
        }
    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);

    return 0;
}
