#ifndef NOISE_HPP
#define NOISE_HPP

#include <vector>
#include <functional>

class Noise
{
    public:
        static float getNoise(float x, float y);
        static float getPerlinNoise(float x, float y);
};

#endif

