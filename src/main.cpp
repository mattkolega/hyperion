#include <array>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "colour.hpp"
#include "ray.hpp"
#include "vec3.hpp"

bool hitSphere(const Point3& center, double radius, const Ray& r)
{
    Vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

Colour rayColour(const Ray& r)
{
    if (hitSphere(Point3(0, 0, -1), 0.5, r)) {
        return Colour(1, 0, 0);
    }

    Vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5*(unitDirection.y() + 1.0);
    return (1.0-a)*Colour(1.0, 1.0, 1.0) + a*Colour(0.5, 0.7, 1.0);
}

int main(int argc, char** argv)
{
    constexpr auto ASPECT_RATIO = 16.0 / 9.0;
    constexpr int IMAGE_WIDTH = 400;
    
    constexpr int IMAGE_HEIGHT = (int(IMAGE_WIDTH / ASPECT_RATIO) < 1) ? 1 : int(IMAGE_WIDTH / ASPECT_RATIO);

    constexpr int CHANNEL_NUM = 3;  // Image is in RGB format

    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(IMAGE_WIDTH) / IMAGE_HEIGHT);
    auto cameraCenter = Point3(0, 0, 0);

    auto viewportU = Vec3(viewportWidth, 0, 0);
    auto viewportV = Vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewportU / IMAGE_WIDTH;
    auto pixelDeltaV = viewportV / IMAGE_HEIGHT;

    auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    std::vector<unsigned char> imageData {};

    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - i) << ' ' << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            auto pixelCenter = pixel00Loc + (j * pixelDeltaU) + (i * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            Colour pixelColour = rayColour(r);
            writeColour(imageData, pixelColour);
        }
    }

    stbi_write_png("image.png", IMAGE_WIDTH, IMAGE_HEIGHT, CHANNEL_NUM, imageData.data(), IMAGE_WIDTH * CHANNEL_NUM);

    std::clog << "\rDone.                 \n";
}