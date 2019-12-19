#include "src/Render.h"

int main() {
    // Execute methods
    Render::intersection();
    Render::barycentric();
    Render::ambient();
    Render::specular();
    Render::diffuse();
    Render::blinn_phong();
    Render::shadow();
    Render::cornell();
    return 0;
}