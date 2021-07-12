#include <vector>
#include <string>
#include <iostream>
#include <iterator>
template <typename T>
void print_vector(const T &v)
{
    for (typename T::size_type i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

template <typename T>
void print_vector1(const T &v)
{
    for (typename T::const_iterator i = v.begin(); i != v.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
}

void print_vector2(const std::vector<std::size_t> &v)
{
    for (auto i = v.begin(); i != v.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> vs{"aa", "bb", "cc"};
    std::vector<std::size_t> vi{1, 2, 3};
    print_vector(vs);
    print_vector1(vs);
    print_vector(vi);
    print_vector1(vi);
    print_vector2(vi);
}
