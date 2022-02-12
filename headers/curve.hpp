#ifndef __CURVE
#define __CURVE
#include <line.hpp>
#include <vector.hpp>
#include <functions.hpp>

#ifndef OPENCLCOMP
typedef struct
{
    LineSegment2D *lines;
    size_t nLines;
} Curve;

void InitCurve(Curve *C, size_t n)
{
    C->nLines = n;
    C->lines = new LineSegment2D[n];
}
#endif

#ifdef OPENCLCOMP
float max_(float a, float b)
{
    return a * (a >= b) + b * (b > a);
}
#endif

#ifndef OPENCLCOMP
void Show(const Curve &c, const float &lw, const float &x, const float &y, float *minD_, float *maxD_, RGBA *rgba)
#else
void Show(global const LineSegment2D *lines, const int nlines, const float lw, const float x, const float y, private float *minD_, private float *maxD_, global RGBA *rgba)
#endif
{
    #ifndef OPENCLCOMP
    float minD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    float maxD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    #else
    float minD = DistanceTwo2D(lines[0], Vec2From(x, y));
    float maxD = DistanceTwo2D(lines[0], Vec2From(x, y));
    #endif

    #ifndef OPENCLCOMP
    for (size_t i = 1; i < c.nLines; i++)
    {
        float d = DistanceTwo2D(c.lines[i], Vec2From(x, y));
    #else
    for (size_t i = 1; i < nlines; i++)
    {
        float d = DistanceTwo2D(lines[i], Vec2From(x, y));
    #endif
        if (d < minD)
        {
            minD = d;
        }
        if (d > maxD)
        {
            maxD = d;
        }
    }
    *minD_ = minD;
    *maxD_ = maxD;

    if (minD < lw * lw)
    {    
        rgba->p[R] = rgba->p[G] = rgba->p[B] = 0.0;
    }
}

#ifndef OPENCLCOMP
void ShowC(const Curve &c, const float &lw, const float &x, const float &y, float *minD_, float *maxD_, RGBA *rgba, const Vec4 &color)
#else
void ShowC(global const LineSegment2D *lines, const int nlines, const float lw, const float x, const float y, private float *minD_, private float *maxD_, global RGBA *rgba, const Vec4 color)
#endif
{
    #ifndef OPENCLCOMP
    float minD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    float maxD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    #else
    float minD = DistanceTwo2D(lines[0], Vec2From(x, y));
    float maxD = DistanceTwo2D(lines[0], Vec2From(x, y));
    #endif

    #ifndef OPENCLCOMP
    for (size_t i = 1; i < c.nLines; i++)
    {
        float d = DistanceTwo2D(c.lines[i], Vec2From(x, y));
    #else
    for (size_t i = 1; i < nlines; i++)
    {
        float d = DistanceTwo2D(lines[i], Vec2From(x, y));
    #endif
        if (d < minD)
        {
            minD = d;
        }
        if (d > maxD)
        {
            maxD = d;
        }
    }
    *minD_ = minD;
    *maxD_ = maxD;

    if (minD < lw * lw)
    {
        rgba->p[R] = color.p[R];
        rgba->p[G] = color.p[G];
        rgba->p[B] = color.p[B];
    }
}
#ifndef OPENCLCOMP
void ShowG(const Curve &c, const float &lw, const float &x, const float &y, float *minD_, float *maxD_, RGBA *rgba, 
           const float &pR, const Vec4 &glowC)
#else
void ShowG(global const LineSegment2D *lines, const int nlines, const float lw, const float x, const float y, private float *minD_, private float *maxD_, global RGBA *rgba, 
           const float pR, const Vec4 glowC)
#endif
{
    float minD, maxD;
    #ifndef OPENCLCOMP
    Show(c, lw, x, y, &minD, &maxD, rgba);
    #else
    Show(lines, nlines, lw, x, y, &minD, &maxD, rgba);
    #endif
    *minD_ = minD;
    *maxD_ = maxD;

    if (minD < lw * lw)
    {
        rgba->p[R] = rgba->p[G] = rgba->p[B] = 0.0;
    }
    else
    {
        float rtemp = rgba->p[R] = glowC.p[R] * exp(-minD / (pR * pR));
        float gtemp = rgba->p[G] = glowC.p[G] * exp(-minD / (pR * pR));
        float btemp = rgba->p[B] = glowC.p[B] * exp(-minD / (pR * pR));
        Vec4FixUpper(rgba, 1.0);
        Vec4FixLower(rgba, 0.0);
        rgba->p[R] += 1.0 - max_(gtemp, btemp);
        rgba->p[G] += 1.0 - max_(rtemp, btemp);
        rgba->p[B] += 1.0 - max_(rtemp, gtemp);
        Vec4FixUpper(rgba, 1.0);
        Vec4FixLower(rgba, 0.0);
    }
}
#else
#endif

