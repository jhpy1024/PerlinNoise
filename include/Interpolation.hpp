#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

class Interpolation
{
    public:
        static float linear(float a, float b, float x);
        static float cosine(float a, float b, float x);
        static float cubic(float beforeA, float a, float b, float afterB, float x);

    private:
        static const float PI;
};

#endif

