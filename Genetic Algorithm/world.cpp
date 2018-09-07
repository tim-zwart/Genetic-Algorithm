#include "world.h"

using namespace std;

World::World()
{

}

World::World(int worldWidth, int worldHeight, vec popStart, box popGoal)
{
    width = worldWidth;
    height = worldHeight;
    startLoc = popStart;
    goalLoc = popGoal;
    goalCenter.x = (goalLoc.tr.x + goalLoc.bl.x) / 2;
    goalCenter.y = (goalLoc.tr.y + goalLoc.bl.y) / 2;
    tSinceFood=0;

    addVal = new double* [width];
    for(int x = 0; x<width; x++)
    {
        addVal[x] = new double[height];
        for(int y = 0; y<height; y++)
        {
            //double distance = sqrt(pow(goalCenter.x-x, 2) + pow(goalCenter.y-y, 2));
            double distance = sqrt(pow(abs(goalCenter.x-x), 2) + pow(abs(goalCenter.y-y), 2));
            addVal[x][y] = pow(2, -pow(distance, 0.2));
        }
    }

    food = new double* [width];
    for(int x=0; x<width; x++)
    {
        food[x] = new double[height];
        for(int y=0;y<height;y++)
        {
            food[x][y] = addVal[x][y];
        }
    }

    box b;
    b.bl.x=40;
    b.bl.y=40;
    b.tr.x=300;
    b.tr.y=80;
    obstacles.push_back(b);

    b.bl.x=340;
    b.bl.y=40;
    b.tr.x=640;
    b.tr.y=80;
    obstacles.push_back(b);

    b.bl.x=40;
    b.bl.y=40;
    b.tr.x=80;
    b.tr.y=420;
    obstacles.push_back(b);

    b.bl.x=260;
    b.bl.y=40;
    b.tr.x=300;
    b.tr.y=420;
    obstacles.push_back(b);

    b.bl.x=340;
    b.bl.y=40;
    b.tr.x=380;
    b.tr.y=420;
    obstacles.push_back(b);

    b.bl.x=260;
    b.bl.y=380;
    b.tr.x=380;
    b.tr.y=420;
    obstacles.push_back(b);
}

World::~World()
{
    for(int i=0; i<width; i++)
    {
        delete[] food[i];
    }
    delete[] food;
}

void World::showObstacles(SDL_Surface* screen)
{
    SDL_PixelFormat *fmt = screen->format;
    SDL_Rect r;
    /*
    for(int i=0; i<(int)obstacles.size(); i++)
    {
        SDL_Rect r;
        r.x=obstacles[i].bl.x;
        r.y=screen->h-obstacles[i].tr.y;
        r.w=abs(obstacles[i].tr.x-obstacles[i].bl.x);
        r.h=abs(obstacles[i].tr.y-obstacles[i].bl.y);

        SDL_PixelFormat *fmt = screen->format;

        SDL_FillRect(screen, &r, SDL_MapRGB(fmt, 0, 0, 0));
    }*/
    for(int x=0;x<width;x++)
    {
        for(int y=0;y<height;y++)
        {
            r.x=x;
            r.y=height - y;
            r.w=1;
            r.h=1;
            if(obstacle[x][y])
            {
                SDL_FillRect(screen, &r, SDL_MapRGB(fmt, 0, 0, 0));
            }
            else
            {
                SDL_FillRect(screen, &r, SDL_MapRGB(fmt, 255, 255, 255));
            }
        }
    }

    r.x=goalLoc.bl.x;
    r.y=height - goalLoc.tr.y;
    r.w=scale;
    r.h=scale;

    SDL_FillRect(screen, &r, SDL_MapRGB(fmt, 255, 0, 0));
}

bool World::collided(vec pos)
{
    return obstacle[(int)(pos.x)][(int)(pos.y)];
    /*for(int i=0; i<(int)obstacles.size(); i++)
    {
        if(pos.x >= obstacles[i].bl.x && pos.x <= obstacles[i].tr.x && pos.y >= obstacles[i].bl.y && pos.y <= obstacles[i].tr.y)
        {
            return true;
        }
    }
    return false;*/
}

void World::addFood()
{
    for(int x = 0; x<width; x++)
    {
        for(int y = 0; y<height; y++)
        {
            food[x][y] += addVal[x][y];
        }
    }
}

void World::updateEats()
{
    for(int i=0; i<(int)eatList.size(); i++)
    {
        food[(int)eatList[i].x][(int)eatList[i].y] /= 2;
    }
}

void World::update()
{
    updateEats();

    int eatLen = eatList.size();
    eatList.clear();
    eatList.reserve(eatLen);
/*
    tSinceFood++;
    if(tSinceFood % 500 == 0)
    {
        addFood();
    }*/
}

double World::eat(int x, int y)
{
    vec v;
    v.x = x;
    v.y = y;
    eatList.push_back(v);

    return food[x][y]/2;
}

void World::buildWorld(vector<vector<char>> grid)
{
    int scale = 20;
    width = grid.size()*scale;
    height = grid[0].size()*scale;

    obstacle = new bool* [width];
    for(int x=0; x<width; x++)
    {
        obstacle[x] = new bool[height];
        for(int y=0;y<height;y++)
        {
            obstacle[x][y] = false;
        }
    }

    for(int x=0;x<width/scale;x++)
    {
        for(int y=0;y<height/scale;y++)
        {
            switch(grid[x][y])
            {
            case 'w':
            case 'W':
                box b;
                b.bl.x=x*scale;
                b.bl.y=y*scale;
                b.tr.x=(x+1)*scale;
                b.tr.y=(y+1)*scale;
                obstacles.push_back(b);
                for(int i=0;i<scale;i++)
                {
                    for(int j=0;j<scale;j++)
                    {
                        obstacle[x*scale+i][height - (y*scale+j)]=true;
                    }
                }
                break;
            case 'g':
            case 'G':
                goalLoc.bl.x=x*scale;
                goalLoc.bl.y=height - (y+1)*scale;
                goalLoc.tr.x=(x+1)*scale;
                goalLoc.tr.y=height - y*scale;
                break;
            case 's':
            case 'S':
                startLoc.x = (x+0.5)*scale;
                startLoc.y = height - (y+0.5)*scale;
                break;
            }
        }
    }

    goalCenter.x = (goalLoc.tr.x + goalLoc.bl.x) / 2;
    goalCenter.y = (goalLoc.tr.y + goalLoc.bl.y) / 2;
    tSinceFood=0;

    addVal = new double* [width];
    for(int x = 0; x<width; x++)
    {
        addVal[x] = new double[height];
        for(int y = 0; y<height; y++)
        {
            //double distance = sqrt(pow(goalCenter.x-x, 2) + pow(goalCenter.y-y, 2));
            double distance = sqrt(pow(abs(goalCenter.x-x), 2) + pow(abs(goalCenter.y-y), 2));
            addVal[x][y] = pow(2, -pow(distance, 0.2));
        }
    }

    food = new double* [width];
    for(int x=0; x<width; x++)
    {
        food[x] = new double[height];
        for(int y=0;y<height;y++)
        {
            food[x][y] = addVal[x][y];
        }
    }
}

void World::buildWorld(char** grid, unsigned int w, unsigned int h)
{
    for(int x=0;x<(int)w;x++)
    {
        for(int y=0;y<(int)h;y++)
        {
            if(grid[x][y] == 'W' && grid[x][y] == 'w')
            {
                box b;
                b.bl.x=x*scale;
                b.bl.y=x*scale;
                b.tr.x=(x+1)*scale;
                b.tr.y=(x+1)*scale;
                obstacles.push_back(b);
            }
        }
    }
}

int World::w()
{
    return width;
}

int World::h()
{
    return height;
}

box World::goal()
{
    return goalLoc;
}

vec World::start()
{
    return startLoc;
}

int World::nEats()
{
    return eatList.size();
}
