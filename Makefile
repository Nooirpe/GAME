CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
CLIBS = -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main \
        -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
OBJECTS = GameUnity.o main.o

all: main   

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(CLIBS)

main.o: main.cpp Headers/*.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(CLIBS)

GameUnity.o: GameUnity.cpp Headers/*.h Sources/*.cpp
	$(CXX) $(CXXFLAGS) -c GameUnity.cpp $(CLIBS)

run:
	./main

.PHONY : clean
clean:
	-del -f *.o *.exe