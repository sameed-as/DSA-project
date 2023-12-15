#pragma once
#include <iostream>
#include <bits.h>
using namespace std;

class BigInt {
public:
	string dig = "";

	BigInt(string& str) {
		dig = "";
		int size = str.size();
		for (int i = size - 1; i >= 0;i--) {
			dig.push_back(str[i] - '0');
		}
	}
	BigInt(unsigned long long num = 0) {
		do {
			dig.push_back(num % 10);
			num /= 10;
		} while (num);
	}
	BigInt(const char* str) {
		dig = "";
		int size = strlen(str);
		for (int i = size - 1; i >= 0;i--) {
			dig.push_back(str[i] - '0');
		}
	}
	BigInt(BigInt& copy) {
		dig = copy.dig;
	}

	bool Null(const BigInt& first) {
		if (first.dig.size() == 1 && first.dig[0] == 0)
			return true;
		return false;
	}
	int Length(const BigInt& first)const {
		return first.dig.size();
	}
	int operator[](const int index)const {
		return dig[index];
	}
	bool operator==(const BigInt& other) {
		return this->dig == other.dig;
	}
	bool operator!=(const BigInt& other) {
		return !(*this == other);
	}
	bool operator<(const BigInt& other)const {
		int s1 = Length(*this), s2 = Length(other);
		if (s1 != s2)
			return s1 < s2;
		while (s1--)
			if (this->dig[s1] != other.dig[s1])
				return this->dig[s1] < other.dig[s1];
		return false;
	}
	bool operator>(const BigInt& other)const {
		return other < *this;
	}
	bool operator>=(const BigInt& other) {
		return !(*this < other);
	}
	bool operator<=(BigInt& other) {
		return !(*this > other);
	}

	BigInt& operator=(const BigInt& first) {
		dig = first.dig;
		return *this;
	}

	BigInt& operator++() {
		int i, s1 = dig.size();
		for (i = 0; i < s1 && dig[i] == 9;i++)
			dig[i] = 0;
		if (i == s1)
			dig.push_back(1);
		else
			dig[i]++;
		return *this;
	}
	BigInt operator++(int temp) {
		BigInt temporary;
		temporary = *this;
		++(*this);
		return temporary;
	}

	BigInt& operator--() {
		int i, s1 = dig.size();
		for (i = 0; dig[i] == 0 && i < s1;i++)
			dig[i] = 9;
		dig[i]--;
		if (s1 > 1 && dig[s1 - 1] == 0)
			dig.pop_back();
		return *this;
	}
	BigInt operator--(int temp) {
		BigInt temporary;
		temporary = *this;
		--(*this);
		return temporary;
	}

	BigInt& operator+=( const BigInt& other) {
		int num1 = 0, num2 = 0;
		int s1 = Length(*this), s2 = Length(other);
		if (s2 > s1)
			this->dig.append(s2 - s1, 0);
		s1 = Length(*this);
		for (int i = 0; i < s1; i++) {
			if (i < s2)
				num2 = (this->dig[i] + other.dig[i]) + num1;
			else
				num2 = this->dig[i] + num1;
			num1 = num2 / 10;
			this->dig[i] = (num2 % 10);
		}
		if (num1)
			this->dig.push_back(num1);
		return *this;
	}
	BigInt operator+( const BigInt& other) {
		BigInt temporary;
		temporary = *this;
		temporary += other;
		return temporary;
	}

	BigInt& operator-=( const BigInt& other) {
		int s1 = Length(*this), s2 = Length(other);
		int  num1 = 0, num2;
		for (int i = 0; i < s1;i++) {
			if (i < s2)
				num2 = this->dig[i] - other.dig[i] + num1;
			else
				num2 = this->dig[i] + num1;
			if (num2 < 0)
				num2 += 10,
				num1 = -1;
			else
				num1 = 0;
			this->dig[i] = num2;
		}
		while (s1 > 1 && this->dig[s1 - 1] == 0)
			this->dig.pop_back(),
			s1--;
		return *this;
	}
	BigInt operator-( const BigInt& other) {
		BigInt temporary;
		temporary = *this;
		temporary -= other;
		return temporary;
	}

	BigInt& operator*=(const BigInt& other) {
		if (Null(*this) || Null(other)) {
			*this = BigInt();
			return *this;
		}
		int s1 = this->dig.size(), s2 = other.dig.size();
		int* arr = new int[s1 + s2] {0};
		int size = 0;
		for (int i = 0; i < s1;i++)
			for (int j = 0; j < s2;j++) {
				arr[i + j] += (this->dig[i]) * (other.dig[j]);
			}
		for (int i = 0; i < s1 + s2;i++) {
			if (arr[i] != 0)
				size++;
		}
		s1 += s2;

		this->dig.resize(s1);
		int num1 = 0 , num2 = 0;
		for (int i = 0; i < s1; i++) {
			num1 = num2 + arr[i];
			arr[i] = num1 % 10;
			num2 = num1 / 10;
			this->dig[i] = arr[i];
		}
		for (int i = s1 - 1; i >= 1 && !arr[i];i--)
			this->dig.pop_back();
		return *this;
	}
	

	friend BigInt operator*(const BigInt&, const BigInt&);

	BigInt& operator/=( const BigInt& other) {
		
		int counter, idx = 0, check;
		int s1 = Length(*this), s2 = Length(other);
		int* arr = new int[s1] {0};
		BigInt temp;
		for (counter = s1 - 1; temp * 10 + this->dig[counter] < other;counter--) {
			temp *= 10;
			temp += this->dig[counter];
		}
		for (; counter >= 0; counter--) {
			temp = temp * 10 + this->dig[counter];
			for (check = 9; check * other > temp;check--);
			temp -= check * other;
			arr[idx++] = check;
		}
		this->dig.resize(s1);
		for (counter = 0; counter < idx;counter++)
			this->dig[counter] = arr[idx - counter - 1];
		this->dig.resize(idx);
		return *this;
	}
	BigInt operator/( const BigInt& other) {
		BigInt temporary;
		temporary = *this;
		temporary /= other;
		return temporary;
	}

	BigInt& operator%=( const BigInt& other) {
		int counter, idx = 0, check;
		int s1 = Length(*this), s2 = Length(other);
		//vector<int> cat(s1, 0);
		int* arr = new int[s1] {0};
		BigInt temp;
		for (counter = s1 - 1; temp * 10 + this->dig[counter] < other;counter--) {
			temp *= 10;
			temp += this->dig[counter];
		}
		for (; counter >= 0; counter--) {
			temp = temp * 10 + this->dig[counter];
			for (check = 9; check * other > temp;check--);
			temp -= check * other;
			arr[idx++] = check;
		}
		*this = temp;
		return *this;
	}
	BigInt operator%(BigInt& other) {
		BigInt temp;
		temp = *this;
		temp %= other;
		return temp;
	}

	friend void power(BigInt& first, BigInt& second);

	//Read and Write
	friend ostream& operator<<(ostream&, const BigInt&);
	friend istream& operator>>(istream&, BigInt&);

};



BigInt operator*(const BigInt& first, const BigInt& second) {
	BigInt temp;
	temp = first;
	temp *= second;
	return temp;
}


	void power(BigInt& first, BigInt& second) {
		if ((second.dig.size() == 1 && second.dig[0] == 0))
			first = 1;
		else {
			BigInt temp(first), i(1);
			for (i; i < second; i++) {
				first = first * temp;
			}
		}
	}

istream& operator>>(istream& in, BigInt& a) {
	string s;
	in >> s;
	int s1 = s.size();
	for (int i = s1 - 1; i >= 0;i--) {
		if (!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.dig[s1 - i - 1] = s[i];
	}
	return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
	for (int i = a.dig.size() - 1; i >= 0;i--)
		cout << (short)a.dig[i];
	return cout;
}