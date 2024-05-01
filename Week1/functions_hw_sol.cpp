#include<iostream>
#include<cmath>
template<class T>
void print(const T *arr, const size_t size)
{
    for(size_t i=0; i<size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout<<std::endl;
}
template<class T>
T *filter(const T *arr, const size_t size, bool (*f)(T), size_t &retSize)
{
    retSize = 0;
    for(int i=0; i<size; i++)
    {
        retSize += f(arr[i]);
    }
    T *res = new T[retSize];
    int idx = 0;
    for(int i=0; i<size; i++)
    {
        if(f(arr[i]))
        {
            res[idx] = arr[i];
            idx++;
        }
    }
    return res;
}
bool even(int a) { return !(a % 2); }
bool prime(int a) 
{ 
	if(a < 2) return false;
	int sqrt_a = sqrt(a);
	for(int i = 2; i <= sqrt_a; ++i) {
		if(a % i == 0) return false;
	}
	return true;
}
int main() 
{
	int arr[]{0,1,2,3,4,5,6,7,8,9,10};

	std::size_t newSize;
	int *res = filter(arr, 11, even, newSize);
	print(res, newSize);
	delete []res;
	
	res = filter(arr, 11, prime, newSize);
	print(res, newSize);
	delete []res;

}