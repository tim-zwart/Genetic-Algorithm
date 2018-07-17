#ifndef FRAMEWORK_H_INCLUDED
#define FRAMEWORK_H_INCLUDED

#include "libraries.h"

struct vec;

struct coord
{
    double x;
    double y;
    vec convert();
};

struct vec
{
    double direction;
    double magnitude;
    vec operator+(const vec& v);
    vec operator-()const;
    vec operator*(int i);
    coord convert();
};

struct box
{
    coord bl;
    coord tr;
};

vec operator*(int i, const vec& v);

vec convert(double magnitude, double direction);
vec convert(coord c);
coord convertC(int x, int y);

double random(double max);
double random(double min, double max);

#endif // FRAMEWORK_H_INCLUDED
