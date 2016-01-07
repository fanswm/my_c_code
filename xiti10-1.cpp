#include <iostream>
using namespace std;

class Complex
{
public:
    Complex(){real=0;imag=0;}                               //默认构造函数
    Complex(double r,double i){real=r;imag=i;}              //重载构造函数
    void display();
    friend ostream& operator << (ostream&,Complex&);        //重载<<,使之可以输出复数Complex类
    friend Complex operator + (Complex c1,Complex c2);
private:
    double real;
    double imag;
};

void Complex::display()
{
    cout<<"("<<real<<"<"<<imag<<"i)"<<endl;
}

ostream& operator << (ostream& output,Complex& c)
{
    output << "(" << c.real << "+" << c.imag <<"i)"<<endl;
    return output;
}

Complex operator + (Complex c1,Complex c2)
{
    return Complex(c1.real+c2.real,c1.imag+c2.imag);
}

int main()
{
    Complex c1(3,4),c2(2,5),c3;
    c3=c1+c2;
    c3.display();
    cout<<"display"<<endl;
    cout<<"chongzai"<<endl;
    cout<<c3<<endl;
    return 0;
}

