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
    void update(SDL_Surface* screen, box goal);
    void calculateFitness(box goal);
    void naturalSelection(box goal);
    void outGenResults(ofstream file);

    // const functions
    bool allDead() const;

private:
    vec loc; // Starting location
    int n; // Number of dots
    Dot* dots;
    Dot* newDots;
    double fitnessSum; // Total fitness of all dots
    int gen; // Current generation
};

#endif // POPULATION_H_INCLUDED
