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

vec vec::operator+(const vec& v)
{
    vec result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    return result;
}

vec vec::operator-() const
{
    vec v;
    v.x = -this->x;
    v.y = -this->y;
    return v;
}

vec vec::operator*(double num)
{
    vec v;
    v.x = this->x*num;
    v.y = this->y*num;
    return v;
}

vec operator*(double num, const vec& v)
{
    vec result;
    result.x = v.x*num;
    result.y = v.y*num;
    return result;
}

vec vec::operator*=(const double& num)
{
    vec result;
    result.x = x*num;
    result.y = y*num;
    return result;
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

double random(double min, double max)
{
    uniform_real_distribution<double> dist(min, max);

    return dist(mt);
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
