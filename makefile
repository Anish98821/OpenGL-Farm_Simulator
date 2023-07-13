all:
	g++ -g --std=c++17 -I./include -L./lib ./src/main.cpp -lopengl32 -lglut32 -lglfw3dll -lGLU32 -lGlaux -lglui32 -o main
	./bin/main