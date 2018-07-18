#ifndef DOT_H_INCLUDED
#define DOT_H_INCLUDED

#include "libraries.h"
#include "STL_Basic.h"
#include "brain.h"
#include "framework.h"

class Dot
{
public:
    Dot(int nDir, vec start);
    Dot(vec start);
    Dot();
    ~Dot();
    Dot& operator=(const Dot &d);

private:
    // Member functions
    void reCreate(int nDir, vec start);
    void move();
    void update(SDL_Surface* screen, box goal);
    Dot mutate(vec start);
    Dot clone(vec start);
    void calculateFitness(box goal);

    // Dynamic member variables
    vec pos;
    vec v;
    int mass;
    double fitness;
    int instruct_step = 0;
    bool reachedGoal = false;
    bool dead = false;

    // Generally static member variables
    Brain* brain;

    SDL_Surface* graphic;
    const SDL_Surface* defaultGraphic = loadImage("box.png");
    const SDL_Surface* bestGraphic = loadImage("best_box.png");

    // Friends
    friend class Population;
};

// Blit an image onto another, but with (0, 0) at the bottom left of the screen rather than the top left
void image(int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif // DOT_H_INCLUDED
