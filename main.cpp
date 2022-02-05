#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include "functions.hpp"
#include <cstring>
#include "stb_image_write.h"
#include "vector.hpp"
#include "line.hpp"

int main()
{
    int w = 1920 * 2;
    int h = 1080 * 2;
    double r_ = (double)w / (double)h;
    double R0 = 0.4;
    RGBA32 *pixels = new RGBA32[w * h];

    size_t n = 100;
    double htheta = 2 * pi / n;
    LineSegment2D *circle = new LineSegment2D[n + 1];

    LineSegment2D lineX, lineY;
    InitLine2D(&lineX, 0.0, w, h / 2.0, h / 2.0);
    InitLine2D(&lineY, w / 2.0, w / 2.0, 0.0, h);

    R0 = h / 3;
    double cx = (double)w / 2.0;
    double cy = (double)h / 2.0;

    for (size_t i = 0; i <= n; i++)
    {
        InitLine2D(&circle[i], (R0 * cos((double)i * htheta) + cx), 
                               (R0 * cos((double)(i + 1) * htheta) + cx), 
                               R0 * sin((double)i * htheta) + cy,
                               R0 * sin((double)(i + 1) * htheta) + cy);
    }
    htheta = (double)w / (double)n;
    for (size_t i = 0; i <= n; i++)
    {
        InitLine2D(&circle[i], (double)i * htheta, 
                               (double)(i + 1) * htheta, 
                               (double)h / 2.0 - (double)h / 2.0 * sin(2.0 * pi / (double)w * (double)i * htheta),
                               (double)h / 2.0 - (double)h / 2.0 * sin(2.0 * pi / (double)w * (double)(i + 1) * htheta));
    }

    for (int y = 0; y < h; y++)
    {
        double V = (double)y / (double)h;
        for (int x = 0; x < w; x++)
        {
            double U = (double)x / (double)(w);
            R r = 255;
            G g = 255;
            B b = 255;
            A a = 255;

            R r_ = r;
            G g_ = g;
            B b_ = b;
            A a_ = a;
            double minD = DistanceTwo2D(circle[0], Vec2From(x, y));
            double maxD = DistanceTwo2D(circle[0], Vec2From(x, y));

            for (size_t i = 0; i <= n; i++)
            {
                double d = DistanceTwo2D(circle[i], Vec2From(x, y));
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
                r = g = b = 0;
            }
            else
            {
                // r = (R)(exp(-minD / 5000) * 255) & 255;
                // b = (B)(exp(-minD / 100000) * 255) & 255;
                b = (B)(exp(-minD / 5000) * 255) & 255;
                g = b;
                r = ~max(b, g);
                b = b | r;
                g = g | r;
            }

            if (PaintLine2D(lineX, Vec2From(x, y), 5))
            {
                r = b = g = 0;
            }

            if (PaintLine2D(lineY, Vec2From(x, y), 5))
            {
                r = b = g = 0;
            }

            pixels[y * w + x] = ToRGBA32(r, g, b, a);
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
