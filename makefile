all:
	g++ *.cpp -std=c++11 -lGL -lsfml-graphics -lsfml-system -lsfml-window -lGLEW -o opengl
run:
	./opengl
