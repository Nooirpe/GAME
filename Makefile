CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
CLIBS = -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main \
        -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
OBJECTS = GameUnity.o main.o

all: main   

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(CLIBS)

# Add dependency information to avoid unnecessary recompilation
main.o: main.cpp defs.h graphics.h player.h animation.h game.h obstacle.h stage.h cursor.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(CLIBS)

GameUnity.o: GameUnity.cpp graphics.h cursor.h player.h animation.h game.h obstacle.h stage.h \
            graphics.cpp animation.cpp player.cpp cursor.cpp obstacle.cpp stage.cpp game.cpp
	$(CXX) $(CXXFLAGS) -c GameUnity.cpp $(CLIBS)

run:
	./main

.PHONY : clean
clean:
	-del -f *.o *.exe