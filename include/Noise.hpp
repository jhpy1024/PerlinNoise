#ifndef NOISE_HPP
#define NOISE_HPP

#include <vector>
#include <functional>

class Noise
{
    public:
        static float getNoise(int x, unsigned functionIndex);

        static unsigned getNumNoiseFunctions();

    private:
        static std::vector<std::function<float(int)>> m_NoiseFunctions;
};

#endif
