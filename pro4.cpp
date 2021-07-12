#include <vector>
#include <list>
#include <string>
#include <iostream>
template <typename InputIt, typename T>
InputIt find(const InputIt beg, const InputIt end, const T &value)
{
    for (InputIt iter = beg; iter != end; ++iter)
    {
        if (*iter == value)
            return iter;
    }
}

int main()
{
    std::vector<int> vi{1, 2, 3};
    std::list<std::string> ls{"aa", "bb", "cc"};
    std::cout << *(find(vi.begin(), vi.end(), 3)) << std::endl;
    std::cout << *(find(ls.begin(), ls.end(), "aa")) << std::endl;
}
