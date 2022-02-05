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
    int w = 1920;
    int h = 1080;
    double r_ = (double)w / (double)h;
    double R0 = 0.4;
    RGBA32 *pixels = new RGBA32[w * h];

    size_t n = 100;
    double htheta = 2 * pi / n;
    LineSegment2D *circle = new LineSegment2D[n + 1];

    LineSegment2D line;

    for (size_t i = 0; i <= n; i++)
    {
        InitLine2D(&circle[i], (R0 * cos((double)i * htheta) / r_ + 0.5), 
                               (R0 * cos((double)(i + 1) * htheta) / r_ + 0.5), 
                               R0 * sin((double)i * htheta) + 0.5,
                               R0 * sin((double)(i + 1) * htheta) + 0.5);
    }

    InitLine2D(&line, 0.0, 1.0, 0.0, 1.0);

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
            double minD = DistanceTwo2D(circle[0], Vec2From(U, V));
            double maxD = DistanceTwo2D(circle[0], Vec2From(U, V));

            for (size_t i = 0; i <= n; i++)
            {
                double d = DistanceTwo2D(circle[i], Vec2From(U, V));
                if (d < minD)
                {
                    minD = d;
                }
                if (d > maxD)
                {
                    maxD = d;
                }
            }
            /*{
                double d = DistanceTwo2D(line, Vec2From(U, V));
                if (d < 0.02 * 0.02)
                {
                    r = b = g = 0;
                }
                else
                {
                    r = exp(-d / 0.01) * 255;
                    b = exp(-d / 0.01) * 255;
                    g = ~r;
                    r = r | 255;
                    b = b | 255;
                    g = g & 255;
                }
                pixels[y * w + x] = ToRGBA32(r, g, b, a);
            }*/

            if (minD < (0.02 * 0.02))
            {
                r = g = b = 0;
            }
            else
            {
                r = exp(-minD / 0.01) * 255;
                b = exp(-minD / 0.01) * 255;
                g = ~r;
                r = r | 255;
                b = b | 255;
                g = g & 255;
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
