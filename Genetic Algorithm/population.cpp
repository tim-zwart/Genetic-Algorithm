#include "population.h"

Population::Population(int nDots, vec start)
{
    gen=1;
    n = nDots;
    loc = start;
    dots = new Dot[n];
    for(int i=0;i<n;i++)
    {
        dots[i].reCreate(1000, start, defaultGraphic);
    }
}

void Population::update(World *w)
{
    for(int i=0; i<n; i++)
    {
        dots[i].update(w);
    }
}

void Population::calculateFitness(World *w)
{
    int best=0;
    fitnessSum = 0;

    for(int i=0; i<n - (gen==1); i++)
    {
        dots[i].calculateFitness(w);
        fitnessSum += dots[i].fitness;
        fitDist[i] = fitnessSum;

        if(dots[i].fitness > dots[best].fitness && (!dots[n-1].reachedGoal || dots[i].reachedGoal))
        {
            best = i;
        }
    }
    newDots[n-1] = dots[best].clone(loc, bestGraphic);

    // Output results about past generation
    if(!dots[best].reachedGoal)
    {
        cout << "Food gained: " << dots[best].fitness << endl << endl;
    }
    else
    {
        cout << "Number of steps taken to reach goal: " << dots[best].instruct_step << endl << endl;
    }
}

void Population::showPos(SDL_Surface* screen)
{
    for(int i=0; i<n; i++)
    {
        dots[i].showPos(screen);
    }
}

void Population::showBest(SDL_Surface* screen)
{
    dots[n-1].showPath(screen);
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

void Population::naturalSelection(World *w)
{
    cout << "Generation " << gen << endl;
    if(gen==0)
    {
        n++;
    }
    newDots = new Dot[n];
    fitDist = new double[n];

    calculateFitness(w);

    for(int i=0;i<n-1;i++)
    {
        double element = ((double)n-1)/2;
        double r = random(0, fitnessSum);
        /*
        double num = r;
        int j=0;
        while(num >= 0)
        {
            num -= dots[j].fitness;
            j++;
        }
        */

        for(int j=4;;j*=2)
        {
            if(r <= fitDist[int(element)])
            {
                if(((int)element) == 0 || r >= fitDist[int(element-1)])
                {
                    break;
                }
                element -= ((double)n-1)/j;
            }
            else
            {
                if(((int)element) == n-2)
                {
                    element++;
                    break;
                }
                element += ((double)n-1)/j;
            }
        }

        newDots[i] = dots[int(element)].mutate(loc, defaultGraphic);
    }
    delete[] dots;
    dots = newDots;
    newDots = NULL;
    gen++;
}
