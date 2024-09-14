#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// TODO idk maybe figure out a better default than 1200x1200
#define INIT_WIDTH 1200
#define INIT_HEIGHT 1200

void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, SDL_GetError());
}

int ren(SDL_Texture *t, SDL_Renderer *r, int x, int y) {
    SDL_Rect o;
    o.x = x;
    o.y = y;

    int e = SDL_QueryTexture(t, NULL, NULL, &o.w, &o.h);
    if(e) {
        error("Unable to look up texture");
        return e;
    }

    e = SDL_RenderCopy(r, t, NULL, &o);
    if(e)
        error("Error copying texture into the rendering context");

    return e;
}

int main() {
    int e = SDL_Init(SDL_INIT_VIDEO);
    if(e) {
        error("Error initializing SDL");
        return e;
    }

    // TODO make window resizable
    SDL_Window *w = SDL_CreateWindow("yay it worky",
                                     100, 100, INIT_WIDTH, INIT_HEIGHT,
                                     0 /*SDL_WINDOW_RESIZABLE*/);
    if(!w) {
        error("Error creating window");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *r = SDL_CreateRenderer(w, -1,
                                         SDL_RENDERER_ACCELERATED|
                                             SDL_RENDERER_PRESENTVSYNC);
    if(!r) {
        error("Error creating rendering context");
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *a = IMG_LoadTexture(r, "res/jacey.png");
    if(!a) {
        error("Error loading image");
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *b = IMG_LoadTexture(r, "res/nova.png");
    if(!b) {
        error("Error loading image");
        SDL_DestroyTexture(a);
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                case SDL_MOUSEBUTTONDOWN:
                    quit = 1;
                    break;
            }
        }

        if(SDL_RenderClear(r))
            error("Error clearing the rendering context");

        int w, h;
        if(SDL_QueryTexture(b, NULL, NULL, &w, &h))
            error("Unable to look up texture");

        ren(b, r, 0, 0);
        ren(b, r, w, 0);
        ren(b, r, 0, h);
        ren(b, r, w, h);

        if(SDL_QueryTexture(a, NULL, NULL, &w, &h))
            error("Unable to look up texture");

        // TODO probably dont assume the screen width is the default
        // width for a resizable window lol
        int x = INIT_WIDTH / 2 - w / 2;
        int y = INIT_HEIGHT / 2 - h / 2;
        ren(a, r, x, y);

        SDL_RenderPresent(r);
    }

    SDL_DestroyTexture(b);
    SDL_DestroyTexture(a);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
}
