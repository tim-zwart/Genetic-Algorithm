#include "brain.h"

Brain::Brain(int nDir)
{
    for(int i=0;i<nDir;i++)
    {
        directions.push_back(convert(0.1, random(2*M_PI)));
    }
}

Brain::Brain()
{

}

Brain* Brain::mutate()
{
    Brain* b = new Brain();
    const double mutateRate = 0.01;
    for(int i=0;i<directions.size();i++)
    {
        double r = random(1.0);
        if(r <= mutateRate)
        {
            vec v;
            v.direction = random(2*M_PI);
            v.magnitude = 0.1;
            b->directions.push_back(v);
        }
        else
        {
            b->directions.push_back(directions[i]);
        }
    }
    return b;
}

Brain* Brain::clone()
{
    Brain* b = new Brain();
    b->directions = directions;
    return b;
}
