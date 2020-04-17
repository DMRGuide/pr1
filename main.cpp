//1142 Караблин Дмитрий
//Не очень понял, что должен делать вывод, но по данным получилось так
#include <iostream>
using namespace std;
class Complex {
	double re, im;
public:
	Complex(double r = 0, double i = 0) { re = r; im = i;}
	Complex(const Complex& c) {
		re = c.re;
		im = c.im;
	}
	double &Re() { return re; }
	double &Im() { return im; }
	Complex operator +(const Complex& c)const
	{
		return Complex(re + c.re, im + c.im);
	}
	Complex operator -(const Complex& c)const
	{
		return Complex(re - c.re, im - c.im);
	}
	friend ostream &operator << (ostream &o, const Complex &c)
	{
		return o << '(' << c.re << ";" << c.im << ')';
	}
};
int main()
{
	Complex a(2, 4);
	Complex b(6, 1);
	Complex c(a);
	std::cout << a << std::endl; // 2 + 4i 
	std::cout << a + b << std::endl; // 8 + 5i
	b = a;
	std::cout << a << std::endl; // 4 + 8i

}
