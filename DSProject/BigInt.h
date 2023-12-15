#pragma once
#include <iostream>
#include <bits.h>
using namespace std;

class BigInt {
public:
	string digits = "";

	//Constructors:
	BigInt(string& s) {
		digits = "";
		int n = s.size();
		for (int i = n - 1; i >= 0;i--) {
			if (!isdigit(s[i]))
				throw("ERROR");
			digits.push_back(s[i] - '0');
		}
	}
	BigInt(unsigned long long nr = 0) {
		do {
			digits.push_back(nr % 10);
			nr /= 10;
		} while (nr);
	}
	BigInt(const char* s) {
		digits = "";
		for (int i = strlen(s) - 1; i >= 0;i--) {
			if (!isdigit(s[i]))
				throw("ERROR");
			digits.push_back(s[i] - '0');
		}
	}
	BigInt(BigInt& a) {
		digits = a.digits;
	}

	//Helper Functions:
	bool Null(const BigInt& a) {
		if (a.digits.size() == 1 && a.digits[0] == 0)
			return true;
		return false;
	}
	int Length(const BigInt& a)const {
		return a.digits.size();
	}
	int operator[](const int index)const {
		if (digits.size() <= index || index < 0)
			throw("ERROR");
		return digits[index];
	}

	/* * * * Operator Overloading * * * */

//Direct assignment
	bool operator==(const BigInt& b) {
		return this->digits == b.digits;
	}
	bool operator!=(const BigInt& b) {
		return !(*this == b);
	}
	bool operator<(const BigInt& b)const {
		int n = Length(*this), m = Length(b);
		if (n != m)
			return n < m;
		while (n--)
			if (this->digits[n] != b.digits[n])
				return this->digits[n] < b.digits[n];
		return false;
	}
	bool operator>(const BigInt& b)const {
		return b < *this;
	}
	bool operator>=(const BigInt& b) {
		return !(*this < b);
	}
	bool operator<=(BigInt& b) {
		return !(*this > b);
	}

	BigInt& operator=(const BigInt& a) {
		digits = a.digits;
		return *this;
	}

	BigInt& operator++() {
		int i, n = digits.size();
		for (i = 0; i < n && digits[i] == 9;i++)
			digits[i] = 0;
		if (i == n)
			digits.push_back(1);
		else
			digits[i]++;
		return *this;
	}
	BigInt operator++(int temp) {
		BigInt aux;
		aux = *this;
		++(*this);
		return aux;
	}

	BigInt& operator--() {
		if (digits[0] == 0 && digits.size() == 1)
			throw("UNDERFLOW");
		int i, n = digits.size();
		for (i = 0; digits[i] == 0 && i < n;i++)
			digits[i] = 9;
		digits[i]--;
		if (n > 1 && digits[n - 1] == 0)
			digits.pop_back();
		return *this;
	}
	BigInt operator--(int temp) {
		BigInt aux;
		aux = *this;
		--(*this);
		return aux;
	}

	BigInt& operator+=( const BigInt& b) {
		int t = 0, s = 0, i = 0;
		int n = Length(*this), m = Length(b);
		if (m > n)
			this->digits.append(m - n, 0);
		n = Length(*this);
		for (i = 0; i < n; i++) {
			if (i < m)
				s = (this->digits[i] + b.digits[i]) + t;
			else
				s = this->digits[i] + t;
			t = s / 10;
			this->digits[i] = (s % 10);
		}
		if (t)
			this->digits.push_back(t);
		return *this;
	}
	BigInt operator+( const BigInt& b) {
		BigInt temp;
		temp = *this;
		temp += b;
		return temp;
	}

	BigInt& operator-=( const BigInt& b) {
		if (*this < b)
			throw("UNDERFLOW");
		int n = Length(*this), m = Length(b);
		int i, t = 0, s;
		for (i = 0; i < n;i++) {
			if (i < m)
				s = this->digits[i] - b.digits[i] + t;
			else
				s = this->digits[i] + t;
			if (s < 0)
				s += 10,
				t = -1;
			else
				t = 0;
			this->digits[i] = s;
		}
		while (n > 1 && this->digits[n - 1] == 0)
			this->digits.pop_back(),
			n--;
		return *this;
	}
	BigInt operator-( const BigInt& b) {
		BigInt temp;
		temp = *this;
		temp -= b;
		return temp;
	}

	BigInt& operator*=(const BigInt& b) {
		if (Null(*this) || Null(b)) {
			*this = BigInt();
			return *this;
		}
		int n = this->digits.size(), m = b.digits.size();
		//vector<int> v(n + m, 0);
		int* v = new int[n + m] {0};
		int size = 0;
		for (int i = 0; i < n;i++)
			for (int j = 0; j < m;j++) {
				v[i + j] += (this->digits[i]) * (b.digits[j]);
			}
		for (int i = 0; i < n + m;i++) {
			if (v[i] != 0)
				size++;
		}
		n += m;
		//cout <<endl << endl << endl << v.size()<< " " <<n<< endl << endl << endl;

		this->digits.resize(n);
		for (int s, i = 0, t = 0; i < n; i++) {
			s = t + v[i];
			v[i] = s % 10;
			t = s / 10;
			this->digits[i] = v[i];
		}
		for (int i = n - 1; i >= 1 && !v[i];i--)
			this->digits.pop_back();
		return *this;
	}
	

	friend BigInt operator*(const BigInt&, const BigInt&);

	BigInt& operator/=( const BigInt& b) {
		if (Null(b))
			throw("Arithmetic Error: Division By 0");
		if (*this < b) {
			*this = BigInt();
			return *this;
		}
		if (*this == b) {
			*this = BigInt(1);
			return *this;
		}
		int i, lgcat = 0, cc;
		int n = Length(*this), m = Length(b);
		//vector<int> cat(n, 0);
		int* cat = new int[n] {0};
		BigInt t;
		for (i = n - 1; t * 10 + this->digits[i] < b;i--) {
			t *= 10;
			t += this->digits[i];
		}
		for (; i >= 0; i--) {
			t = t * 10 + this->digits[i];
			for (cc = 9; cc * b > t;cc--);
			t -= cc * b;
			cat[lgcat++] = cc;
		}
		this->digits.resize(n);
		for (i = 0; i < lgcat;i++)
			this->digits[i] = cat[lgcat - i - 1];
		this->digits.resize(lgcat);
		return *this;
	}
	BigInt operator/( const BigInt& b) {
		BigInt temp;
		temp = *this;
		temp /= b;
		return temp;
	}

	BigInt& operator%=( const BigInt& b) {
		if (Null(b))
			throw("Arithmetic Error: Division By 0");
		if (*this < b) {
			return *this;
		}
		if (*this == b) {
			*this = BigInt();
			return *this;
		}
		int i, lgcat = 0, cc;
		int n = Length(*this), m = Length(b);
		//vector<int> cat(n, 0);
		int* cat = new int[n] {0};
		BigInt t;
		for (i = n - 1; t * 10 + this->digits[i] < b;i--) {
			t *= 10;
			t += this->digits[i];
		}
		for (; i >= 0; i--) {
			t = t * 10 + this->digits[i];
			for (cc = 9; cc * b > t;cc--);
			t -= cc * b;
			cat[lgcat++] = cc;
		}
		*this = t;
		return *this;
	}
	BigInt operator%(BigInt& b) {
		BigInt temp;
		temp = *this;
		temp %= b;
		return temp;
	}

	friend void power(BigInt& a, BigInt& b);

	//Read and Write
	friend ostream& operator<<(ostream&, const BigInt&);
	friend istream& operator>>(istream&, BigInt&);

};



BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}


	void power(BigInt& a, BigInt& b) {
		if ((b.digits.size() == 1 && b.digits[0] == 0))
			a = 1;
		else {
			BigInt temp(a), i(1);
			for (i; i < b; i++) {
				a = a * temp;
			}
		}
	}

istream& operator>>(istream& in, BigInt& a) {
	string s;
	in >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0;i--) {
		if (!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.digits[n - i - 1] = s[i];
	}
	return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
	for (int i = a.digits.size() - 1; i >= 0;i--)
		cout << (short)a.digits[i];
	return cout;
}