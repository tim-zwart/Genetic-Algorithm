#include "brain.h"

int Brain::cBrains = 0;

Brain::Brain(int nDir)
{
    cBrains++;
    for(int i=0;i<nDir;i++)
    {
        directions.push_back(convert(0.1, random(0, 2*M_PI)));
        //directions.push_back(convert(0.1, M_PI_2));
    }
}

Brain::Brain()
{
    cBrains++;
}

Brain::~Brain()
{
    cBrains--;
}

Brain* Brain::mutate() const
{
    Brain* b = new Brain();
    b->directions.reserve(directions.size());
    const double mutateRate = 0.01;
    for(int i=0;i<(int)directions.size();i++)
    {
        double r = random(0.0, 1.0);
        if(r <= mutateRate /*+ pow(i, 0.1)/directions.size()*/)
        {
            vec v;

            double mag = sqrt(pow(directions[i].x,2) + pow(directions[i].y,2));
            double dir = atan2(directions[i].y, directions[i].x) + randBell(-M_PI, M_PI);
            //double dir = random(0, 2*M_PI);

            v.x = mag*cos(dir);
            v.y = mag*sin(dir);

            b->directions.push_back(v);
        }
        else
        {
            b->directions.push_back(directions[i]);
        }
    }
    return b;
}

Brain* Brain::clone() const
{
    Brain* b = new Brain();
    b->directions = directions;
    return b;
}
