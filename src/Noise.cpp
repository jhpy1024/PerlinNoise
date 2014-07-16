#include "Noise.hpp"
#include <cassert>

std::vector<std::function<float(int)>> Noise::m_NoiseFunctions =
{
[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 14557 + 788913) + 1376312323) & 0x7fffffff) / 1073741827.f);
},

[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 15581 + 788947) + 1376312543) & 0x7fffffff) / 1073741789.f);
},

[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 15683 + 789137) + 1376312783) & 0x7fffffff) / 1073741971.f);
},

[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.f);
},

[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 16069 + 789533) + 1377313061) & 0x7fffffff) / 1073842787.f);
},

[](int x)
{
    x = (x << 13) ^ x;
    return (1.f - ((x * (x * x * 16253 + 789721) + 1377313391) & 0x7fffffff) / 1073843167.f);
}
};

float Noise::getNoise(int x, unsigned functionIndex)
{
    assert(functionIndex < m_NoiseFunctions.size());

    return m_NoiseFunctions[functionIndex](x);
}

unsigned Noise::getNumNoiseFunctions()
{
    return m_NoiseFunctions.size();
}
