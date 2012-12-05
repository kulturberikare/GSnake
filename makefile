CCC = g++
VERSION = 4.7.2
CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra
LDFLAGS = -L/sw/gcc-4.7.2/lib -static-libstdc++

GSnake: GSnake.o GSnakeEvent.o GSurface.o GSnakeAnimation.o GSnakeObject.o
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o GSnake GSnake.o GSnakeEvent.o GSurface.o GSnakeAnimation.o GSnakeObject.o -lSDL -lSDL_image

GSnake.o: Define.h GSnake.h GSnake.cc
	$(CCC) $(CCFLAGS) -c GSnake.cc

GSnakeEvent.o: GSnakeEvent.h GSnakeEvent.cc
	$(CCC) $(CCFLAGS) -c GSnakeEvent.cc

GSurface.o: GSurface.h GSurface.cc
	$(CCC) $(CCFLAGS) -c GSurface.cc

GSnakeAnimation.o: GSnakeAnimation.h GSnakeAnimation.cc
	$(CCC) $(CCFLAGS) -c GSnakeAnimation.cc

GSnakeObject.o: Define.h GSnakeObject.h GSnakeObject.cc
	$(CCC) $(CCFLAGS) -c GSnakeObject.cc

# Städa arbetsmappen

clean:
	@ \rm -f *.o
