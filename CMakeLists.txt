cmake_minimum_required(VERSION 3.15)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment_4 main.cpp src/Image.h src/Image.cpp src/Triangle.h src/Vertex.h src/Render.cpp src/Render.h src/Vector.h src/Camera.h src/Ray.h src/Light.h src/Color.h)