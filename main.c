#include <stdio.h>

#include <SDL2/SDL.h>

int main() {
    if(SDL_Init(SDL_INIT_VIDEO))
        fprintf(stderr, "lmao it boke");
    else
        puts("yay it worky");
}
