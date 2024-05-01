#include<iostream>
template<class T> 
void loop0(T f, const size_t n)
{
    for(int i=0; i<n; i++)
    {
        f();
    }
}
void loop(void (*f)(), const size_t n)
{
    for(int i=0; i<n; i++)
    {
        f();
    }
}
int repeat(int (*f)(int), const int x0, const size_t n)
{
    int res = x0;
    for(int i=0; i<n; i++)
    {
        res = f(res);
    }
    return res;
}
void sort(int *arr, const size_t n, bool (*cmp)(int,int))
{
    while(1)
    {
        bool flag = false;
        for(int i=0; i+1<n; i++)
        {
            if(cmp(arr[i+1], arr[i]))
            {
                std::swap(arr[i+1], arr[i]);
                flag = true;
            }
        }
        if(!flag) break;
    }
}
template<class T>
void print(const T *arr, const size_t size)
{
    for(size_t i=0; i<size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout<<std::endl;
}
void printSomething() { std::cout << "[Hello]"; }
int	 mul2(int n) { return 2 * n; }
bool less(int a, int b) { return a < b; }
bool greater(int a, int b) { return a > b; }
int main() {
	loop0(printSomething, 5);
	std::cout << std::endl;
	loop(printSomething, 5);
	std::cout << std::endl;

	std::cout << repeat(mul2, 10, 3) << std::endl;

	int arr[] = {3, 2, 1, 5, 3, 4, 7, 9, 8, 0};
	sort(arr, 10, less);
	print(arr, 10);
	sort(arr, 10, greater);
	print(arr, 10);

	return 0;
}