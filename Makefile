CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
CLIBS = -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main \
        -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
OBJECTS = GameUnity.o main.o

all: main copy_dlls

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(CLIBS)

copy_dlls:
	copy src\\include\\SDL2\\*.dll .

main.o: main.cpp Headers/*.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(CLIBS)

GameUnity.o: GameUnity.cpp Headers/*.h Sources/*.cpp
	$(CXX) $(CXXFLAGS) -c GameUnity.cpp $(CLIBS)

run: all
	./main

.PHONY : clean copy_dlls
clean:
	-del -f *.o *.exe *.dll