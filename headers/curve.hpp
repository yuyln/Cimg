#ifndef __CURVE
#define __CURVE
#include "line.hpp"
#include "vector.hpp"
#include "functions.hpp"
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

void Show(const Curve &c, const double &lw, const double &x, const double &y, double *minD_, double *maxD_, RGBA &rgba)
{
    double minD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    double maxD = DistanceTwo2D(c.lines[0], Vec2From(x, y));

    for (size_t i = 1; i < c.nLines; i++)
    {
        double d = DistanceTwo2D(c.lines[i], Vec2From(x, y));
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
        rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
    }
}

void ShowC(const Curve &c, const double &lw, const double &x, const double &y, double *minD_, double *maxD_, RGBA &rgba, const Vec4 &color)
{
    double minD = DistanceTwo2D(c.lines[0], Vec2From(x, y));
    double maxD = DistanceTwo2D(c.lines[0], Vec2From(x, y));

    for (size_t i = 1; i < c.nLines; i++)
    {
        double d = DistanceTwo2D(c.lines[i], Vec2From(x, y));
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
        rgba.p[R] = color.p[R];
        rgba.p[G] = color.p[G];
        rgba.p[B] = color.p[B];
    }
}

void ShowG(const Curve &c, const double &lw, const double &x, const double &y, double *minD_, double *maxD_, RGBA &rgba, 
           const double &pR, const Vec4 &glowC)
{
    double minD, maxD;
    Show(c, lw, x, y, &minD, &maxD, rgba);
    *minD_ = minD;
    *maxD_ = maxD;

    if (minD < lw * lw)
    {
        rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
    }
    else
    {
        double rtemp = rgba.p[R] = glowC.p[R] * exp(-minD / (pR * pR));
        double gtemp = rgba.p[G] = glowC.p[G] * exp(-minD / (pR * pR));
        double btemp = rgba.p[B] = glowC.p[B] * exp(-minD / (pR * pR));
        Vec4FixUpper(rgba, 1.0);
        Vec4FixLower(rgba, 0.0);
        rgba.p[R] += 1.0 - max_(gtemp, btemp);
        rgba.p[G] += 1.0 - max_(rtemp, btemp);
        rgba.p[B] += 1.0 - max_(rtemp, gtemp);
        Vec4FixUpper(rgba, 1.0);
        Vec4FixLower(rgba, 0.0);
    }
}

#endif

