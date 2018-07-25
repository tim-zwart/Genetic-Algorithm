#ifndef STL_BASIC_H_INCLUDED
#define STL_BASIC_H_INCLUDED

#include "libraries.h"

extern SDL_Surface* loadImage(std::string filename);

extern void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

extern SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP);
extern SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP, std::string title);

#endif // STL_BASIC_H_INCLUDED
