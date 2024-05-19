#include<iostream>
#include<cstring>
#include<ostream>
class Word
{
    public:
        Word()
        {
            size = 0;
            capacity = 1;
            arr = new char[1];
        }
        Word(const char *word)
        {
            size = strlen(word);
            capacity = size;
            arr = new char[capacity+1];
            for(int i=0; i<size; i++)
            {
                arr[i] = word[i];
            }
            std::cout<<size<<std::endl;
        }
        Word(const Word& word)
        {
            copy(word);
        }
        ~Word()
        {
            delete[] arr;
        }
        Word& operator=(const Word& other)
        {
            if(this == &other) return *this;
            delete[] arr;
            copy(other);
            return *this;
        }
        Word& operator+=(const Word& other)
        {
            if(size + other.size > capacity)
            {
                size_t newCap = capacity;
                while(newCap < size + other.size) newCap *= 2;
                resize(newCap);
            }
            for(int i=0; i<other.size; i++)
            {
                arr[size+i] = other.arr[i];
            }
            size = size + other.size;
            return *this;
        }
        Word operator+(Word &other)
        {
            Word result(*this);
            result += other;
            return result;
        }
        Word& operator<<(int pos)
        {
            for(int i=0; i<pos; i++)
            {
                this->shiftleft();
            }
            return *this;
        }
        Word operator~()
        {
            Word res(*this);
            for(int i=0; i<size; i++)
            {
                res.arr[i] = arr[size-i-1];
            }
            return res;
        }
    private:
        void copy(const Word& word)
        {
            size = word.size;
            capacity = size;
            arr = new char[size];
            for(int i=0; i<size; i++)
            {
                arr[i] = word.arr[i];
            }
        }
        void resize(size_t newCap)
        {
            char *new_arr = new char[newCap];
            for(int i=0; i<size; i++)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
            capacity = newCap;
        }
        void shiftleft()
        {
            if(size <= 1) return;
            char first = arr[0];
            for(int i=0; i<size-1; i++)
            {
                arr[i] = arr[i+1];
            }
            arr[size-1] = first;
        }
        char* arr;
        size_t size, capacity;

        friend std::ostream &operator<<(std::ostream &out, const Word &word);    
};
std::ostream &operator<<(std::ostream &out, const Word &word)
{
    std::cout<<word.size<<std::endl;
    for(std::size_t i=0; i<word.size; i++)
    {
        out<<word.arr[i];
    }
    return out;
}
int main() {
	
	Word hello("Hello");
	Word world("World");

	Word HelloWorld = hello + world;
	std::cout << HelloWorld << std::endl;

	Word traicho("Traicho");
    std::cout<< traicho << std::endl;
    
	std::cout << (traicho << 2) << std::endl;
	std::cout<< traicho << std::endl;
    
    std::cout << (~traicho) << std::endl;
}