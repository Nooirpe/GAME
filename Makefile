CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
CLIBS = -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main \
        -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
OBJECTS = main.o

all: main   

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(CLIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(CLIBS)
	
run:
	./main

.PHONY : clean
clean:
	-del -f *.o *.exe