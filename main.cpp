#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include "stb_image_write.h"
#include "functions.hpp"
#include "funcs.tpp"
#include "vector.hpp"
#include "line.hpp"

int main()
{
    int w = 1920;
    int h = 1080;
    double r_ = (double)w / (double)h;
    double R0 = 0.4;
    RGBA32 *pixels = new RGBA32[w * h];

    size_t n = 100;
    double htheta = 2 * pi / n;
    LineSegment2D *curve = new LineSegment2D[n + 1];
    LineSegment2D *curve2 = new LineSegment2D[n + 1];

    LineSegment2D lineX, lineY, lineXY;
    InitLine2D(&lineX, 0.0, w, h / 2.0, h / 2.0);
    InitLine2D(&lineY, w / 2.0, w / 2.0, 0.0, h);
    InitLine2D(&lineXY, 0.0, w, h, 0.0);

    R0 = h / 3;
    double cx = (double)w / 2.0;
    double cy = (double)h / 2.0;

    htheta = (double)w / (double)n;
    for (size_t i = 0; i <= n; i++)
    {
        double x = i * htheta;
        double xp = (i + 1) * htheta;
        InitLine2D(&curve[i], x,
                   xp,
                   (double)h / 2.0 - (double)h / 2.0 * sin(2.0 * pi / (double)(w) * x),
                   (double)h / 2.0 - (double)h / 2.0 * sin(2.0 * pi / (double)(w) * xp));

        InitLine2D(&curve2[i], x,
                   xp,
                   x * x,
                   xp * xp);
    }

    for (int y = 0; y < h; y++)
    {
        double V = (double)y / (double)h;
        for (int x = 0; x < w; x++)
        {
            double U = (double)x / (double)(w);
            RGBA rgba = {{1.0, 1.0, 1.0, 1.0}};
            RGBA rgba2 = {{0.0, 0.0, 0.0, 1.0}};
            RGBA rgba3 = {{0.0, 0.0, 0.0, 1.0}};
            double minD = DistanceTwo2D(curve[0], Vec2From(x, y));
            double maxD = DistanceTwo2D(curve[0], Vec2From(x, y));

            for (size_t i = 0; i <= n; i++)
            {
                double d = DistanceTwo2D(curve[i], Vec2From(x, y));
                if (d < minD)
                {
                    minD = d;
                }
                if (d > maxD)
                {
                    maxD = d;
                }
            }

            if (minD < 6 * 6)
            {
                rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
            }
            else
            {
                rgba.p[B] = exp(-minD / 1000);
                if (rgba.p[B] > 1.0)
                {
                    rgba.p[B] = 1.0;
                }
                rgba.p[R] = rgba.p[G] = 1.0 - rgba.p[B];

                rgba.p[B] = exp(-minD / 1000) + exp(minD / 1000);
                if (rgba.p[B] > 1.0)
                {
                    rgba.p[B] = 1.0;
                }
            }

            if (PaintLine2D(lineX, Vec2From(x, y), 5))
            {
                rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
            }

            if (PaintLine2D(lineY, Vec2From(x, y), 5))
            {
                rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
            }

            if (PaintLine2D(lineXY, Vec2From(x, y), 5))
            {
                rgba.p[R] = rgba.p[G] = rgba.p[B] = 0.0;
            }
            else
            {
                double minD = DistanceTwo2D(lineXY, Vec2From(x, y));
                rgba2.p[R] = exp(-minD / 1000);
                if (rgba2.p[R] > 1.0)
                {
                    rgba2.p[R] = 1.0;
                }
                rgba2.p[B] = rgba2.p[G] = 1.0 - rgba2.p[R];

                rgba2.p[R] = exp(-minD / 1000) + exp(minD / 1000);
                if (rgba2.p[R] > 1.0)
                {
                    rgba2.p[R] = 1.0;
                }
            }
            rgba = Vec4Pow(rgba, 1.0 / 2.2);
            rgba2 = Vec4Pow(rgba2, 1.0 / 2.2);
            Vec4 s = Vec4Mult(rgba, rgba2);
            pixels[y * w + x] = ToRGBA32(s);
        }
    }

    stbi_write_png("out.png", w, h, 4, pixels, w * sizeof(RGBA32));
#if 0
    {
        char pal[] = "VAI SE";
        uint64_t l;
        printf("%s\n", pal);
        l = *(uint64_t*)pal;
        printf("%u\n", l);
        l++; l++; l++; l++; l++;
        memcpy(pal, &l, 7);
        printf("%s\n", pal);
    }
#endif
    return 0;
}
