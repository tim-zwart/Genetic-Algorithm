#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED

#include "libraries.h"
#include "framework.h"
#include "dot.h"

class Population
{
public:
    Population(int nInstruct, vec start);
    void update(SDL_Surface* screen, box goal);
    void calculateFitness(box goal);
    bool allDead();
    void naturalSelection(box goal);

private:
    vec loc;
    int n;
    vector <Dot> dotss;
    vector <Dot> newDotss;
    Dot* dots;
    Dot* newDots;
    double fitnessSum;
    vector <Dot> prev;
    int gen;
};

#endif // POPULATION_H_INCLUDED
