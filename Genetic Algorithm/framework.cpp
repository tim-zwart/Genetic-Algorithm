#include "framework.h"

using namespace std;

random_device rd;
mt19937 mt(time(NULL));

vec convert(coord c)
{
    vec v;
    v.magnitude=sqrt(pow(c.x,2) + pow(c.y,2));
    v.direction=atan2(c.y, c.x);
    return v;
}

vec convert(double magnitude, double direction)
{
    vec v;
    v.direction=direction;
    v.magnitude=magnitude;
    return v;
}

vec vec::operator+(const vec& v)
{
    double x = this->magnitude*cos(this->direction) + v.magnitude*cos(v.direction);
    double y = this->magnitude*sin(this->direction) + v.magnitude*sin(v.direction);

    vec result;

    result.magnitude = sqrt(pow(x,2) + pow(y,2));
    result.direction = atan2(y, x);

    return result;
}

vec vec::operator-() const
{
    vec v;
    v.magnitude = this->magnitude*(-1);
    v.direction = this->direction;

    return v;
}

vec vec::operator*(int i)
{
    vec v;
    v.magnitude = this->magnitude*i;
    v.direction = this->direction;

    return v;
}

vec operator*(int i, const vec& v)
{
    vec vec;
    vec.magnitude = v.magnitude*i;
    vec.direction = v.direction;

    return vec;
}

coord vec::convert()
{
    coord c;
    c.x = magnitude*cos(direction);
    c.y = magnitude*sin(direction);

    return c;
}

vec coord::convert()
{
    vec v;
    v.magnitude = sqrt(pow(x,2) + pow(y,2));
    v.direction = atan2(y, x);

    return v;
}

coord convertC(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;
    return c;
}

double random(double max)
{
    return random(0, max);
}

double random(double min, double max)
{
    uniform_real_distribution<double> dist(min, max);

    return dist(mt);
}
