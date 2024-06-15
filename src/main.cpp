#include <array>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "colour.hpp"
#include "vec3.hpp"

int main(int argc, char** argv) {
    constexpr int IMAGE_WIDTH = 256;
    constexpr int IMAGE_HEIGHT = 256;
    constexpr int CHANNEL_NUM = 3;  // Image is in RGB format

    std::vector<unsigned char> imageData {};

    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - i) << ' ' << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            auto pixelColour = Colour(double(j)/(IMAGE_WIDTH-1), double(i)/(IMAGE_HEIGHT-1), 0);
            writeColour(imageData, pixelColour);
        }
    }

    stbi_write_png("image.png", IMAGE_WIDTH, IMAGE_HEIGHT, CHANNEL_NUM, imageData.data(), IMAGE_WIDTH * CHANNEL_NUM);

    std::clog << "\rDone.                 \n";
}