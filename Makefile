all: compile run clean

compile:
	g++ -c -o build/main.o src/main.cpp
	g++ -c -o build/graphics.o src/graphics.cpp
	g++ -c -o build/game.o src/game.cpp
	g++ -c -o build/objects.o src/objects.cpp
	g++ -c -o build/audio.o src/audio.cpp
	g++ -o bin/fnaf3 build/main.o build/graphics.o build/game.o build/objects.o build/audio.o -lSDL2_mixer -lSDL2_image -lSDL2

run:
	bin/fnaf3

clean:
	rm -f build/* bin/*

install:
	sudo mkdir -p /opt/fnaf3/
	sudo mkdir -p /opt/fnaf3/assets/
	sudo mkdir -p /opt/fnaf3/bin/
	sudo cp bin/fnaf3 /opt/fnaf3/bin/
	sudo cp -r assets/* /opt/fnaf3/assets/
	sudo cp icon.png /opt/fnaf3/
	sudo cp fnaf3.desktop /usr/share/applications/

uninstall:
	sudo rm -rf /opt/fnaf3/
	sudo rm /usr/share/applications/fnaf3.desktop