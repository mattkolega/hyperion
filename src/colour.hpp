#pragma once

#include <vector>

class Vec3;

using Colour = Vec3;

void writeColour(std::vector<unsigned char>& imageData, const Colour& pixelColour);