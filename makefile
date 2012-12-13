CCC = g++
VERSION = 4.7.2
CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra
LDFLAGS = -L/sw/gcc-4.7.2/lib -static-libstdc++

# Filkataloger där andra delar av programet finns.
SOURCE = ./src

CPPFLAGS += -I$(SOURCE)

GSnake: Menu.o Graphics.o GSnakeEvent.o Sound.o GSnake.o GSnakeObject.o Runner.o Snake.o
	$(CCC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o GSnake Menu.o Graphics.o GSnakeEvent.o Sound.o GSnake.o Runner.o GSnakeObject.o Snake.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

GSnake.o: $(SOURCE)/Define.h $(SOURCE)/GSnake.h $(SOURCE)/GSnake.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/GSnake.cc

GSnakeObject.o: $(SOURCE)/Define.h $(SOURCE)/GSnakeObject.h $(SOURCE)/GSnakeObject.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/GSnakeObject.cc

GSnakeEvent.o: $(SOURCE)/GSnakeEvent.h $(SOURCE)/GSnakeEvent.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/GSnakeEvent.cc

Graphics.o: $(SOURCE)/Graphics.h $(SOURCE)/Graphics.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/Graphics.cc

Sound.o: $(SOURCE)/Sound.h $(SOURCE)/Sound.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/Sound.cc

Menu.o: $(SOURCE)/Menu.h $(SOURCE)/Menu.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/Menu.cc

Runner.o: $(SOURCE)/Runner.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/Runner.cc

Snake.o: $(SOURCE)/Snake.h $(SOURCE)/Snake.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(SOURCE)/Snake.cc

# Städa arbetsmappen
clean:
	@ \rm -f *.o
