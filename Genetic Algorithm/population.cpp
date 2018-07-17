#include "population.h"

Population::Population(int nDots, vec start)
{
    gen=0;
    n = nDots;
    loc = start;/*
    dots = new Dot[n];
    for(int i=0;i<n;i++)
    {
        Dot d(400, start);
        dots[i] = d;
    }*/
    dotss.reserve(nDots);
    for(int i=0;i<nDots;i++)
    {
        Dot d(400, start);
        dotss.push_back(d);
    }
    newDotss.resize(nDots);
}

void Population::update(SDL_Surface* screen, box goal)
{
    for(int i=0;i<dotss.size();i++)
    {
        dotss[i].update(screen, goal);
    }
    /*for(int i=0; i<n; i++)
    {
        dots[i].update(screen, goal);
    }*/
    for(int i=0; i<((int)prev.size())-1; i++)
    {
        prev[i].update(screen, goal);
    }
}

void Population::calculateFitness(box goal)
{
    int best=0;
    fitnessSum = 0;
/*
    for(int i=0; i<n - (gen==0); i++)
    {
        dots[i].calculateFitness(goal);
        fitnessSum += dots[i].fitness;
        if(dots[i].fitness > dots[best].fitness)
        {
            best = i;
        }
    }*/
    for(int i=0; i<dotss.size(); i++)
    {
        dots[i].calculateFitness(goal);
        fitnessSum += dots[i].fitness;
        if(dots[i].fitness > dots[best].fitness)
        {
            best = i;
        }
    }
    #define prev 0
    #if prev
    for(int i=0;i<prev.size();i++)
    {
        prev[i] = prev[i].clone(loc);
        prev[i].graphic = prev[i].bestGraphic;
    }
    prev.push_back(dots[best].clone(loc));
    prev[prev.size()-1].graphic = prev[prev.size()-1].bestGraphic;
    #endif
    if(gen==0)
    {
        newDotss.push_back(dotss[best].clone(loc));
    }
    else
    {
        newDotss[newDotss.size()-1] = dotss[best].clone(loc);
    }
    //newDots[n-1] = dots[best].clone(loc);
    //newDots[n-1].graphic = newDots[n-1].bestGraphic;
}

bool Population::allDead()
{
    for(int i=0; i<n; i++)
    {
        if(!dots[i].dead)
        {
            return false;
        }
    }
    return true;
}

void Population::naturalSelection(box goal)
{
    calculateFitness(goal);

    for(int i=0;i<dotss.size()-1;i++)
    {
        double r = random(fitnessSum);
        double num = r;
        int j=0;
        while(num >= 0)
        {
            num -= dots[j].fitness;
            j++;
        }
        newDots[i] = dots[j-1].mutate(loc);
    }



/*
    if(gen==0)
    {
        n++;
    }
    newDots = new Dot[n];
    calculateFitness(goal);
    gen++;
    for(int i=0;i<n-1;i++)
    {
        double r = random(fitnessSum);
        double num = r;
        int j=0;
        while(num >= 0)
        {
            num -= dots[j].fitness;
            j++;
        }
        newDots[i] = dots[j-1].mutate(loc);
    }
    delete[] dots;
    dots = newDots;
    newDots = NULL;*/
}
