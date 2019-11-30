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
//        Vector u = q - p;
//        Vector v = r - p;
//
//        Vector n = u.cross(v).normalize();
//        Vector w = n.cross(u).normalize();
//
//        if(n.dot(direction) < 0.001f)
//            return false;
//
//        float sp = (p - origin).dot(n);
//        float dn = direction.dot(n);
//        Vector o = origin + (direction * (sp / dn));
//
//        Vector calc = p + (u * (n.dot(p)) / n.dot(u));
//
//        if(o.z < 0)
//            return false;
//
//        Vector s = p - direction;
//
//        Vector pcs(o.dot(u), o.dot(w), o.dot(n));
//
//        Vector pcp(p.dot(u), p.dot(w), p.dot(n));
//        Vector pcq(q.dot(u), q.dot(w), q.dot(n));
//        Vector pcr(r.dot(u), r.dot(w), r.dot(n));

        Vector v0v1 = q - p;
        Vector v0v2 = r - p;
        Vector pvec = direction.cross(v0v2);
        float det = v0v1.dot(pvec);

        if (det < 0.0001f) return false;
        // ray and triangle are parallel if det is close to 0
        if (std::fabs(det) < 0.0001f) return false;

        float invDet = 1 / det;

        Vector tvec = origin - p;
        float u = tvec.dot(pvec) * invDet;
        if (u < 0 || u > 1) return false;

        Vector qvec = tvec.cross(v0v1);
        float v = direction.dot(qvec) * invDet;
        if (v < 0 || u + v > 1) return false;

        float t = v0v2.dot(qvec) * invDet;

        return (t > 0.0001f) ? t : false;


//        Triangle triangle1(Vertex(pcp, RGB(0, 0, 0), UV(0, 0)),
//                Vertex(pcq, RGB(0, 0, 0), UV(0, 0)),
//               Vertex(pcr, RGB(0, 0, 0), UV(0, 0)));
//
//        float a, b, c;
//        triangle1.get_barycentric(pcs, a, b, c);

//        if(a < 0 || b < 0 || c < 0)
//            return false;

//        float ne = o.dot(n);
//        float n2 = p.dot(n);
//        float n3 = q.dot(n);
//        float n4 = r.dot(n);




//        Vector pp(p.dot(u), p.dot(w), p.dot(n));
//        Vector pq(q.dot(u), q.dot(w), q.dot(n));
//        Vector pr(r.dot(u), r.dot(w), r.dot(n));

//
//        Vector ss = ps.normalize();
//        Vector pps = pp.normalize();
//
//        float x = n.dot(direction);
//
//        float d = n.dot(triangle.A.position);
//
//        float t = (n.dot(p - origin)) / n.dot(direction);
//
//        if(t < 0)
//            return false;
//
//        Vector psss = origin + (direction * t);



    return true;
    }
};