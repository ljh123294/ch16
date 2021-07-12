// 编写自己的vec<T>
#ifndef VEC_H_
#define VEC_H_

#include <string>
#include <memory>
// #include <utility>

template <typename T>
class Vec;

template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator==(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator<=(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator>=(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator<(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator>(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs);
template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
class Vec
{
    friend bool operator!=<T>(Vec &lhs, Vec &rhs);
    friend bool operator==<T>(Vec &lhs, Vec &rhs);
    friend bool operator<=<T>(Vec &lhs, Vec &rhs);
    friend bool operator>=<T>(Vec &lhs, Vec &rhs);
    friend bool operator<< T>(Vec &lhs, Vec &rhs);
    friend bool operator><T>(Vec &lhs, Vec &rhs);

public:
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(const Vec &);
    Vec &operator=(const Vec &);
    Vec(std::initializer_list<T>);
    Vec(Vec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(cap)) { s.elements = s.first_free = s.cap = nullptr; }
    ~Vec();
    void push_back(const T &);
    size_t size() const
    {
        return first_free - elements;
    }
    size_t capacity() const
    {
        return cap - elements;
    }
    std::string *begin() const
    {
        return elements;
    }
    std::string *end() const
    {
        return first_free;
    }
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const std::string &s);

private:
    T *elements;
    T *first_free;
    T *cap;
    std::allocator<T> alloc;
    std::pair<T *, T *> alloc_n_copy(const T *, const T *);
    void free();
    void reallocate();
    void my_alloc(size_t);
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
};

template <typename T>
void Vec<T>::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

template <typename T>
void Vec<T>::my_alloc(size_t n)
{
    auto new_data = alloc.allocate(n);
    auto dest = new_data;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = new_data;
    first_free = dest;
    cap = elements + n;
}

template <typename T>
void Vec<T>::reallocate()
{
    auto new_capacity = size() ? 2 * size() : 1;
    my_alloc(new_capacity);
}

template <typename T>
void Vec<T>::push_back(const T &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

template <typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

template <typename T>
Vec<T>::Vec(const Vec &sv)
{
    auto data = alloc_n_copy(sv.begin(), sv.end());
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> ilst)
{
    auto data = alloc_n_copy(ilst.begin(), ilst.end());
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
Vec<T>::~Vec()
{
    free();
}

template <typename T>
void Vec<T>::reserve(size_t n)
{
    if (n <= capacity())
        return;
    my_alloc(n);
}

template <typename T>
void Vec<T>::resize(size_t n)
{
    resize(n, std::string());
}

template <typename T>
void Vec<T>::resize(size_t n, const std::string &s)
{
    if (n < size())
    {
        while (n < size())
            alloc.destroy(--first_free);
    }
    else if (n > size())
    {
        while (n > size())
            push_back(s);
    }
}

template <typename T>
bool operator==(Vec<T> &lhs, Vec<T> &rhs)
{
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(Vec<T> &lhs, Vec<T> &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator>(Vec<T> &lhs, Vec<T> &rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator<=(Vec<T> &lhs, Vec<T> &rhs)
{
    return !(rhs > lhs);
}

template <typename T>
bool operator>=(Vec<T> &lhs, Vec<T> &rhs)
{
    return !(rhs < lhs);
}
#endif