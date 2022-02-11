#ifndef __LINE
#define __LINE
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector.hpp>

typedef struct
{
    double kx, ky, cx, cy;
    double xmax, xmin, ymax, ymin;
} LineSegment2D;

void InitLine2D(LineSegment2D *line)
{
    line->kx = line->ky = 1.0;
    line->cx = line->cy = 0.0;
}

void InitLine2D(LineSegment2D *line, double xmin, double xmax, double ymin, double ymax)
{
    line->cx = xmin;
    line->cy = ymin;
    line->kx = xmax - xmin;
    line->ky = ymax - ymin;
    line->xmax = xmax;
    line->xmin = xmin;
    line->ymax = ymax;
    line->ymin = ymin;
}

Vec2 Point2D(const LineSegment2D &line, double t)
{
    return (Vec2){(t >= 1.0) * line.xmax + (t <= 0) * line.xmin + (t > 0.0 && t < 1.0) * (line.kx * t + line.cx),
                  (t >= 1.0) * line.ymax + (t <= 0) * line.ymin + (t > 0.0 && t < 1.0) * (line.ky * t + line.cy)};
}

Vec2 VecDistance2D(const LineSegment2D &line, Vec2 X)
{
    double t = (line.ky * X.p[1] + line.kx * X.p[0] - line.cy * line.ky - line.cx * line.kx) /
               (line.kx * line.kx + line.ky * line.ky);
    Vec2 XL = Point2D(line, t);
    Vec2 X_ = Vec2Sub(X, XL);
    return X_;
}

inline double Distance2D(const LineSegment2D &line, Vec2 X)
{
    return Vec2Length(VecDistance2D(line, X));
}

inline double DistanceTwo2D(const LineSegment2D &line, Vec2 X)
{
    return Vec2Length2(VecDistance2D(line, X));
}

inline bool PaintLine2D(const LineSegment2D &line, Vec2 X, double lw)
{
    return DistanceTwo2D(line, X) <= lw * lw;
}


#endif
