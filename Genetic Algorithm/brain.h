#ifndef BRAIN_H_INCLUDED
#define BRAIN_H_INCLUDED

using namespace std;

#include "libraries.h"
#include "framework.h"

class Brain
{
    public:
        vector <vec> directions;/*
        Brain* mutate();
        Brain* clone();*/
        Brain mutate();
        Brain clone();

        Brain();
        Brain(int nDir);
};

#endif // BRAIN_H_INCLUDED
