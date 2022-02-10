#ifndef __FORMS
#define __FORMS
#include "functions.hpp"
#include "line.hpp"
#include "curve.hpp"

void Square(Curve &C, const Vec2 &p1, const Vec2 &p2, Vec2 const &p3, Vec2 const &p4)
{
    InitLine2D(&C.lines[0], p1.p[0], p2.p[0], p1.p[1], p2.p[1]);
    InitLine2D(&C.lines[1], p2.p[0], p3.p[0], p2.p[1], p3.p[1]);
    InitLine2D(&C.lines[2], p3.p[0], p4.p[0], p3.p[1], p4.p[1]);
    InitLine2D(&C.lines[3], p4.p[0], p1.p[0], p4.p[1], p1.p[1]);
}

void Triangule(Curve &C, const Vec2 &p1, const Vec2 &p2, Vec2 const &p3)
{
    InitLine2D(&C.lines[0], p1.p[0], p2.p[0], p1.p[1], p2.p[1]);
    InitLine2D(&C.lines[1], p2.p[0], p3.p[0], p2.p[1], p3.p[1]);
    InitLine2D(&C.lines[2], p3.p[0], p1.p[0], p3.p[1], p1.p[1]);
}

void Ellipse(Curve &C, const Vec2 &center, const Vec2 &r)
{
    double htheta = 2.0 * pi / C.nLines;
    double R0 = 100.0;
    for (int i = 0; i < C.nLines; i++)
    {
        double t = i * htheta;
        double tp = (i + 1) * htheta;
        InitLine2D(&C.lines[i], r.p[0] * cos(t) + center.p[0],
                                      r.p[0] * cos(tp) + center.p[0],
                                      r.p[1] * sin(t) + center.p[1],
                                      r.p[1] * sin(tp) + center.p[1]);
    }
}

void Sin(Curve &C, double a, double w, double f, double x0, double xf)
{
    double htheta = (xf - x0) / (double)C.nLines;
    for (int i = 0; i < C.nLines; i++)
    {
        double x = i * htheta + x0;
        double xp = (i + 1) * htheta + x0;
        InitLine2D(&C.lines[i], x,
                   xp,
                   a * sin(2.0 * pi * w * x + f),
                   a * sin(2.0 * pi * w * xp + f));
    }
}

void Cos(Curve &C, double a, double w, double f, double x0, double xf)
{
    Sin(C, a, w, pi / 2.0, x0, xf);
}
#endif