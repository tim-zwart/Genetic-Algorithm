#include "dot.h"
#include "windows.h"

Dot::Dot(int nDir, vec start)
{
    fitness = 0;
    brain = new Brain(nDir);
    pos = start;
    v.magnitude = 0;
    v.direction = 0;
    graphic = (SDL_Surface*)defaultGraphic;
}

Dot::Dot(vec start)
{
    fitness = 0;
    brain = NULL;
    pos = start;
    v.magnitude = 0;
    v.direction = 0;
    graphic = (SDL_Surface*)defaultGraphic;
}

Dot::Dot()
{
    brain = NULL;
    graphic = (SDL_Surface*)defaultGraphic;
}

Dot::~Dot()
{
    if(brain != NULL)
    {
        delete brain;
    }
    delete defaultGraphic;
    delete bestGraphic;
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
    if(d.graphic == d.defaultGraphic)
    {
        graphic = (SDL_Surface*)defaultGraphic;
    }
    else
    {
        graphic = (SDL_Surface*)bestGraphic;
    }
    brain = d.brain->clone();
    pos = d.pos;
    v = d.v;
    mass = d.mass;
    fitness = d.fitness;

    return *this;
}

void Dot::reCreate(int nDir, vec start)
{
    fitness = 0;
    brain = new Brain(nDir);
    pos = start;
    v.magnitude = 0;
    v.direction = 0;
    graphic = (SDL_Surface*)defaultGraphic;
}

void Dot::move()
{
    if(dead)
    {
        return;
    }
    if(instruct_step < (int)brain->directions.size())
    {
        v = v + brain->directions[instruct_step];
        v.magnitude = min(v.magnitude, (double)3);
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

    move();

    coord c = pos.convert();

    bool wasDead = dead;

    if(c.x > screen->w-graphic->w/2-1 || c.x < graphic->w/2 || c.y > screen->h-graphic->h/2-1 || c.y < graphic->h/2+1)
    {
        dead = true;
    }

    if(!dead)
    {
        bool left = pos.convert().x - floor(graphic->w/2) >= goal.bl.x;
        bool right = pos.convert().x + floor(graphic->w/2) <= goal.tr.x;
        bool bottom = pos.convert().y - floor(graphic->h/2) >= goal.bl.y;
        reachedGoal =  left && right && bottom;
        dead = reachedGoal;
        if(reachedGoal)
        {
            fitness = pow(brain->directions.size() - instruct_step, 2);
        }
    }

    if(dead && !wasDead)
    {
        c.x = std::min((double)screen->w-graphic->w/2-1, c.x);
        c.y = std::min((double)screen->h-graphic->h/2-1, c.y);

        c.x = std::max((double)graphic->w/2, c.x);
        c.y = std::max((double)graphic->h/2+1, c.y);

        pos = c.convert();
    }

    image(c.x-graphic->w/2, c.y+graphic->h/2, (SDL_Surface*)graphic, screen);
    //image(c.x-graphic->w/2, c.y+graphic->h/2, (SDL_Surface*)defaultGraphic, screen);
}

void Dot::calculateFitness(box goal)
{
    coord g = convertC((goal.bl.x+goal.tr.x)/2,(goal.bl.y+goal.tr.y)/2);
    coord p = pos.convert();
    double distance = sqrt(pow(g.x-p.x, 2) + pow(g.y-p.y, 2));
    fitness += 1/pow(distance, 2);
}

Dot Dot::mutate(vec start)
{
    Dot baby(start);
    Brain* b = brain->mutate();
    baby.brain = b;
    return baby;
}

Dot Dot::clone(vec start)
{
    Dot baby(start);
    Brain* b = brain->clone();
    baby.brain = b;
    return baby;
}

void image(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    apply_surface(x, destination->h - y, source, destination);
}
