## game (?)

To start, this repo will mostly be adapted from the [TwinkleBearDev SDL2
tutorial](https://www.willusher.io/pages/sdl2), with the main
modifications being adapting it to C and make from C++ and cmake, as
well as just generally adapting it to a workflow im more
comfortable/familiar with. After I get through the tutorial the plan is
to adapt it into a more comprehensive game writing framework and
eventually game according to a private roadmap at Rosaline Software.

## dependencies
- libSDL2
- make
- cc

*Nota bene*: I try to make this code work portably in any environment,
but testing is done on FreeBSD with clang and bmake for the time being.
I also plan to start testing this on macOS as well with gmake and clang.

## synopsis
`$ make && ./mreow`
