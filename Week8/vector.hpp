#pragma once
template<class T>
class Vector
{
    T* arr;
    std::size_t capacity;
    std::size_t size;
    public:
        class Iterator
        {
            protected:
                Vector<T> *v;
                std::size_t idx;
                Iterator(Vector<T> *v, std::size_t idx) : v(v), idx(idx) {}
            public:
                Iterator& operator++();
                Iterator operator++(int);

        }
}
Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
    ++this->idx;
    return *this;
}
Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    Iterator res = *this;
    this->operator++;
    return res;
} 