#include <iostream>
#include <vector>
#include <algorithm>
template <typename T>
size_t get_number(T t, std::vector<T> &vt)
{
    auto iter = vt.begin();
    size_t num = 0;
    while (iter != vt.end())
    {
        iter = std::find(iter, vt.end(), t);
        if (iter != vt.end())
        {
            ++num;
            ++iter;
        }
    }
    return num;
}

size_t get_number(const char *t, std::vector<std::string> &vt)
{
    auto iter = vt.begin();
    size_t num = 0;
    while (iter != vt.end())
    {
        iter = std::find(iter, vt.end(), t);
        if (iter != vt.end())
        {
            ++num;
            ++iter;
        }
    }
    return num;
}

template <>
size_t get_number(const char *t, std::vector<const char *> &vt)
{
    auto iter = vt.begin();
    size_t num = 0;
    while (iter != vt.end())
    {
        iter = std::find(iter, vt.end(), t);
        if (iter != vt.end())
        {
            ++num;
            ++iter;
        }
    }
    return num;
}

int main()
{
    std::vector<double> vd = {1, 2, 3, 3.14, 4, 3.14, 5, 6.28};
    std::vector<int> vi = {1, 2, 3, 3, 4, 3, 5, 6};
    std::vector<std::string> vs = {"a", "bb", "ccc", "dddd"};
    std::vector<const char *> vcp = {"a", "bb", "ccc", "dddd"};

    std::cout << get_number(3.14, vd) << std::endl;
    std::cout << get_number(3, vi) << std::endl;
    std::cout << get_number("a", vs) << std::endl;
    std::cout << get_number("a", vcp) << std::endl;

    return 0;
}