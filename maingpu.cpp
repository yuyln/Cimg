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

    char *kernel;
    ReadFile("kernel.c", &kernel);

    InitPlatforms(&plats, &nplat);
    InitDevice(&devices, plats[i_], i_, &ndev);
    InitContext(&context, devices);
    InitQueue(&queue, &context, devices);

    InitProgram(&program, &context, 1, (const char**)&kernel);
    BuildProgram(&program, 1, devices, "-I./headers -DOPENCLCOMP");
    return 0;
}

