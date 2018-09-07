#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "framework.h"

using namespace std;

class World
{
public:
    World();
    World(int width, int height, vec start, box goal);
    ~World();
    void update();
    void updateEats();
    double eat(int x, int y);
    void showObstacles(SDL_Surface* screen);
    bool collided(vec pos);
    void buildWorld(vector<vector<char>> grid);
    void buildWorld(char** grid, unsigned int w, unsigned int h);
    int w();
    int h();
    box goal();
    vec start();
    int nEats();

private:
    const int scale=20;

    // Graphic
    // Graphic view;

    // Map properties
    int width;
    int height;

    // Obstacles
    vector <box> obstacles;
    bool** obstacle;

    // Population properties
    vec startLoc;
    box goalLoc;
    vec goalCenter;

    // Food
    void addFood();
    double** food;
    double** addVal;
    vector <vec> eatList;
    int tSinceFood;
};

#endif // WORLD_H_INCLUDED
