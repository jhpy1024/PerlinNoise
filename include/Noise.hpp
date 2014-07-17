#ifndef NOISE_HPP
#define NOISE_HPP

#include <vector>
#include <functional>

class Noise
{
    public:
        static float getNoise(int x, int y, unsigned functionIndex);
        static float getSmoothNoise(int x, int y, unsigned functionIndex);

        static unsigned getNumNoiseFunctions();

    private:
        static float noiseFunction(int x, int y, unsigned functionIndex);

    private:
        static std::vector<std::vector<long>> m_Primes;
};

#endif

