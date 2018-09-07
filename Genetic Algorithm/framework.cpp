#include "framework.h"

using namespace std;

random_device rd;
mt19937 mt(time(NULL));

vec convert(double magnitude, double direction)
{
    vec v;
    v.x = magnitude*cos(direction);
    v.y = magnitude*sin(direction);
    return v;
}

vec vec::operator+(const vec& v) const
{
    vec result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    return result;
}

vec vec::operator+=(const vec& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

vec vec::operator-() const
{
    vec v;
    v.x = -this->x;
    v.y = -this->y;
    return v;
}

vec vec::operator*(double num) const
{
    vec v;
    v.x = this->x*num;
    v.y = this->y*num;
    return v;
}

inline vec operator*(double num, const vec& v)
{
    vec result;
    result.x = v.x*num;
    result.y = v.y*num;
    return result;
}

vec vec::operator*=(const double& num)
{
    this->x *= num;
    this->y *= num;
    return *this;
}
/*
coord vec::convert()
{
    coord c;
    c.x = magnitude*cos(direction);
    c.y = magnitude*sin(direction);

    return c;
}
*//*
vec coord::convert()
{
    vec v;
    v.magnitude = sqrt(pow(x,2) + pow(y,2));
    v.direction = atan2(y, x);

    return v;
}
*/
vec convertC(int x, int y)
{
    vec v;
    v.x = x;
    v.y = y;
    return v;
}


const int RANDOM_COUNT = 1024*1024;
double storedRandoms[RANDOM_COUNT];
bool randomsStarted = false;
int ixRnd = 0;
double random(double min, double max)
{
    if(!randomsStarted)
    {
        uniform_real_distribution<double> dist(0, 1);
        for(int x = 0;x < RANDOM_COUNT; x++)
        {
            storedRandoms[x] = dist(mt);
        }
        randomsStarted = true;
    }

    double ret = storedRandoms[ixRnd];
    //ret = min + (max - min) * ret;

    ixRnd = (ixRnd + 1) % RANDOM_COUNT;
    //return ret;
    return min + (max - min) * ret;
}

double randBell(double min, double max)
{
    double n = max+1;
    while(n>max || n<min)
    {
        normal_distribution<double> dist(5, 1.0);
        n = dist(mt) / 10 * (max-min) + min;
    }

    return n;
}
