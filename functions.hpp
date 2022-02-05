#ifndef __FUNC
#define __FUNC
#include <cinttypes>
#include <cmath>

typedef uint32_t RGBA32;
typedef uint32_t RGB32;
typedef uint8_t R;
typedef uint8_t G;
typedef uint8_t B;
typedef uint8_t A;

static double const pi = acos(-1.0);

template <typename T>
inline T max(T v1, T v2)
{
    return v1 * (v1 >= v2) + v2 * (v2 > v1);
}

inline uint8_t GetAlpha(RGBA32 f)
{
    return (f & 0xFF000000) >> 8 * 3;
}

inline uint8_t GetRed(RGBA32 f)
{
    return (f & 0x00FF0000) >> 8 * 2;
}

inline uint8_t GetGreen(RGBA32 f)
{
    return (f & 0x0000FF00) >> 8 * 1;
}

inline uint8_t GetBlue(RGBA32 f)
{
    return (f & 0x000000FF) >> 8 * 0;
}

inline RGB32 ToRGB(uint8_t R, uint8_t G, uint8_t B)
{
    return R << 8 * 2 | G << 8 * 1 | B << 8 * 0;
}

inline RGBA32 ToRGBA32(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    return B << 8 * 2 | G << 8 * 1 | R << 8 * 0 | A << 8 * 3;
}

#endif
