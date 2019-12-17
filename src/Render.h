//
// Created by Jake Meegan on 17/11/2019.
//

#ifndef ASSIGNMENT_3_RENDER_H
#define ASSIGNMENT_3_RENDER_H


class Render {
public:
    static void intersection();

    static void barycentric();

    // Clamp value between 0-255
    static int clamp(int value);

    static void ambient();

    static void specular();

    static void diffuse();

    static void blinn_phong();

    static void shadow();
};


#endif //ASSIGNMENT_3_RENDER_H
