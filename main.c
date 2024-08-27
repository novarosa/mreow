#include <stdio.h>

#include <SDL2/SDL.h>

int main() {
    if(SDL_Init(SDL_INIT_VIDEO))
        fprintf(stderr, "lmao it boke\n");
    else
        puts("yay it worky");
}
