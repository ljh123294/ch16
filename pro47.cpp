#include <iostream>
#include <memory>

void func_lvalue(std::string &lhs, std::string &rhs)
{
    lhs = "Wang\n";
    rhs = "Alan\n";
}

void func_rvalue(int &&lhs, int &&rhs)
{
    std::allocator<int> alloc;
    int *data(alloc.allocate(3));

    alloc.construct(data, lhs);
    alloc.construct(data + 1, 0);
    alloc.construct(data + 2, rhs);

    for (auto p = data; p != data + 3; ++p)
        std::cout << *p << "\n";

    for (auto p = data + 3; p != data;)
        alloc.destroy(--p);
    alloc.deallocate(data, 3);
}

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

int main()
{
    std::string s1, s2;
    flip(func_lvalue, s1, s2);
    std::cout << s1 << s2;
    flip(func_rvalue, 99, 88);
    int b = 0;
    int &&a = (int &&)b;
    int &c = (int &)b;
    return 0;
}
