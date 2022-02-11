#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <stb_image_write.h>
#include <functions.hpp>
#include <funcs.tpp>
#include <vector.hpp>
#include <line.hpp>
#include <curve.hpp>
#include <forms.hpp>


int main()
{
    int w = 1920;
    int h = 1080;
    double r_ = (double)w / (double)h;
    RGBA32 *pixels = new RGBA32[w * h];

    size_t n = 100;
    double htheta = 2 * pi / n;
    Curve seno, circulo, triangulo, quadrado, ell, seno2;
    Curve xaxis, yaxis, line1, line2;

    InitCurve(&seno, n); InitCurve(&circulo, n); InitCurve(&triangulo, 3); InitCurve(&quadrado, 4);
    InitCurve(&xaxis, 1); InitCurve(&yaxis, 1); InitCurve(&line1, 1); InitCurve(&line2, 1);
    InitCurve(&ell, n); InitCurve(&seno2, n);

    InitLine2D(&line1.lines[0], -w / 2, w / 2, -h / 2, h / 2);
    InitLine2D(&line2.lines[0], -w / 2, w / 2, h / 2, -h / 2);
    InitLine2D(&xaxis.lines[0], -w / 2, w / 2, 0, 0);
    InitLine2D(&yaxis.lines[0], 0, 0, -h / 2, h / 2);

    Sin(seno, h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);
    Sin(seno2, -h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);
    Ellipse(circulo, Vec2From(-w / 4, -h / 4), Vec2FromScalar(100));
    Ellipse(ell, Vec2From(w / 4, h / 4), Vec2From(100, 200));
    Triangule(triangulo, Vec2From(w / 4, 0), Vec2From(w / 5.5, -h / 3.3), Vec2From(w / 3.3, -h / 6.0));
    Square(quadrado, Vec2From(-w / 3, h / 5), Vec2From(-w / 5, h / 5), Vec2From(-w / 5, h / 3), Vec2From(-w / 3, h / 3));

    RGBA rgba = {{1.0, 1.0, 1.0, 1.0}};
    RGBA rgba2 = {{1.0, 1.0, 1.0, 1.0}};
    RGBA rgba3 = {{1.0, 1.0, 1.0, 1.0}};
    RGBA rgba4 = {{1.0, 1.0, 1.0, 1.0}};
    RGBA rgba5 = {{1.0, 1.0, 1.0, 1.0}};
    for (int y = -h / 2; y < h / 2; y++)
    {
        int y_ = y + h / 2;
        for (int x = -w / 2; x < w / 2; x++)
        {
            rgba = {{1.0, 1.0, 1.0, 1.0}};
            rgba2 = {{1.0, 1.0, 1.0, 1.0}};
            rgba3 = {{1.0, 1.0, 1.0, 1.0}};
            rgba4 = {{1.0, 1.0, 1.0, 1.0}};
            rgba5 = {{1.0, 1.0, 1.0, 1.0}};
            int x_ = x + w / 2.0;
            double dummy, dummy2;
            Show(xaxis, 6, x, y, &dummy, &dummy2, rgba);
            Show(yaxis, 6, x, y, &dummy, &dummy2, rgba);
            Show(triangulo, 6, x, y, &dummy, &dummy2, rgba);
            Show(quadrado, 6, x, y, &dummy, &dummy2, rgba);
            ShowG(seno, 6, x, y, &dummy, &dummy2, rgba2, 100, Vec4From(0, 1, 0, 0));
            ShowG(seno2, 6, x, y, &dummy, &dummy2, rgba3, 100, Vec4From(1, 1, 0, 0));
            ShowG(circulo, 6, x, y, &dummy, &dummy2, rgba4, 50, Vec4From(1.0, 0.0, 1.0, 0.0));
            ShowG(ell, 6, x, y, &dummy, &dummy2, rgba5, 50, Vec4From(0.0, 0.0, 1.0, 0.0));
            RGBA s = Vec4Mult(rgba, rgba2);
            s = Vec4Mult(s, rgba3);
            s = Vec4Mult(s, rgba4);
            s = Vec4Mult(s, rgba5);
            s = Vec4Pow(s, 1.0 / 2.2);
            pixels[(h - 1 - y_) * w + x_] = (~ToRGBA32(s)) | 0xFF000000;
        }
    }
    stbi_write_png("out.png", w, h, 4, pixels, w * sizeof(RGBA32));
    return 0;
}

