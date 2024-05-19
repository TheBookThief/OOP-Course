#include<iostream>
class Vector
{
    public:
        int x,y;

        Vector(float x, float y) : x(x), y(y) {}
        Vector operator*(float lambda) const { return Vector(this->x*lambda, this->y*lambda); }
        Vector operator+(const Vector &other) const { return Vector(this->x+other.x, this->y+other.y); } 
        Vector operator-(const Vector &other) const { return Vector(this->x-other.x, this->y-other.y); }
        Vector& operator*=(float lambda)
        {
            this->x *= lambda;
            this->y *= lambda;
            return *this;
        }
        Vector& operator /=(float lambda)
        {
            this->x /= lambda;
            this->y /= lambda;
            return *this;
        }
        static float dot(const Vector a, const Vector b) 
        {
            return a.x*b.x+a.y*b.y;
        }

    
};
Vector operator*(float lambda, const Vector &other)
{
    return Vector(lambda*other.x, lambda*other.y);
}
int main() 
{
	Vector a(1, 2), b(2, 1);
	Vector c = a * 2;
    std::cout << c.x << " " << c.y << std::endl;
    c = (float)(4) * a;
    std::cout << c.x << " " << c.y << std::endl;
	a *= 2;
	
}