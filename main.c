#include <stdio.h>

#include <SDL2/SDL.h>

int main() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *w = SDL_CreateWindow("yay it worky",
                                     100, 100, 640, 480,
                                     SDL_WINDOW_RESIZABLE);
    if(!w) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *r = SDL_CreateRenderer(w, -1,
                                         SDL_RENDERER_ACCELERATED|
                                             SDL_RENDERER_PRESENTVSYNC);
    if(!r) {
        fprintf(stderr,
                "Error creating rendering context: %s\n",
                SDL_GetError());
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("res/nova.bmp");
    if(!bmp) {
        fprintf(stderr, "Error loading image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(r, bmp);
    if(!t) {
        fprintf(stderr,
                "Error creating texture from image: %s\n",
                SDL_GetError());
        SDL_FreeSurface(bmp);
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_FreeSurface(bmp);

    // TwinkleBearDev describes this loop as "sleepy" 😭
    for(int i = 0; i < 3; i++) {
        if(SDL_RenderClear(r))
            fprintf(stderr,
                    "Error clearing the rendering context: %s\n",
                    SDL_GetError());

        if(SDL_RenderCopy(r, t, NULL, NULL))
            fprintf(stderr,
                    "Error copying texture into the rendering %s%s\n",
                    "context: ",
                    SDL_GetError());

        SDL_RenderPresent(r);
        SDL_Delay(1000);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
}
