#include <iostream>
#include <string>

template <typename T, unsigned N>
T *begin(T (&arr)[N])
{
    return arr;
}

template <typename T, unsigned N>
T *end(T (&arr)[N])
{
    return arr + N - 1;
}

int main()
{
    char ac[] = "aabbccdd";

    std::cout << *(begin(ac)) << std::endl;
    std::cout << *(end(ac) - 2) << std::endl;

    return 0;
}
