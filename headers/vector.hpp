#ifndef __VEC
#define __VEC

typedef struct
{
    float p[2];
} Vec2;

Vec2 Vec2FromScalar(float x)
{
    return (Vec2){{x, x}};
}

Vec2 Vec2From(float x, float y)
{
    return (Vec2){{x, y}};
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

Vec2 Vec2MultScalar(Vec2 v, float s)
{
    for (int i = 0; i < 2; i++)
    {
        v.p[i] *= s;
    }
    return v;
}

float Vec2Dot(Vec2 v1, Vec2 v2)
{
    float s = 0.0;
    for (int i = 0; i < 2; i++)
    {
        s += v1.p[i] * v2.p[i];
    }
    return s;
}

inline float Vec2Length2(const Vec2 v)
{
    return Vec2Dot(v, v);
}

inline float Vec2Length(const Vec2 v)
{
    return sqrt(Vec2Dot(v, v));
}

inline Vec2 Vec2Pow(Vec2 v1, Vec2 v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] = pow(v1.p[i], v2.p[i]);
    }
    return v1;
}

inline Vec2 Vec2PowS(Vec2 v1, float v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] = pow(v1.p[i], v2);
    }
    return v1;
}

inline Vec2 Vec2Max(Vec2 v1, Vec2 v2)
{
    for (int i = 0; i < 2; i++)
    {
        v1.p[i] = v1.p[i] * (v1.p[i] >= v2.p[i]) + v2.p[i] * (v2.p[i] > v1.p[i]);
    }
    return v1;
}
#ifndef OPENCLCOMP
inline void Vec2FixUpper(Vec2 *v, float U)
#else
inline void Vec2FixUpper(global Vec2 *v, float U)
#endif
{
    for (int i = 0; i < 2; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] <= U) + U * (v->p[i] > U);
    }
}

#ifndef OPENCLCOMP
inline void Vec2FixLower(Vec2 *v, float U)
#else
inline void Vec2FixLower(global Vec2 *v, float U)
#endif
{
    for (int i = 0; i < 2; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] >= U) + U * (v->p[i] < U);
    }
}

typedef struct
{
    float p[3];
} Vec3;

Vec3 Vec3FromScalar(float x)
{
    return (Vec3){{x, x, x}};
}

Vec3 Vec3From(float x, float y, float z)
{
    return (Vec3){{x, y, z}};
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

Vec3 Vec3MultScalar(Vec3 v, float s)
{
    for (int i = 0; i < 3; i++)
    {
        v.p[i] *= s;
    }
    return v;
}

float Vec3Dot(Vec3 v1, Vec3 v3)
{
    float s = 0.0;
    for (int i = 0; i < 3; i++)
    {
        s += v1.p[i] * v3.p[i];
    }
    return s;
}

inline float Vec3Length2(const Vec3 v)
{
    return Vec3Dot(v, v);
}

inline float Vec3Length(const Vec3 v)
{
    return sqrt(Vec3Dot(v, v));
}

inline Vec3 Vec3Pow(Vec3 v1, Vec3 v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] = pow(v1.p[i], v3.p[i]);
    }
    return v1;
}

inline Vec3 Vec3PowS(Vec3 v1, float v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] = pow(v1.p[i], v3);
    }
    return v1;
}

inline Vec3 Vec3Max(Vec3 v1, Vec3 v3)
{
    for (int i = 0; i < 3; i++)
    {
        v1.p[i] = v1.p[i] * (v1.p[i] >= v3.p[i]) + v3.p[i] * (v3.p[i] > v1.p[i]);
    }
    return v1;
}

#ifndef OPENCLCOMP
inline void Vec3FixUpper(Vec3 *v, float U)
#else
inline void Vec3FixUpper(global Vec3 *v, float U)
#endif
{
    for (int i = 0; i < 3; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] <= U) + U * (v->p[i] > U);
    }
}

#ifndef OPENCLCOMP
inline void Vec3FixLower(Vec3 *v, float U)
#else
inline void Vec3FixLower(global Vec3 *v, float U)
#endif
{
    for (int i = 0; i < 3; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] >= U) + U * (v->p[i] < U);
    }
}

typedef struct
{
    float p[4];
} Vec4;

Vec4 Vec4FromScalar(float x)
{
    return (Vec4){{x, x, x, x}};
}

Vec4 Vec4From(float x, float y, float z, float w)
{
    return (Vec4){{x, y, z, w}};
}

Vec4 Vec4Sum(Vec4 v1, Vec4 v4)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] += v4.p[i];
    }
    return v1;
}

Vec4 Vec4Sub(Vec4 v1, Vec4 v4)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] -= v4.p[i];
    }
    return v1;
}

Vec4 Vec4Mult(Vec4 v1, Vec4 v4)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] *= v4.p[i];
    }
    return v1;
}

Vec4 Vec4MultScalar(Vec4 v, float s)
{
    for (int i = 0; i < 4; i++)
    {
        v.p[i] *= s;
    }
    return v;
}

float Vec4Dot(Vec4 v1, Vec4 v4)
{
    float s = 0.0;
    for (int i = 0; i < 4; i++)
    {
        s += v1.p[i] * v4.p[i];
    }
    return s;
}

inline float Vec4Length2(const Vec4 v)
{
    return Vec4Dot(v, v);
}

inline float Vec4Length(const Vec4 v)
{
    return sqrt(Vec4Dot(v, v));
}

inline Vec4 Vec4Pow(Vec4 v1, Vec4 v4)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] = pow(v1.p[i], v4.p[i]);
    }
    return v1;
}

inline Vec4 Vec4PowS(Vec4 v1, float v4)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] = pow(v1.p[i], v4);
    }
    return v1;
}

inline Vec4 Vec4Max(Vec4 v1, Vec4 v3)
{
    for (int i = 0; i < 4; i++)
    {
        v1.p[i] = v1.p[i] * (v1.p[i] >= v3.p[i]) + v3.p[i] * (v3.p[i] > v1.p[i]);
    }
    return v1;
}

#ifndef OPENCLCOMP
inline void Vec4FixUpper(Vec4 *v, float U)
#else
inline void Vec4FixUpper(global Vec4 *v, float U)
#endif
{
    for (int i = 0; i < 4; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] <= U) + U * (v->p[i] > U);
    }
}

#ifndef OPENCLCOMP
inline void Vec4FixLower(Vec4 *v, float U)
#else
inline void Vec4FixLower(global Vec4 *v, float U)
#endif
{
    for (int i = 0; i < 4; i++)
    {
        v->p[i] = v->p[i] * (v->p[i] >= U) + U * (v->p[i] < U);
    }
}

#endif