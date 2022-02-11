#ifndef FUNCTPP
#define FUNCTPP
template <typename T>
inline T max_(T v1, T v2)
{
    return v1 * (v1 >= v2) + v2 * (v2 > v1);
}
#endif