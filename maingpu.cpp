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
#define HEADER_IMPL
#include <OpenCLWrapper.h>

//TODO: change how everything its included on openclkernel
int main()
{
    int i_ = 1;
    int iD = 0;
    int nplat, ndev;
    cl_platform_id *plats;
    cl_device_id *devices;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel *ks;
    Kernel *kernels;
    size_t *globalwork;
    size_t *localwork;
    const char *kernelnames[4] = {"ShowLGPU", "ShowCGPU", "ShowGGPU", "Collapse"};

    int w = 1920;
    int h = 1080;
    int T = w * h;
    RGBA32 *pixels = new RGBA32[T];

    char *kernel;
    ReadFile("kernel.c", &kernel);

    InitPlatforms(&plats, &nplat);
    InitDevice(&devices, plats[i_], i_, &ndev);
    InitContext(&context, &devices[iD]);
    InitQueue(&queue, &context, &devices[iD]);

    InitProgram(&program, &context, 1, (const char**)&kernel);
    BuildProgram(&program, 1, &devices[iD], "-I./headers -DOPENCLCOMP");

    InitKernelsStructGround(&kernels, &ks, &program, kernelnames, 4);

    InitGlobalWorkItems(1, &T, &globalwork);
    InitGroupWorkItemsGCD(1, &T, &localwork, &devices[iD]);

    int n = 8;
    Curve *curves = new Curve[n];
    cl_mem *curvesb = new cl_mem[n];

    InitCurve(&curves[0], 100); 
    Sin(curves[0], h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);

    InitCurve(&curves[1], 100); 
    Sin(curves[1], -h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);

    InitCurve(&curves[2], 3); 
    Triangule(curves[2], Vec2From(w / 4, 0), Vec2From(w / 5.5, -h / 3.3), Vec2From(w / 3.3, -h / 6.0));

    InitCurve(&curves[3], 4);
    SquareCenter(curves[3], Vec2From(-w / 4, h / 4), 160, 160);

    InitCurve(&curves[4], 5);
    Ellipse(curves[4], Vec2From(-w / 4, -h / 4), Vec2FromScalar(100));

    InitCurve(&curves[5], 50);
    Ellipse(curves[5], Vec2From(w / 4, h / 4), Vec2From(100, 200));

    InitCurve(&curves[6], 1);
    InitLine2D(curves[6].lines, -w / 2, w / 2, 0.0, 0.0);

    InitCurve(&curves[7], 1);
    InitLine2D(curves[7].lines, 0.0, 0.0, -h / 2, h / 2);

    for (int i = 0; i < n; i++)
    {
        CreateBuffer(&curvesb[i], curves[i].lines, sizeof(LineSegment2D) * curves[i].nLines, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
        WriteBuffer(&curvesb[i], curves[i].lines, sizeof(LineSegment2D) * curves[i].nLines, queue);
    }

    RGBA *rgbas = new RGBA[T * n];
    cl_mem *rgbasb = new cl_mem[n];

    for (int i = 0; i < n; i++)
    {
        CreateBuffer(&rgbasb[i], &rgbas[i * T], sizeof(RGBA) * T, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
        for (int j = 0; j < T; j++)
        {
            rgbas[i * T + j] = {{1.0, 1.0, 1.0, 1.0}};
        }
        WriteBuffer(&rgbasb[i], &rgbas[i * T], sizeof(RGBA) * T, queue);
    }

    const Vec4 cols[6] = {{{0.0, 103.0, 255.0, 0.0}}, 
                        {{255.0, 0x67, 0.0, 0.0}},
                        {{255.0, 0.0, 0.0, 0.0}},
                        {{255.0, 0.0, 255.0}},
                        {{255.0, 255.0, 0.0}},
                        {{0.0, 0.0, 255.0, 0.0}}};
    double pR = 50.0;
    double lw = 3.5;
    for (int i = 0; i < n - 2; i++)
    {
        Vec4 col = Vec4MultScalar(cols[i], 1.0 / 255.0);
        SetKernelArg(&kernels[2], &rgbasb[i], sizeof(cl_mem), 0);
        SetKernelArg(&kernels[2], &curvesb[i], sizeof(cl_mem), 1);
        SetKernelArg(&kernels[2], &col, sizeof(Vec4), 2);
        SetKernelArg(&kernels[2], &w, sizeof(int), 3);
        SetKernelArg(&kernels[2], &h, sizeof(int), 4);
        SetKernelArg(&kernels[2], &(curves[i].nLines), sizeof(int), 5);
        SetKernelArg(&kernels[2], &lw, sizeof(double), 6);
        SetKernelArg(&kernels[2], &pR, sizeof(double), 7);    

        EnqueueND(&queue, &kernels[2], 1, NULL, globalwork, localwork);
    }


    for (int i = 6; i < n; i++)
    {
        SetKernelArg(&kernels[0], &rgbasb[i], sizeof(cl_mem), 0);
        SetKernelArg(&kernels[0], &curvesb[i], sizeof(cl_mem), 1);
        SetKernelArg(&kernels[0], &w, sizeof(int), 2);
        SetKernelArg(&kernels[0], &h, sizeof(int), 3);
        SetKernelArg(&kernels[0], &(curves[i].nLines), sizeof(int), 4);
        SetKernelArg(&kernels[0], &lw, sizeof(double), 5);

        EnqueueND(&queue, &kernels[0], 1, NULL, globalwork, localwork);
    }

    Finish(&queue);

    for (int i = 0; i < n; i++)
    {
        ReadBuffer(&rgbasb[i], &rgbas[i * T], sizeof(RGBA) * T, queue);
    }

    for (int j = 0; j < T; j++)
    {
        int x = (j % w);
        int y = (j - x) / w;
        RGBA s = {{1.0, 1.0, 1.0, 1.0}};
        for (int i = 0; i < n; i++)
        {
            s = Vec4Mult(s, rgbas[i * T + j]);
        }
        s = Vec4PowS(s, 1.0 / 2.2);
        pixels[(h - 1 - y) * w + x] = (~ToRGBA32V4(s)) | 0xFF000000;
        if (j % (T / 10) == 0)
        {
            printf("%d\n", j);
        }
    }
    stbi_write_png("./imgs/outG.png", w, h, 4, pixels, w * sizeof(RGBA32));
    return 0;
}


