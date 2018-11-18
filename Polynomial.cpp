#ifndef __POLYNOMIAL_CPP_
#define __POLYNOMIAL_CPP_
#include <iostream>
#include <list>
#include "Polynomial.h"
using namespace std;

template<typename NumberType>
const Polynomial<NumberType> & Polynomial<NumberType>::operator=(const Polynomial<NumberType> & rhs) {
	if (this != &rhs) {
		term_list = rhs.term_list;
		number_of_terms = rhs.number_of_terms;
		highest_degree = rhs.highest_degree;
	}
	return *this;
}
//Move assignment operator
template<typename NumberType>
const Polynomial<NumberType> & Polynomial<NumberType>::operator=(const Polynomial<NumberType> && rhs) {
	if (this != &rhs) {
		//term_list = std::move(rhs.term_list);
		delete[] term_list;
		term_list = rhs.term_list;
		rhs.term_list = nullptr;
		number_of_terms = rhs.number_of_terms;
		highest_degree = rhs.highest_degree;
	}
	return *this;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator+=(const Monomial<NumberType> &m) {
	insert_in_poly(m);
	return *this;
}
template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator+=(const Polynomial<NumberType> &rhs) {
	for (list<Monomial<NumberType>>::const_iterator it = rhs.term_list.begin(); it != rhs.term_list.end(); ++it) {
		insert_in_poly(*it);
	}
	return *this;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator+ (const Monomial<NumberType> &m)const {
	Polynomial<NumberType> p(*this);
	return p += m;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator+ (const Polynomial<NumberType> & rhs)const {
	Polynomial<NumberType> p(*this);
	return p += rhs;
}


template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator-=(const Monomial<NumberType> &m) {
	insert_in_poly(Monomial<NumberType> {-(m.coefficient()), m.degree()});
	return *this;
}
template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator-=(const Polynomial<NumberType> & rhs) {
	
	for (list<Monomial<NumberType>>::const_iterator it = rhs.term_list.begin(); it != rhs.term_list.end(); ++it) {
		insert_in_poly(Monomial<NumberType> {-(it->coefficient()), it->degree()});
	}

	return *this;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator-(const Monomial<NumberType> &m)const {
	Polynomial<NumberType> p(*this);
	return p -= m;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator-(const Polynomial<NumberType> & rhs)const {
	Polynomial<NumberType> p(*this);
	return p -= rhs;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator*=(const Monomial<NumberType> &m) {
	for (list<Monomial<NumberType>>::iterator it = term_list.begin(); it != term_list.end(); ++it) {
		if (it == term_list.begin())
			highest_degree = it->degree() + m.degree();
		//do not change degree of zero polynomial
		if (it->coefficient() != 0) {
			it->assign_coefficient((it->coefficient())*(m.coefficient()));
			it->assign_degree((it->degree()) + (m.degree()));
		}
	}
	return *this;
}
template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator*=(const Polynomial<NumberType> & rhs) {
	Polynomial<NumberType> p;
	for (list<Monomial<NumberType>>::const_iterator it = term_list.begin(); it != term_list.end(); ++it) {
		for (list<Monomial<NumberType>>::const_iterator it2 = rhs.term_list.begin(); it2 != rhs.term_list.end(); ++it2) {
			p.insert_in_poly(Monomial<NumberType> {(it->coefficient())*(it2->coefficient()), (it->degree())+(it2->degree())});
		}
	}
	*this = p;
	return *this;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator*(const Monomial<NumberType> &m)const {
	Polynomial<NumberType> p(*this);
	return p *= m;
}
template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator*(const Polynomial<NumberType> &rhs)const {
	Polynomial<NumberType> p(*this);
	return p *= rhs;
}


template<typename NumberType>
const NumberType Polynomial<NumberType>::evaluate(NumberType x)const {
	NumberType sum = 0;
	for (list<Monomial<NumberType>>::const_iterator it = term_list.begin(); it != term_list.end(); ++it) {
		sum += (it->coefficient() * power(x, it->degree()));
	}
	return sum;
}
template<typename NumberType>
bool Polynomial<NumberType>::operator==(const Polynomial<NumberType> &p) const {
	return (this->term_list == p.term_list);
}
template<typename NumberType>
bool Polynomial<NumberType>::operator!=(const Polynomial<NumberType> &p) const {
	return !(this->term_list == p.term_list);
}

template<typename NumberType>
void Polynomial<NumberType>::insert_in_poly(const Monomial<NumberType> & m) {
	//do not want duplicate zero monomials
	if (m.coefficient() == 0) return;
	int m_degree = m.degree();

	list<Monomial<NumberType>>::iterator itr = term_list.begin();
	//find a spot for m
	bool inserted = false;
	while (itr != term_list.end() && !inserted) {
		//do not modify zero polynomial
		if (itr->coefficient() == 0) {
			break;
		}
		if (m_degree > itr->degree()) {
			term_list.insert(itr, m);
			inserted = true;
		}
		else if (m_degree == itr->degree()) {
			if (m.coefficient() + itr->coefficient() == 0) {
				itr = term_list.erase(itr);
					
			} else {
				itr->assign_coefficient(m.coefficient() + itr->coefficient());
			}
			inserted = true;
		}

		itr++;
	}
	if (!inserted) {
		term_list.insert(itr, m);
	}
	itr = term_list.begin();
	highest_degree = itr->degree();
	number_of_terms = term_list.size();
	
}

template<typename NumberType>
NumberType Polynomial<NumberType>::power(NumberType x, int n) const {
	NumberType result = 1;
	while (n) {
		if (n & 1)
			result *= x;
		n >>= 1;
		x *= x;
	}
	/*
	for (int i = 0; i < n; ++i) {
		result *= x;
	}
	*/
	return result;
}

template<typename NumberType>
void Polynomial<NumberType>::read(istream & in = cin) {
	NumberType c;
	NumberType e;
	in >> c;
	do {
		if (c != 0) {
			in >> e;
			if (e < 0) {
				cout << "Negative degree";
				Polynomial<NumberType> p{};
				*this = p;
				break;
			}
			Monomial<NumberType> m{ c,e };
			insert_in_poly(m);
			in >> c;
		}
		else {
			insert_in_poly(Monomial<NumberType> { 0,0 });
			
		}
	} while (c != 0);
}

template<typename NumberType>
void Polynomial<NumberType>::print(ostream & out = cout) const {
	
	list<Monomial<NumberType>>::const_iterator itr = term_list.begin();
	string c = "";
	while (itr != term_list.end()) {
		if (itr->coefficient() == 0) {
			if (itr == term_list.begin()) c = "0";
			break;
		} 
		if (itr != term_list.begin() && itr->coefficient() > 0) {
			c += "+";
		}
		
		if (itr->coefficient() != 1 || (itr->coefficient() == 1  && itr->degree() == 0)) {
			
			c += to_string(itr->coefficient());
			
		}
		
		if (itr->degree() != 0) {
			c += "x";
			if (itr->degree() != 1) {
				c += "^" + to_string(itr->degree());
			}
		}
		itr++;
	}
	out << c;
	
	
	/*
	for (list<Monomial<NumberType>>::const_iterator it = term_list.begin(); it != term_list.end(); ++it) {
		out << it->coefficient() << " " << it->degree() << " ";
	}
	*/

}

template<typename NumberType>
istream& operator >>(istream & in, Polynomial<NumberType> & rhs) {
	cout << "Please enter a polynomial: ";
	rhs.read(in);
	return in;
}
template<typename NumberType>
ostream& operator<<(ostream & out, const Polynomial<NumberType> & rhs) {
	rhs.print(out);
	
	return out;
}
#endif