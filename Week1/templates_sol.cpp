#include<iostream>
#include <string.h>
// task 0
template<class T>
void print(const T *arr, const size_t size)
{
    for(size_t i=0; i<size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout<<std::endl;
}
// task 1
template<class T>
T sum(const T *arr, const size_t size)
{
    T sum = arr[0];
    for(size_t i=1; i<size; i++)
    {
        sum += arr[i];
    }
    return sum;
}
// task 2
template<class T>
T max(const T *arr, const size_t size)
{
    T max = arr[0];
    for(size_t i=1; i<size; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}
// task 3
template<class T>
int count(const T *arr, const size_t size)
{
    int cnt = 0;
    for(int i=0; i<size; i++)
    {
        if(arr[i] >= 0)
            cnt++;
    }
    return cnt;
}
// task 4 
template<class T> 
T* filterMoreThan(const T *arr, const size_t size, const T k, size_t &new_size)
{
    for(int i=0; i<size; i++)
    {
        if(arr[i] > k)
        {
            new_size++;
        }
    }
    T *new_arr = new T[new_size];
    int idx = 0;
    for(int i=0; i<size; i++)
    {
        if(arr[i] > k)
        {
            new_arr[idx] = arr[i];
            idx++;
        }
    }
    return new_arr;
}
int main()
{
    char *text1 = "Hello World!";
    print(text1, strlen(text1));
    std::cout<< sum(text1, strlen(text1)) <<std::endl;
    std::cout<< max(text1, strlen(text1)) <<std::endl;
    std::cout<< count(text1, strlen(text1)) <<std::endl;

    float arr3[] = {-2, 1, 3, -1, 3, -10};
	size_t filteredSize;
	float *filtered = filterMoreThan(arr3, 6, -1.f, filteredSize);
	print(filtered, filteredSize);
}