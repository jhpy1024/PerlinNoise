#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include <vector>
#include <functional>

class PerlinNoise
{
    public:
        PerlinNoise(float seed = 0.f);

        float operator()(float x, float y, float zoom = 75.f, float persistence = 0.5f, unsigned numOctaves = 2);

        void setSeed(float seed);

    private:
        float getNoise(float x, float y) const;
        float getPerlinNoise(float x, float y) const;

    private:
        float m_Seed;
};

#endif

