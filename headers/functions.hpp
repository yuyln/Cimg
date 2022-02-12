#ifndef __FUNC
#define __FUNC

#ifndef OPENCLCOMP
#include <cinttypes>
#include <cmath>
#endif

#include <vector.hpp>
#define R 0
#define G 1
#define B 2
#define A 3

typedef Vec3 RGB;
typedef Vec4 RGBA;

#ifndef OPENCLCOMP
typedef uint8_t int_8;
typedef uint32_t int_32;
#else
typedef uchar int_8;
typedef uint int_32;
#endif

typedef int_32 RGBA32;
typedef int_32 RGB32;

#ifndef OPENCLCOMP
static double const pi = acos(-1.0);
#endif

inline int_8 GetAlpha(RGBA32 f)
{
    return (f & 0xFF000000) >> 8 * 3;
}

inline int_8 GetRed(RGBA32 f)
{
    return (f & 0x000000FF) >> 8 * 0;
}

inline int_8 GetGreen(RGBA32 f)
{
    return (f & 0x0000FF00) >> 8 * 1;
}

inline int_8 GetBlue(RGBA32 f)
{
    return (f & 0x00FF0000) >> 8 * 2;
}

inline RGB32 ToRGB(int_8 r, int_8 g, int_8 b)
{
    return r << 8 * 2 | g << 8 * 1 | b << 8 * 0;
}

inline RGBA32 ToRGBA32I8(int_8 r, int_8 g, int_8 b, int_8 a)
{
    return b << 8 * 2 | g << 8 * 1 | r << 8 * 0 | a << 8 * 3;
}

inline RGBA32 ToRGBA32D(double r, double g, double b, double a)
{
    return ((int_32)((size_t)(fabs(b) * 255.0) & 255)) << 8 * 2 |
           ((int_32)((size_t)(fabs(g) * 255.0) & 255)) << 8 * 1 |
           ((int_32)((size_t)(fabs(r) * 255.0) & 255)) << 8 * 0 |
           ((int_32)((size_t)(fabs(a) * 255.0) & 255)) << 8 * 3;
}

inline RGBA32 ToRGBA32V4(Vec4 v)
{
    Vec4FixLower(&v, 0.0);
    Vec4FixUpper(&v, 1.0);
    return ((int_32)((size_t)(fabs(v.p[B]) * 255.0) & 255)) << 8 * 2 |
           ((int_32)((size_t)(fabs(v.p[G]) * 255.0) & 255)) << 8 * 1 |
           ((int_32)((size_t)(fabs(v.p[R]) * 255.0) & 255)) << 8 * 0 |
           ((int_32)((size_t)(fabs(v.p[A]) * 255.0) & 255)) << 8 * 3;
}

#endif
