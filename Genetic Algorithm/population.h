#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED

#include "libraries.h"
#include "framework.h"
#include "dot.h"

class Population
{
public:
    // Non const functions
    Population(int nInstruct, vec start);
    void update(World *w);
    void calculateFitness(World *w);
    void naturalSelection(World *w);
    void outGenResults(ofstream file);
    void showPos(SDL_Surface* screen);
    void showBest(SDL_Surface* screen);

    // const functions
    bool allDead() const;

private:
    vec loc; // Starting location
    int n; // Number of dots
    Dot* dots;
    Dot* newDots;
    double* fitDist;
    double fitnessSum; // Total fitness of all dots
    int gen; // Current generation
    SDL_Surface* const defaultGraphic = loadImage("box.png");
    SDL_Surface* const bestGraphic = loadImage("best_box.png");
    SDL_Surface* const point = loadImage("point.png");
};

#endif // POPULATION_H_INCLUDED
