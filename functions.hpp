#ifndef __FUNC
#define __FUNC
#include <cinttypes>
#include <cmath>
#include "vector.hpp"
#define R 0
#define G 1
#define B 2
#define A 3

typedef Vec3 RGB;
typedef Vec4 RGBA;
typedef uint32_t RGBA32;
typedef uint32_t RGB32;

static double const pi = acos(-1.0);

inline uint8_t GetAlpha(RGBA32 f)
{
    return (f & 0xFF000000) >> 8 * 3;
}

inline uint8_t GetRed(RGBA32 f)
{
    return (f & 0x000000FF) >> 8 * 0;
}

inline uint8_t GetGreen(RGBA32 f)
{
    return (f & 0x0000FF00) >> 8 * 1;
}

inline uint8_t GetBlue(RGBA32 f)
{
    return (f & 0x00FF0000) >> 8 * 2;
}

inline RGB32 ToRGB(uint8_t r, uint8_t g, uint8_t b)
{
    return r << 8 * 2 | g << 8 * 1 | b << 8 * 0;
}

inline RGBA32 ToRGBA32(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return b << 8 * 2 | g << 8 * 1 | r << 8 * 0 | a << 8 * 3;
}

inline RGBA32 ToRGBA32(double r, double g, double b, double a)
{
    return ((uint32_t)((size_t)(fabs(b) * 255.0) & 255)) << 8 * 2 | 
           ((uint32_t)((size_t)(fabs(g) * 255.0) & 255)) << 8 * 1 | 
           ((uint32_t)((size_t)(fabs(r) * 255.0) & 255)) << 8 * 0 | 
           ((uint32_t)((size_t)(fabs(a) * 255.0) & 255)) << 8 * 3;
    // return (uint32_t) B << 8 * 2 | (uint32_t) G << 8 * 1 | (uint32_t) R << 8 * 0 | (uint32_t) A << 8 * 3;
}

inline RGBA32 ToRGBA32(Vec4 v)
{
    return ((uint32_t)((size_t)(fabs(v.p[B]) * 255.0) & 255)) << 8 * 2 | 
           ((uint32_t)((size_t)(fabs(v.p[G]) * 255.0) & 255)) << 8 * 1 | 
           ((uint32_t)((size_t)(fabs(v.p[R]) * 255.0) & 255)) << 8 * 0 | 
           ((uint32_t)((size_t)(fabs(v.p[A]) * 255.0) & 255)) << 8 * 3;
    // return (uint32_t) B << 8 * 2 | (uint32_t) G << 8 * 1 | (uint32_t) R << 8 * 0 | (uint32_t) A << 8 * 3;
}

#endif
