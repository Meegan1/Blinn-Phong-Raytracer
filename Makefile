a.out: main.o Render.o Image.o Texture.o
	g++ -std=c++11 main.o Render.o Image.o Texture.o

main.o: main.cpp src/Image.h src/Render.h src/Texture.h src/Triangle.h src/Vertex.h
	g++ -std=c++11 -c main.cpp

Render.o: src/Render.cpp src/Render.h
	g++ -std=c++11 -c Render.cpp

Texture.o: src/Texture.cpp src/Texture.h
	g++ -std=c++11 -c Texture.cpp

Image.o: src/Image.cpp src/Image.h
	g++ -std=c++11 -c Image.cpp