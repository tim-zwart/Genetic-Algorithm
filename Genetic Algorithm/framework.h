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
    double x;
    double y;
    vec operator+(const vec& v);
    vec operator-()const;
    vec operator*(double num);
    vec operator*=(const double& num);
    coord convert();
};

struct box
{
    vec bl;
    vec tr;
};

vec operator*(int i, const vec& v);

vec convert(double magnitude, double direction);
vec convert(coord c);
vec convertC(int x, int y);

double random(double min, double max);
double randBell(double min, double max);

#endif // FRAMEWORK_H_INCLUDED
