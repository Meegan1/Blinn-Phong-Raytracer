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

    bool intersects(Triangle triangle) {
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

        Vector s = point - p;

        Vector sp(s.dot(u), s.dot(w), s.dot(n));
        Vector lp(direction.dot(u), direction.dot(w), direction.dot(n));
        float t = -(origin-p).dot(n)/direction.dot(n);

        Vector o = origin + direction*t;

        Vector ps = p - p;
        Vector rs = r - p;
        Vector qs = q - p;

        Vector psp(ps.dot(u), ps.dot(w), ps.dot(n));
        Vector rsp(rs.dot(u), rs.dot(w), rs.dot(n));
        Vector qsp(qs.dot(u), qs.dot(w), qs.dot(n));


        Triangle triangle1(Vertex(psp, RGB(0, 0, 0), UV(0, 0)),
                Vertex(rsp, RGB(0, 0, 0), UV(0, 0)),
               Vertex(qsp, RGB(0, 0, 0), UV(0, 0)));

        float a, b, c;
        triangle1.get_barycentric(sp, a, b, c);

        if(a < 0 || a > 1 || b < 0 || b > 1 || c < 0 || c > 1)
            return false;

        return true;
    }
};