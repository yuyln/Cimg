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
    const char *kernelnames[3] = {"ShowLGPU", "ShowCGPU", "ShowGGPU"};

    int w = 1920;
    int h = 1080;
    int T = w * h;

    char *kernel;
    ReadFile("kernel.c", &kernel);

    InitPlatforms(&plats, &nplat);
    InitDevice(&devices, plats[i_], i_, &ndev);
    InitContext(&context, devices);
    InitQueue(&queue, &context, devices);

    InitProgram(&program, &context, 1, (const char**)&kernel);
    BuildProgram(&program, 1, devices, "-I./headers -DOPENCLCOMP");

    InitKernelsStructGround(&kernels, &ks, &program, kernelnames, 3);

    InitGlobalWorkItems(1, &T, &globalwork);
    InitGroupWorkItemsGCD(1, &T, &localwork, devices);

    RGBA *rgbas = new RGBA[T];
    RGBA *rgbas2 = new RGBA[T];
    RGBA32 *pixels = new RGBA32[T];
    Curve seno, sin2;
    cl_mem senob, sin2b;
    cl_mem RGBAsb, RGBAcb;

    InitCurve(&seno, 100);
    InitCurve(&sin2, 100);
    Sin(seno, h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);
    Sin(sin2, -h / 2, 1.0 / w, 0.0, -w / 2.0, w / 2.0);

    CreateBuffer(&senob, seno.lines, sizeof(LineSegment2D) * seno.nLines, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
    WriteBuffer(&senob, seno.lines, sizeof(LineSegment2D) * seno.nLines, queue);
    CreateBuffer(&sin2b, sin2.lines, sizeof(LineSegment2D) * sin2.nLines, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
    WriteBuffer(&sin2b, sin2.lines, sizeof(LineSegment2D) * sin2.nLines, queue);


    rgbas = new RGBA[T];
    rgbas2 = new RGBA[T];
    CreateBuffer(&RGBAsb, rgbas, sizeof(RGBA) * T, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
    CreateBuffer(&RGBAcb, rgbas2, sizeof(RGBA) * T, context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
    for (int j = 0; j < T; j++)
    {
        rgbas[j] = {{1.0, 1.0, 1.0, 1.0}};
        rgbas2[j] = {{1.0, 1.0, 1.0, 1.0}};
    }
    WriteBuffer(&RGBAsb, rgbas, sizeof(RGBA) * T, queue);
    WriteBuffer(&RGBAcb, rgbas2, sizeof(RGBA) * T, queue);


    Vec4 col = {{0.0, 0b10011000, 255.0, 0.0}};
    col = Vec4MultScalar(col, 1.0 / 255.0);
    double pR = 100.0;
    double lw = 6.0;

    SetKernelArg(&kernels[2], &RGBAsb, sizeof(cl_mem), 0);
    SetKernelArg(&kernels[2], &senob, sizeof(cl_mem), 1);
    SetKernelArg(&kernels[2], &col, sizeof(Vec4), 2);
    SetKernelArg(&kernels[2], &w, sizeof(int), 3);
    SetKernelArg(&kernels[2], &h, sizeof(int), 4);
    SetKernelArg(&kernels[2], &seno.nLines, sizeof(int), 5);
    SetKernelArg(&kernels[2], &lw, sizeof(double), 6);
    SetKernelArg(&kernels[2], &pR, sizeof(double), 7);

    EnqueueND(&queue, &kernels[2], 1, NULL, globalwork, localwork);

    col = {{0xFF, 0x67, 0.0, 0.0}};
    col = Vec4MultScalar(col, 1.0 / 255.0);
    pR = 100.0;
    lw = 6.0;

    SetKernelArg(&kernels[2], &RGBAcb, sizeof(cl_mem), 0);
    SetKernelArg(&kernels[2], &sin2b, sizeof(cl_mem), 1);
    SetKernelArg(&kernels[2], &col, sizeof(Vec4), 2);
    SetKernelArg(&kernels[2], &w, sizeof(int), 3);
    SetKernelArg(&kernels[2], &h, sizeof(int), 4);
    SetKernelArg(&kernels[2], &sin2.nLines, sizeof(int), 5);
    SetKernelArg(&kernels[2], &lw, sizeof(double), 6);
    SetKernelArg(&kernels[2], &pR, sizeof(double), 7);
    
    EnqueueND(&queue, &kernels[2], 1, NULL, globalwork, localwork);

    Finish(&queue);

    ReadBuffer(&RGBAsb, rgbas, sizeof(RGBA) * T, queue);
    ReadBuffer(&RGBAcb, rgbas2, sizeof(RGBA) * T, queue);

    for (int i = 0; i < T; i++)
    {
        RGBA s = Vec4Sum(Vec4FromScalar(0.0), rgbas[i]);
        s = Vec4Mult(s, rgbas2[i]);
        s = Vec4PowS(s, 1.0 / 2.2);
        pixels[i] = (ToRGBA32V4(s)) | 0xFF000000;
    }

    stbi_write_png("./imgs/outG.png", w, h, 4, pixels, w * sizeof(RGBA32));
    return 0;
}


