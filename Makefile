all: compile link run clean

compile:
	g++ -c main.cpp -o release/main.o -I"C:\Users\zahir\Documents\libraries\SFML-2.6.1\include" -DSFML_STATIC -DSFML_AUDIO_STATIC -DSFML_GRAPHICS_STATIC -DSFML_WINDOW_STATIC -DSFML_SYSTEM_STATIC -DSFML_NETWORK_STATIC

link:
	g++ release/main.o -o release/main.exe -L"C:\Users\zahir\Documents\libraries\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg -lopenal32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -static-libgcc -static-libstdc++

run:
	release/main.exe

clean:
	del release/main.o
	del release/main.exe
