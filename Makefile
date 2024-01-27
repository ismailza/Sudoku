all: compile link

# SFML include and lib directories
SFML_INCLUDE = "C:\Users\zahir\Documents\libraries\SFML-2.6.1\include"
SFML_LIB = "C:\Users\zahir\Documents\libraries\SFML-2.6.1\lib"

# Compiler flags
CFLAGS = -DSFML_STATIC -DSFML_AUDIO_STATIC -DSFML_GRAPHICS_STATIC -DSFML_WINDOW_STATIC -DSFML_SYSTEM_STATIC -DSFML_NETWORK_STATIC

# Linker flags
LFLAGS = -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg -lopenal32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -static-libgcc -static-libstdc++

# Executable name
EXECUTABLE = main.exe

compile:
	g++ -c main.cpp -o release/main.o -I$(SFML_INCLUDE) $(CFLAGS)

link:
	g++ release/main.o -o release/$(EXECUTABLE) -L$(SFML_LIB) $(LFLAGS)

run:
	release/$(EXECUTABLE)

clean:
	del release/main.o
	del release/$(EXECUTABLE)

	.PHONY: all run clean