#ifndef FRAMEWORK_H_INCLUDED
#define FRAMEWORK_H_INCLUDED

#include "libraries.h"

struct vec
{
    double x;
    double y;
    vec operator+(const vec& v) const;
    vec operator+=(const vec& v);
    vec operator-() const;
    vec operator*(double num) const;
    vec operator*=(const double& num);
};

struct box
{
    vec bl;
    vec tr;
};

vec operator*(int i, const vec& v);

vec convert(double magnitude, double direction);
vec convertC(int x, int y);

double random(double min, double max);
double randBell(double min, double max);

#endif // FRAMEWORK_H_INCLUDED
