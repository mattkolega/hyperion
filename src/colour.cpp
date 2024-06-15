#include "colour.hpp"

#include "vec3.hpp"

void writeColour(std::vector<unsigned char>& imageData, const Colour& pixelColour)
{
    auto r = pixelColour.x();
    auto g = pixelColour.y();
    auto b = pixelColour.z();

    int rByte = int(255.999 * r);
    int gByte = int(255.999 * g);
    int bByte = int(255.999 * b);

    imageData.push_back(rByte);
    imageData.push_back(gByte);
    imageData.push_back(bByte);
}