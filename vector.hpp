#ifndef __VEC
#define __VEC
typedef struct
{
    double p[2];
} Vec2;

Vec2 Vec2FromScalar(double x)
{
    return (Vec2){x, x};
}

Vec2 Vec2From(double x, double y)
{
    return (Vec2){x, y};
}

Vec2 Vec2Sum(Vec2 v1, Vec2 v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] += v2.p[i];
    }
    return v1;
}

Vec2 Vec2Sub(Vec2 v1, Vec2 v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] -= v2.p[i];
    }
    return v1;
}

Vec2 Vec2Mult(Vec2 v1, Vec2 v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] *= v2.p[i];
    }
    return v1;
}

Vec2 Vec2MultScalar(Vec2 v, double s)
{
    for (int i = 0; i < 2; i++)
    {
        v.p[i] *= s;
    }
    return v;
}

double Vec2Dot(Vec2 v1, Vec2 v2)
{
    double s = 0.0;
    for (int i = 0; i < 2; i++)
    {
        s += v1.p[i] * v2.p[i];
    }
    return s;
}

double Vec2Length2(const Vec2 &v)
{
    return Vec2Dot(v, v);
}

double Vec2Length(const Vec2 &v)
{
    return sqrt(Vec2Dot(v, v));
}

typedef struct
{
    double p[3];
} Vec3;

Vec3 Vec3FromScalar(double x)
{
    return (Vec3){x, x};
}

Vec3 Vec3From(double x, double y)
{
    return (Vec3){x, y};
}

Vec3 Vec3Sum(Vec3 v1, Vec3 v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] += v3.p[i];
    }
    return v1;
}

Vec3 Vec3Sub(Vec3 v1, Vec3 v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] -= v3.p[i];
    }
    return v1;
}

Vec3 Vec3Mult(Vec3 v1, Vec3 v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] *= v3.p[i];
    }
    return v1;
}

Vec3 Vec3MultScalar(Vec3 v, double s)
{
    for (int i = 0; i < 3; i++)
    {
        v.p[i] *= s;
    }
    return v;
}

double Vec3Dot(Vec3 v1, Vec3 v3)
{
    double s = 0.0;
    for (int i = 0; i < 3; i++)
    {
        s += v1.p[i] * v3.p[i];
    }
    return s;
}

double Vec3Length3(const Vec3 &v)
{
    return Vec3Dot(v, v);
}

double Vec3Length(const Vec3 &v)
{
    return sqrt(Vec3Dot(v, v));
}



#endif