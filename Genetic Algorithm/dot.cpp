#include "dot.h"
#include "windows.h"

int Dot::cDots = 0;

Dot::Dot(int nDir, vec start, SDL_Surface* image)
{
    Dot::cDots++;

    fitness = 0;
    brain = new Brain(nDir);
    pos = start;
    v.x = 0;
    v.y = 0;
    graphic = image;
    positions.push_back(pos);
    newPos=true;
}

Dot::Dot(vec start, SDL_Surface* image)
{
    Dot::cDots++;

    fitness = 0;
    brain = NULL;
    pos = start;
    v.x = 0;
    v.y = 0;
    graphic = image;
    positions.push_back(pos);
    newPos=true;
}

Dot::Dot()
{
    Dot::cDots++;
    brain = NULL;
    newPos=true;
}

Dot::~Dot()
{
    Dot::cDots--;
    if(brain != NULL)
    {
        delete brain;
    }
}

Dot& Dot::operator=(const Dot &d)
{
    reachedGoal = d.reachedGoal;
    dead = d.dead;
    instruct_step = d.instruct_step;
    if(brain != NULL)
    {
        delete brain;
    }
    brain = d.brain->clone();
    graphic = d.graphic;
    pos = d.pos;
    v = d.v;
    mass = d.mass;
    fitness = d.fitness;
    positions = d.positions;
    newPos = d.newPos;

    return *this;
}

void Dot::reCreate(int nDir, vec start, SDL_Surface* image)
{
    fitness = 0;
    brain = new Brain(nDir);
    pos = start;
    v.x = 0;
    v.y = 0;
    graphic = image;
    positions.push_back(pos);
}

void Dot::move()
{
    if(instruct_step < (int)brain->directions.size())
    {
        // Determine new speed
        v = v + brain->directions[instruct_step];

        // Limit speed
        double mag = sqrt(pow(v.x,2) + pow(v.y,2));
        if(mag > 3)
        {
            v *= 3/mag;
        }

        if(pos.x >= 200 && pos.x <= 400 && pos.y >= 100 && pos.y <= 200)
        {
            dead = true;
        }

        if(pos.x >= 300 && pos.x <= 500 && pos.y >= 300 && pos.y <= 400)
        {
            dead = true;
        }

        if(pos.x >= 100 && pos.x <= 370 && pos.y >= 220 && pos.y <= 270)
        {
            dead = true;
        }

        float deathCurve = (1.0f / pow((pos.x-320.0f) / 1000.0f,2)) + 160.0f;
        if(pos.y > deathCurve)
        {
            dead = true;
        }

        pos = pos + v;
        instruct_step++;
    }
    else
    {
        dead = true;
    }
}

void Dot::update(SDL_Surface* screen, box goal)
{
    if(brain == NULL)
    {
        return;
    }
    if(reachedGoal)
    {
        return;
    }
    if(dead)
    {
        return;
    }

    move();

    if(pos.x > screen->w-graphic->w/2-1 || pos.x < graphic->w/2 || pos.y > screen->h-graphic->h/2-1 || pos.y < graphic->h/2+1)
    {
        dead = true;
    }

    if(!dead)
    {
        bool left = pos.x - floor(graphic->w/2) >= goal.bl.x;
        bool right = pos.x + floor(graphic->w/2) <= goal.tr.x;
        bool bottom = pos.y - floor(graphic->h/2) >= goal.bl.y;
        reachedGoal =  left && right && bottom;
        dead = reachedGoal;
    }

    if(dead)
    {
        pos.x = std::min((double)screen->w-graphic->w/2-1, pos.x);
        pos.y = std::min((double)screen->h-graphic->h/2-1, pos.y);

        pos.x = std::max((double)graphic->w/2, pos.x);
        pos.y = std::max((double)graphic->h/2+1, pos.y);
    }

    if(newPos)
    {
        positions.push_back(pos);
    }
}

void Dot::calculateFitness(box goal, int minFit)
{
    vec g = convertC((goal.bl.x+goal.tr.x)/2,(goal.bl.y+goal.tr.y)/2);
    //coord p = pos.convert();
    double distance = sqrt(pow(g.x-pos.x, 2) + pow(g.y-pos.y, 2));
    //double distance = g.y-pos.y;
    if(!reachedGoal)
    {
        fitness = 1/pow(distance, 2) + (brain->directions.size() - instruct_step)/10000;
    }
    else
    {
        fitness = pow(brain->directions.size() - instruct_step, 2) + 1/distance;
    }
}

Dot Dot::mutate(vec start, SDL_Surface* image) const
{
    Dot baby(start, image);
    Brain* b = brain->mutate();
    baby.brain = b;
    return baby;
}

Dot Dot::clone(vec start, SDL_Surface* image) const
{
    Dot baby(start, image);
    Brain* b = brain->clone();
    baby.brain = b;
    baby.newPos = false;
    baby.positions = positions;
    return baby;
}

void Dot::showPos(SDL_Surface* screen)
{
    image(pos.x-graphic->w/2, pos.y+graphic->h/2, (SDL_Surface*)graphic, screen);
}

void Dot::showPath(SDL_Surface* screen)
{
    for(int i=0; i<(int)positions.size(); i++)
    {
        image(positions[i].x-graphic->w/2, positions[i].y+graphic->h/2, (SDL_Surface*)graphic, screen);
    }
}

void image(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    apply_surface(x, destination->h - y, source, destination);
}
