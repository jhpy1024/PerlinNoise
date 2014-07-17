#include "PerlinNoise.hpp"
#include "Interpolation.hpp"

#include <cassert>
#include <iostream>
#include <cmath>

PerlinNoise::PerlinNoise(float seed)
    : m_Seed(seed)
{

}

float PerlinNoise::operator()(float x, float y, float zoom, float persistence, unsigned numOctaves)
{
    x += m_Seed;
    y += m_Seed;

    float noise = 0.f;

    for (unsigned i = 0; i < numOctaves; ++i)
    {
        float frequency = std::pow(2.f, (float) i);
        float amplitude = std::pow(persistence, (float) i);

        noise += getPerlinNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
    }

    return noise;
}

void PerlinNoise::setSeed(float seed)
{
    m_Seed = seed;
}

float PerlinNoise::getNoise(float x, float y) const
{
    int n = (int) x + (int) y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return 1.f - ((float) nn / 1073741824.f);
}

float PerlinNoise::getPerlinNoise(float x, float y) const
{
    auto flooredX = std::floor(x);
    auto flooredY = std::floor(y);

    auto s = getNoise(flooredX, flooredY);
    auto t = getNoise(flooredX + 1, flooredY);
    auto u = getNoise(flooredX, flooredY + 1);
    auto v = getNoise(flooredX + 1, flooredY + 1);

    auto lerped1 = Interpolation::cosine(s, t, x - flooredX);
    auto lerped2 = Interpolation::cosine(u, v, x - flooredX);

    return Interpolation::cosine(lerped1, lerped2, y - flooredY);
}
