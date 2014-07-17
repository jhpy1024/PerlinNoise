#include "Noise.hpp"
#include <cassert>

std::vector<std::vector<long>> Noise::m_Primes = 
{
    { 14557, 788913, 1376312323, 1073741827 },
    { 15581, 788947, 1376312543, 1073741789 },
    { 15683, 789137, 1376312783, 1073741971 },
    { 15731, 789221, 1376312589, 1073741824 },
    { 16069, 789533, 1377313061, 1073842787 },
    { 16253, 789721, 1377313391, 1073843167 }
};

float Noise::getNoise(int x, int y, unsigned functionIndex)
{
    assert(functionIndex < m_Primes.size());
    return noiseFunction(x, y, functionIndex);
}

float Noise::noiseFunction(int x, int y, unsigned functionIndex)
{
    auto& primes = m_Primes[functionIndex];

    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * primes[0] + primes[1]) + primes[2]) & 0x7fffffff) / (float) primes[3]);
}

float Noise::getSmoothNoise(int x, int y, unsigned functionIndex)
{
    float corners = (getNoise(x-1, y-1, functionIndex) + getNoise(x+1, y-1, functionIndex) + getNoise(x+1, y+1, functionIndex) + getNoise(x-1, y+1, functionIndex)) / 16.f;
    float sides = (getNoise(x-1, y, functionIndex) + getNoise(x, y-1, functionIndex) + getNoise(x+1, y, functionIndex) + getNoise(x, y+1, functionIndex)) / 8.f;
    float center = getNoise(x, y, functionIndex) / 4.f;

    return corners + sides + center;
}

unsigned Noise::getNumNoiseFunctions()
{
    return m_Primes.size();
}
