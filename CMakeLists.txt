cmake_minimum_required(VERSION 3.15)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment_4 main.cpp src/Image.h src/Image.cpp src/Triangle.h src/Vertex.h src/Texture.h src/Texture.cpp src/Render.cpp src/Render.h src/Vector.h src/Point.h src/Camera.h src/Ray.h src/Matrix4x4.cpp src/Matrix4x4.h)