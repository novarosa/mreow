#include <stdio.h>

#include <SDL2/SDL.h>

// TODO idk maybe figure out a better default than 1200x1200
#define INIT_WIDTH 1200
#define INIT_HEIGHT 1200

void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, SDL_GetError());
}

SDL_Texture* load(char *path, SDL_Renderer *r) {
    SDL_Texture *t;
    SDL_Surface *s = SDL_LoadBMP(path);
    if(s) {
        t = SDL_CreateTextureFromSurface(r, s);
        SDL_FreeSurface(s);
        if(!t)
            error("Error creating texture from image");
    } else
        error("Error loading image");

    return t;
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

    SDL_Texture *a = load("res/jacey.bmp", r);
    if(!a) {
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *b = load("res/nova.bmp", r);
    if(!b) {
        SDL_DestroyTexture(a);
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        SDL_Quit();
        return 1;
    }

    // TwinkleBearDev describes this loop as "sleepy" 😭
    for(int i = 0; i < 3; i++) {
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
        SDL_Delay(1000);
    }

    SDL_DestroyTexture(b);
    SDL_DestroyTexture(a);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
}
