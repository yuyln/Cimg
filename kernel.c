#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#include <functions.hpp>
#include <line.hpp>
#include <vector.hpp>
#include <curve.hpp>

kernel void ShowLGPU(global RGBA *rgba, global LineSegment2D *lines,
                     const int w, const int h, const int nlines, const double lw)
{
    int I = get_global_id(0);
    int x = (I % w) - w / 2;
    int y = (I - x) / w - h / 2;
    double dummy, dummy2;
    Show(lines, nlines, lw, x, y, &dummy, &dummy2, &rgba[I]);
}

kernel void ShowCGPU(global RGBA *rgba, global LineSegment2D *lines, const Vec4 col, 
                     const int w, const int h, const int nlines, const double lw)
{
    int I = get_global_id(0);
    int x = (I % w) - w / 2;
    int y = (I - x) / w - h / 2;
    double dummy, dummy2;
    ShowC(lines, nlines, lw, x, y, &dummy, &dummy2, &rgba[I], col);
}

kernel void ShowGGPU(global RGBA *rgba, global LineSegment2D *lines, const Vec4 Gcol,
                     const int w, const int h, const int nlines, const double lw, const double pR)
{
    int I = get_global_id(0);
    int x = (I % w) - w / 2;
    int y = (I - x) / w - h / 2;
    double dummy, dummy2;
    ShowG(lines, nlines, lw, x, y, &dummy, &dummy2, &rgba[I], pR, Gcol);
}

kernel void Collapse(global RGBA *rgba, global RGBA32 *pixels, const int T, const int nrgbas)
{
    int j = get_global_id(0);
    RGBA s = {{1.0, 1.0, 1.0, 1.0}};

    for (int i = 0; i < nrgbas; i++)
    {
        s = Vec4Mult(s, rgba[i * T + j]);
    }
    
    s = Vec4PowS(s, 1.0 / 2.2);
    pixels[j] = (~ToRGBA32V4(s)) | 0xFF000000;
}