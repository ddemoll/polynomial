#include <iostream>
#include <list>
#include <vector>
#include <string> 
#include <sstream>
#include "Polynomial.h"
using namespace std;

int main() {

	cout << "Testing addition" << endl;
	Polynomial<int> p;
	cin >> p;
	//p.read(istringstream("2 2 4 1 0"));
	Polynomial<int> p2;
	p2.read(istringstream("6 5 3 1 -5 2 0"));
	cout << "p: " << p << endl << "p2: " << p2 << endl << "Execute p += p2" << endl;
	p += p2;
	cout << "p: " << p << endl << "Execute p += 10x^2" << endl;;
	p += Monomial<int> { 10, 2 };
	cout << "p: " << p << endl;
	cout << "p(25) = " << p.evaluate(25) << endl;
	
	Polynomial<int> p3, p4;
	p3.read(istringstream("3 4 5 1 0"));
	p4.read(istringstream("5 4 1 5 0"));
	cout << p3 << " + " << p4 << " = " << p3 + p4 << endl;

	cout << p3 << " + -10x = " << p3 + Monomial<int> { -10, 1 } << endl << endl;

	cout << "Testing subtraction" << endl;
	Polynomial<int> p8, p9;
	p8.read(istringstream("9 2 7 1 0"));
	p9.read(istringstream("3 2 2 1 5 0 0"));
	cout << "p8: " << p8 << endl << "p9: " << p9 << endl << "Execute p8 -= p9" << endl;
	p8 -= p9;
	cout << "p8: " << p8 << endl << "Execute p8 -= -10x" << endl;
	p8 -= Monomial<int> { -10, 1 };
	cout << "p8: " << p8 << endl;
	
	Polynomial<int> p5, p6;
	p5.read(istringstream("10 5 23 7 4 8 0"));
	p6.read(istringstream("5 4 1 5 0"));
	cout << p5 << " - (" << p6 << ") = " << p5 - p6 << endl;

	cout << p5 << " - (-5x^30) = " << p5 - Monomial<int> { -5, 30 } << endl << endl;
	

	cout << "Testing multiplication" << endl;
	Polynomial<int> p10, p11;
	p10.read(istringstream("2 2 5 6 5 0 0"));
	p11.read(istringstream("3 5 23 3 5 0 0"));
	cout << "p10: " << p10 << endl << "p11: " << p11 << endl << "Execute p10 *= p11" << endl;
	p10 *= p11;
	cout << "p10: " << p10 << endl << "Execute p8 *= 10x^4" << endl;
	p10 *= Monomial<int> { 10, 4 };
	cout << "p10: " << p10 << endl;
	cout << "p10.gethighestdegree() = " << p10.gethighestdegree() << endl;
	cout << "p10 = p8" << endl;
	p10 = p8;
	cout << "p10: " << p10 << endl << "Execute p10 += 5" << endl;;
	p10 += Monomial<int>{5, 0};
	cout << "p10: " << p10 << endl;

	cout << p10 << " and " << p11 << ((p10 == p11) ? " are " : " are not ") << "equal" << endl;
	cout << p10 << " and " << p11 << ((p10 != p11) ? " are not " : " are ") << "equal" << endl;

	
	Polynomial<int> p12;
	p12.read(istringstream("5 5 -8 23 0"));
	cout << "p12: " << p12 << endl << "Execute p12 *= 3x^3" << endl;
	p12 *= Monomial<int> {3, 3};
	cout << "p12: " << p12 << endl << "Execute p12 += 0x^0" << endl;
	p12 += Monomial<int> {0, 0};
	cout << "p12: " << p12 << endl << "Execute p12 += 24x^26" << endl;;
	p12 += Monomial<int> {24, 26};
	cout << "p12: " << p12 << endl;

	Polynomial<int> p13, p14;
	p13.read(istringstream("5 2 10 96 0"));
	p14.read(istringstream("75 2 10 55 0"));
	cout << p13 << " * " << p14 << " = " << p13 * p14 << endl;
	
	Monomial<int> z{ -5, 2 };
	cout << p13 << " * -5x^2 = " << p13*z;
	
	return 0;
}