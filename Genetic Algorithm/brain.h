#ifndef BRAIN_H_INCLUDED
#define BRAIN_H_INCLUDED

using namespace std;

#include "libraries.h"
#include "framework.h"

class Brain
{
    public:
        static int cBrains;

        vector <vec> directions;
        Brain* mutate() const;
        Brain* clone() const;

        Brain();
        Brain(int nDir);
        ~Brain();
};

#endif // BRAIN_H_INCLUDED
