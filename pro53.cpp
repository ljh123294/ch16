#include <iostream>
#include <string>

template <typename T>
void print(std::ostream &os, const T &t)
{
    os << t << ",";
}

template <typename T, typename... Args>
void print(std::ostream &os, const T &t, Args... rest)
{
    os << t << ",";
    print(os, rest...);
}

int main()
{
    int i = 1, *p = &i;
    double d = 0.1;
    std::string s = "abc";

    print(std::cout, i);
    std::cout << std::endl;
    print(std::cout, i, d);
    std::cout << std::endl;
    print(std::cout, i, d, s, p, "ccc");
    std::cout << std::endl;

    return 0;
}