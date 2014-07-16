#include "Interpolation.hpp"
#include <cmath>

const float Interpolation::PI = 3.141592653589793238462643383279f;

float Interpolation::linear(float a, float b, float x)
{
    return (a * (1 - x) + b * x);
}

float Interpolation::cosine(float a, float b, float x)
{
    float ft = x * PI;
    float f = (1 - std::cos(ft)) * .5f;

    return (a * (1 - f) + b * f);
}

float Interpolation::cubic(float beforeA, float a, float b, float afterB, float x)
{
    float p = (afterB - b) - (beforeA - a);
    float q = (beforeA - a) - p;
    float r = b - beforeA;
    float s = a;

    return p * std::pow(x, 3.f) + q * std::pow(x, 2.f) + r * x + s;
}
