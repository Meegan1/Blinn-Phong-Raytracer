//
// Created by Jake Meegan on 28/11/2019.
//


#ifndef ASSIGNMENT_3_RAY_H
#define ASSIGNMENT_3_RAY_H

#endif //ASSIGNMENT_3_RAY_H

struct Ray {
    Vector origin;
    Vector direction;

    Ray(Vector origin, Vector direction) : origin(origin), direction(direction) {}

    bool intersects(Triangle &triangle, float &depth, float &alpha, float &beta, float &gamma) {
        Vector p = triangle.A.position;
        Vector q = triangle.B.position;
        Vector r = triangle.C.position;

        // triangle vectors
        Vector u = (q - p).normalize();
        Vector v = (r - p).normalize();

        // plane vectors
        Vector n = u.cross(v).normalize();
        Vector w = n.cross(u).normalize();

        float nom = -(origin - p).dot(n);
        float denom = direction.dot(n);
        Vector point = origin + direction*(nom / denom);
        depth = point.magnitude()/128;

        Vector s = point - p;
        Vector sp(s.dot(u), s.dot(w), s.dot(n));

        Vector ps = p - p;
        Vector rs = r - p;
        Vector qs = q - p;

        Vector psp(ps.dot(u), ps.dot(w), ps.dot(n));
        Vector qsp(qs.dot(u), qs.dot(w), qs.dot(n));
        Vector rsp(rs.dot(u), rs.dot(w), rs.dot(n));

        Triangle triangle1(Vertex(psp, RGB(0, 0, 0), UV(0, 0)),
                           Vertex(qsp, RGB(0, 0, 0), UV(0, 0)),
                           Vertex(rsp, RGB(0, 0, 0), UV(0, 0)));

        triangle1.get_barycentric(sp, alpha, beta, gamma);

        return !(alpha < 0 || beta < 0 || gamma < 0 );
    }

    bool intersects(Triangle &triangle) {
        float depth, alpha, beta, gamma;
        return intersects(triangle, depth, alpha, beta, gamma);
    }
};