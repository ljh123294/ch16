#include <iostream>
template <typename T>
int compare(const T &lhs, const T &rhs)
{
    if (lhs < rhs)
        return -1;
    else if (lhs > rhs)
        return 1;
    else
        return 0;
}
int main()
{
    std::cout << compare(1, 2);
}