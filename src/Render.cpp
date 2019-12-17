//
// Created by Jake Meegan on 17/11/2019.
//

#include "Render.h"
#include "Triangle.h"
#include "Camera.h"
#include "Light.h"
#include "Image.h"


void Render::intersection() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            if (r.intersects(triangle)) {
                image[x][y].r = 0;
                image[x][y].g = 0;
                image[x][y].b = 0;
            }
        }
    }
    image.toFile("intersection");
}

void Render::barycentric() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            if (r.intersects(triangle, alpha, beta, gamma)) {
                RGB color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                image[x][y].r = color.r;
                image[x][y].g = color.g;
                image[x][y].b = color.b;
            }
        }
    }
    image.toFile("barycentric");
}


void Render::ambient() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);
    Light light(camera.position, camera.forward, Vector(1.0f), Vector(0), 0);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            Vector point;
            if (r.intersects(triangle, point, alpha, beta, gamma)) {
                RGB color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                Vector ambient = color * light.ambient * triangle.ambient;
                color = ambient;

                image[x][y].r = color.r;
                image[x][y].g = color.g;
                image[x][y].b = color.b;
            }
        }
    }
    image.toFile("ambient");
}

void Render::specular() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);
    Vector normal = (triangle.B.position - triangle.A.position).cross((triangle.C.position - triangle.A.position)).normalize();
    Light light(camera.position, camera.forward, Vector(1.0f), Vector(255), 32);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            Vector point;
            if (r.intersects(triangle, point, alpha, beta, gamma)) {
                RGB color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                Vector halfDirection = (((point-light.position).normalize() + r.direction) / 2).normalize();
                float angle = halfDirection.dot(normal) / (normal.magnitude() * halfDirection.magnitude());
                Vector specular = light.specular * triangle.specular * pow(angle, light.specular_coefficient);
                color = color + specular;

                image[x][y].r = clamp(color.r);
                image[x][y].g = clamp(color.g);
                image[x][y].b = clamp(color.b);
            }
        }
    }
    image.toFile("specular");
}


void Render::diffuse() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);
    Vector normal = (triangle.B.position - triangle.A.position).cross((triangle.C.position - triangle.A.position)).normalize();
    Light light(camera.position, camera.forward, Vector(1.0f), Vector(1.0f), 32);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            Vector point;
            if (r.intersects(triangle, point, alpha, beta, gamma)) {
                RGB color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                float angle = normal.dot(r.direction);
                Vector diffuse = color * (triangle.diffuse * triangle.diffuse_reflectivity * angle);
                color = diffuse;

                image[x][y].r = clamp(color.r);
                image[x][y].g = clamp(color.g);
                image[x][y].b = clamp(color.b);
            }
        }
    }
    image.toFile("diffuse");
}

/*
 * Sets min/max values of value to 0-255
 */
int Render::clamp(int value) {
    if (value > 255)
        return 255;
    else if (value < 0)
        return 0;
    else
        return value;
}

void Render::blinn_phong() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);
    Vector normal = (triangle.B.position - triangle.A.position).cross((triangle.C.position - triangle.A.position)).normalize();
    Light light(camera.position, camera.forward, Vector(1.0f), Vector(255), 32);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            Vector point;
            if (r.intersects(triangle, point, alpha, beta, gamma)) {
                Vector color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                Vector ambient = color * (light.ambient * triangle.ambient);

                Vector halfDirection = (((point-light.position).normalize() + r.direction) / 2).normalize();
                float specular_angle = halfDirection.dot(normal);
                Vector specular = light.specular * triangle.specular * pow(specular_angle, light.specular_coefficient);

                float diffuse_angle = normal.dot(r.direction);
                Vector diffuse = color * (triangle.diffuse * triangle.diffuse_reflectivity * diffuse_angle);

                color = ambient + diffuse + specular;

                image[x][y].r = clamp(color.r);
                image[x][y].g = clamp(color.g);
                image[x][y].b = clamp(color.b);
            }
        }
    }
    image.toFile("blinn_phong");
}

void Render::shadow() {
    Image image(128);

    std::vector<Triangle> triangles;
    triangles.emplace_back(
            Vertex(Vector(-0.04688, -0.84375, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(0.5625, 0.5625, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(-0.60938, 0.40625, 1), RGB(0, 0, 255), UV(0.230169, 0.222781)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    ); // create triangle with attributes

    // floor
    triangles.emplace_back(
            Vertex(Vector(2, -1, 0), RGB(255, 255, 255), UV(0, 0)),
            Vertex(Vector(-2, -1, 5), RGB(255, 255, 255), UV(0, 0)),
            Vertex(Vector(-2, -1, 0), RGB(255, 255, 255), UV(0, 0)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    );
    triangles.emplace_back(
            Vertex(Vector(-2, -1, 5), RGB(255, 255, 255), UV(0, 0)),
            Vertex(Vector(2, -1, 0), RGB(255, 255, 255), UV(0, 0)),
            Vertex(Vector(2, -1, 5), RGB(255, 255, 255), UV(0, 0)),
            Vector(0.1f),
            Vector(1.0f),
            Vector(1.0f),
            1
    );

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);
    Light light(Vector(0, 1, 0), Vector(0, -1, 1), Vector(1.0f), Vector(1.0f), 4);

    for (int y = image.get_height() - 1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));

            float z_buffer = MAXFLOAT;

            for (Triangle &triangle : triangles) {
                float distance;
                float alpha, beta, gamma;
                Vector point;
                if (r.intersects(triangle, point, distance, alpha, beta, gamma)) {
                    if(distance >= z_buffer)
                        continue;
                    z_buffer = distance;

                    // calculate shadow
                    Ray shadow_ray(light.position, point - light.position);
                    float shadow_z = MAXFLOAT;
                    for (Triangle &shadow_triangle : triangles) {
                        float shadow_distance;
                        if(shadow_ray.intersects(shadow_triangle, shadow_distance)) {
                            if(shadow_distance >= shadow_z)
                                continue;
                            shadow_z = shadow_distance;
                        }
                    }
                    float light_distance = MAXFLOAT;
                    shadow_ray.intersects(triangle, light_distance);
                    if(shadow_z != light_distance) {
                        image[x][y].r = 0;
                        image[x][y].g = 0;
                        image[x][y].b = 0;
                        continue;
                    }


                    Vector normal = (triangle.B.position - triangle.A.position).cross(
                            (triangle.C.position - triangle.A.position)).normalize();
                    RGB color = (triangle.A.color * alpha) + (triangle.B.color * beta) + (triangle.C.color * gamma);

                    Vector ambient = color * (light.ambient * triangle.ambient);

                    Vector halfDirection = (((point-light.position).normalize() + r.direction) / 2).normalize();
                    float specular_angle = halfDirection.dot(normal);
                    Vector specular = light.specular * triangle.specular * pow(specular_angle, light.specular_coefficient);

                    float diffuse_angle = normal.dot(r.direction);
                    Vector diffuse = color * (triangle.diffuse * triangle.diffuse_reflectivity * diffuse_angle);

                    color = ambient + diffuse + specular;

                    image[x][y].r = clamp(color.r);
                    image[x][y].g = clamp(color.g);
                    image[x][y].b = clamp(color.b);
                }
            }
        }
    }
    image.toFile("shadow");
}
