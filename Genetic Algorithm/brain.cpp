#include "brain.h"

Brain::Brain(int nDir)
{
    for(int i=0;i<nDir;i++)
    {
        directions.push_back(convert(0.1, random(2*M_PI)));
        vec v = directions[i];
        int asdf = directions.size();
        int a = 123123;
    }
}

Brain::Brain()
{

}

Brain/***/ Brain::mutate()
{
    //Brain* b = new Brain();
    Brain b;
    const double mutateRate = 0.01;
    for(int i=0;i<directions.size();i++)
    {
        double r = random(1.0);
        if(r <= mutateRate)
        {
            vec v;
            v.direction = random(2*M_PI);
            v.magnitude = 0.1;
            //b->directions.push_back(v);
            b.directions.push_back(v);
        }
        else
        {
            //b->directions.push_back(directions[i]);
            b.directions.push_back(directions[i]);
        }
    }
    return b;
}

Brain/***/ Brain::clone()
{/*
    Brain* b = new Brain();
    b->directions = directions;
    return b;*/
    Brain b;
    b.directions = directions;
    return b;
}
