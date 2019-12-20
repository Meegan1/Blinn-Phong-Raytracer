//
// Created by Jake Meegan on 28/11/2019.
//


#ifndef ASSIGNMENT_3_RAY_H
#define ASSIGNMENT_3_RAY_H


#include "Vector.h"

#define EPSILON 0.0000001

struct Ray {
    Vector origin;
    Vector direction;

    Ray(Vector origin, Vector direction) : origin(origin), direction(direction.normalize()) {}

    bool intersects(Triangle &triangle, Vector &point, float &distance, float &alpha, float &beta, float &gamma) {
        Vector p = triangle.A.position;
        Vector q = triangle.B.position;
        Vector r = triangle.C.position;

        // triangle vectors
        Vector u = q - p;
        Vector v = r - p;

        // plane vectors
        Vector n = u.cross(v).normalize();
        Vector w = n.cross(u);

        float nom = (p - origin).dot(n);
        float denom = direction.dot(n);
        double t = nom/denom;

        distance = t;

        // if point is behind camera
        if(t < 0.0001)
            return false;

        point = origin + direction*t;

        Vector s = point - p;
        Vector sp(s.dot(u), s.dot(w), s.dot(n));

        Vector ps = p - p;
        Vector rs = r - p;
        Vector qs = q - p;

        Vector psp(ps.dot(u), ps.dot(w), ps.dot(n));
        Vector qsp(qs.dot(u), qs.dot(w), qs.dot(n));
        Vector rsp(rs.dot(u), rs.dot(w), rs.dot(n));

        Triangle triangle1(
                Vertex(psp, RGB(0, 0, 0), UV(0, 0)),
                Vertex(qsp, RGB(0, 0, 0), UV(0, 0)),
                Vertex(rsp, RGB(0, 0, 0), UV(0, 0))
        );

        triangle1.get_barycentric(sp, alpha, beta, gamma);

        return !(alpha < -EPSILON || beta < -EPSILON || gamma < -EPSILON );
    }

    bool intersects(Triangle &triangle) {
        Vector point;
        float alpha, beta, gamma, distance;
        return intersects(triangle, point, distance, alpha, beta, gamma);
    }
    bool intersects(Triangle &triangle, float &alpha, float &beta, float &gamma) {
        Vector point;
        float distance;
        return intersects(triangle, point, distance, alpha, beta, gamma);
    }

    bool intersects(Triangle &triangle, Vector &point, float &alpha, float &beta, float &gamma) {
        float distance;
        return intersects(triangle, point,distance, alpha, beta, gamma);
    }

    bool intersects(Triangle &triangle, Vector &point, float &distance) {
        float alpha, beta, gamma;
        return intersects(triangle, point, distance, alpha, beta, gamma);
    }

    bool intersects(Triangle &triangle, float &distance) {
        Vector point;
        float alpha, beta, gamma;
        return intersects(triangle, point, distance, alpha, beta, gamma);
    }
};
#endif //ASSIGNMENT_3_RAY_H
