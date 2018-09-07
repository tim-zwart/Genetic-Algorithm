#ifndef DOT_H_INCLUDED
#define DOT_H_INCLUDED

#include "libraries.h"
#include "SDL_Basic.h"
#include "brain.h"
#include "framework.h"
#include "world.h"

class Dot
{
public:
    static int cDots;

    Dot(int nDir, vec start, SDL_Surface* image);
    Dot(vec start, SDL_Surface* image);
    Dot();
    ~Dot();
    Dot& operator=(const Dot &d);

private:
    // Member functions
    void reCreate(int nDir, vec start, SDL_Surface* image);
    void move();
    void update(World *w);
    Dot mutate(vec start, SDL_Surface* image) const;
    Dot clone(vec start, SDL_Surface* image) const;
    void calculateFitness(World *w);
    void showPos(SDL_Surface* screen);
    void showPath(SDL_Surface* screen);

    // Dynamic member variables
    vec pos;
    vec v;
    int mass;
    double fitness;
    int instruct_step = 0;
    bool reachedGoal = false;
    bool dead = false;

    vector <vec> positions;
    bool newPos;

    // Generally static member variables
    const Brain* brain;

    SDL_Surface* graphic;

    // Friends
    friend class Population;
};

// Blit an image onto another, but with (0, 0) at the bottom left of the screen rather than the top left
void image(int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif // DOT_H_INCLUDED
