CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
INCLUDES = -Isrc/include
LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2

OBJECTS = main.o GameUnity.o

all: main

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(LIBS)

# Main program files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

GameUnity.o: GameUnity.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: all
	.\main

.PHONY: clean all run

clean:
ifeq ($(OS),Windows_NT)
	del /Q /F main.exe *.o 2>NUL || echo "Already clean"
else
	rm -f main *.o *.exe
endif