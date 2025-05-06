CXX = g++
CXXFLAGS = -g -Wall -std=c++11
INCLUDES = -Isrc/include
LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2

# Unity build - all source files are included in GameUnity.cpp
OBJECTS = main.o GameUnity.o

all: RunMo

RunMo: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o RunMo $(OBJECTS) $(LIBS)

# Main program files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

GameUnity.o: GameUnity.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: all
	.\RunMo

# Create a zip file for distribution
zip:
	powershell Compress-Archive -Path *, Assets/*, Headers/*, Sources/*, src/* -DestinationPath RunMo_Windows.zip -Force

.PHONY: clean all run zip

clean:
ifeq ($(OS),Windows_NT)
	del /Q /F RunMo.exe *.o 2>NUL || echo "Already clean"
else
	rm -f RunMo *.o
endif
