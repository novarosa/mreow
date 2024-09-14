# the /usr/local paths here may not be necessary depending on your
# distro/setup
# included here because im using clang on FreeBSD (clang doesnt put
# /usr/local on the default include path but FreeBSD puts packages in
# /usr/local)
INC=-I/usr/local/include
LIB=-L/usr/local/lib -lSDL2 -lSDL2_image

CFLAGS=${INC} ${LIB} -O3 -s

SRC=src/*.c

all: mreow

mreow: ${SRC}
	cc ${CFLAGS} ${SRC} -o $@

clean:
	rm mreow
