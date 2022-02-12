#ifndef __FORMS
#define __FORMS
#include <functions.hpp>
#include <line.hpp>
#include <curve.hpp>

void Square(Curve &C, const Vec2 &p1, const Vec2 &p2, Vec2 const &p3, Vec2 const &p4)
{
    InitLine2D(&C.lines[0], p1.p[0], p2.p[0], p1.p[1], p2.p[1]);
    InitLine2D(&C.lines[1], p2.p[0], p3.p[0], p2.p[1], p3.p[1]);
    InitLine2D(&C.lines[2], p3.p[0], p4.p[0], p3.p[1], p4.p[1]);
    InitLine2D(&C.lines[3], p4.p[0], p1.p[0], p4.p[1], p1.p[1]);
}

void SquareCenter(Curve &C, const Vec2 &cen, float w, float h)
{
    InitLine2D(&C.lines[0], cen.p[0] - w / 2, cen.p[0] + w / 2, cen.p[1] - h / 2, cen.p[1] - h / 2);
    InitLine2D(&C.lines[1], cen.p[0] + w / 2, cen.p[0] + w / 2, cen.p[1] - h / 2, cen.p[1] + h / 2);
    InitLine2D(&C.lines[2], cen.p[0] + w / 2, cen.p[0] - w / 2, cen.p[1] + h / 2, cen.p[1] + h / 2);
    InitLine2D(&C.lines[3], cen.p[0] - w / 2, cen.p[0] - w / 2, cen.p[1] + h / 2, cen.p[1] - h / 2);
}

void Triangule(Curve &C, const Vec2 &p1, const Vec2 &p2, Vec2 const &p3)
{
    InitLine2D(&C.lines[0], p1.p[0], p2.p[0], p1.p[1], p2.p[1]);
    InitLine2D(&C.lines[1], p2.p[0], p3.p[0], p2.p[1], p3.p[1]);
    InitLine2D(&C.lines[2], p3.p[0], p1.p[0], p3.p[1], p1.p[1]);
}

void Ellipse(Curve &C, const Vec2 &center, const Vec2 &r)
{
    float htheta = 2.0 * pi / C.nLines;
    float R0 = 100.0;
    for (size_t i = 0; i < C.nLines; i++)
    {
        float t = i * htheta;
        float tp = (i + 1) * htheta;
        InitLine2D(&C.lines[i], r.p[0] * cos(t) + center.p[0],
                                      r.p[0] * cos(tp) + center.p[0],
                                      r.p[1] * sin(t) + center.p[1],
                                      r.p[1] * sin(tp) + center.p[1]);
    }
}

void Sin(Curve &C, float a, float w, float f, float x0, float xf)
{
    float htheta = (xf - x0) / (float)C.nLines;
    for (size_t i = 0; i < C.nLines; i++)
    {
        float x = i * htheta + x0;
        float xp = (i + 1) * htheta + x0;
        InitLine2D(&C.lines[i], x,
                   xp,
                   a * sin(2.0 * pi * w * x + f),
                   a * sin(2.0 * pi * w * xp + f));
    }
}

void Cos(Curve &C, float a, float w, float f, float x0, float xf)
{
    Sin(C, a, w, pi / 2.0, x0, xf);
}
#endif