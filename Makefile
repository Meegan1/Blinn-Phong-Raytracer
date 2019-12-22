a.out: main.o Render.o Image.o
	g++ -std=c++11 main.o Render.o Image.o

main.o: main.cpp src/Image.h src/Render.h src/Triangle.h src/Vertex.h src/Vector.h src/World.h src/Ray.h src/Color.h
	g++ -std=c++11 -c main.cpp

Render.o: src/Render.cpp src/Render.h
	g++ -std=c++11 -c src/Render.cpp

Texture.o: src/Texture.cpp src/Texture.h
	g++ -std=c++11 -c src/Texture.cpp

Image.o: src/Image.cpp src/Image.h
	g++ -std=c++11 -c src/Image.cpp