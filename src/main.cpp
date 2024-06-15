#include <array>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char** argv) {
    constexpr int IMAGE_WIDTH = 256;
    constexpr int IMAGE_HEIGHT = 256;
    constexpr int CHANNEL_NUM = 3;  // Image is in RGB format

    std::array<unsigned char, IMAGE_WIDTH * IMAGE_HEIGHT * CHANNEL_NUM> pixelData {};

    int pixelDataIndex = 0;

    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - i) << ' ' << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            auto r = double(j) / (IMAGE_WIDTH - 1);
            auto g = double(i) / (IMAGE_HEIGHT - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            pixelData[pixelDataIndex++] = ir;
            pixelData[pixelDataIndex++] = ig;
            pixelData[pixelDataIndex++] = ib;
        }
    }

    stbi_write_png("image.png", IMAGE_WIDTH, IMAGE_HEIGHT, CHANNEL_NUM, pixelData.data(), IMAGE_WIDTH * CHANNEL_NUM);

    std::clog << "\rDone.                 \n";
}