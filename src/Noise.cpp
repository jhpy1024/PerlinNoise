#include "Noise.hpp"
#include <cassert>

std::vector<std::function<float(int, int)>> Noise::m_NoiseFunctions =
{
[](int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * 14557 + 788913) + 1376312323) & 0x7fffffff) / 1073741827.f);
},

[](int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * 15581 + 788947) + 1376312543) & 0x7fffffff) / 1073741789.f);
},

[](int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * 15683 + 789137) + 1376312783) & 0x7fffffff) / 1073741971.f);
},

[](int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.f);
},

[](int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.f - ((n * (n * n * 16069 + 789533) + 1377313061) & 0x7fffffff) / 1073842787.f);
},

[](int x, int y)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 16253 + 789721) + 1377313391) & 0x7fffffff) / 1073843167.f);
}
};

float Noise::getNoise(int x, int y, unsigned functionIndex)
{
    assert(functionIndex < m_NoiseFunctions.size());

    return m_NoiseFunctions[functionIndex](x, y);
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
    return m_NoiseFunctions.size();
}
