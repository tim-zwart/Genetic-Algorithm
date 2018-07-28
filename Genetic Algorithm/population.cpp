#include "population.h"

Population::Population(int nDots, vec start)
{
    gen=1;
    n = nDots;
    loc = start;
    dots = new Dot[n];
    for(int i=0;i<n;i++)
    {
        dots[i].reCreate(400, start, defaultGraphic);
    }
}

void Population::update(SDL_Surface* screen, box goal)
{
    for(int i=0; i<n; i++)
    {
        dots[i].update(screen, goal);
    }
}

void Population::calculateFitness(box goal)
{
    int best=0;
    fitnessSum = 0;

    for(int i=0; i<n - (gen==1); i++)
    {
        dots[i].calculateFitness(goal, 0);
        fitnessSum += dots[i].fitness;
        if(dots[i].fitness > dots[best].fitness)
        {
            best = i;
        }
    }
    newDots[n-1] = dots[best].clone(loc, bestGraphic);

    // Output results about past generation
    if(!dots[best].reachedGoal)
    {
        cout << "Distance from goal: " << pow(dots[best].fitness, -0.5) << endl << endl;
    }
    else
    {
        cout << "Number of steps taken to reach goal: " << dots[best].instruct_step << endl << endl;
    }
}

bool Population::allDead() const
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
    cout << "Generation " << gen << endl;
    if(gen==0)
    {
        n++;
    }
    newDots = new Dot[n];
    calculateFitness(goal);

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
        newDots[i] = dots[j-1].mutate(loc, defaultGraphic);
    }
    delete[] dots;
    dots = newDots;
    newDots = NULL;
    gen++;
}
