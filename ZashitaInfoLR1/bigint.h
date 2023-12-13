#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

constexpr auto dec_mod = 10000;
class BigInt {
private:
	vector<int> parts;
	void increase_digit(int, int);

public:
	BigInt() : parts({ 0 }) {};
	BigInt(int n) : parts({ 0 }) { increase_digit(0, n); };
	~BigInt() {};

	BigInt& operator*(int x);
	BigInt& operator+(const BigInt& rhs) const;
	BigInt& operator*(const BigInt& rhs) const;
	BigInt pow(long power);
	friend ostream& operator<<(ostream&, const BigInt&);
};

BigInt BigInt::pow(long power) {
	BigInt newVal = *this;
	BigInt initial = *this;
	for (long i = 0; i < power; i++)
	{
		newVal = newVal * initial;
	}
	return newVal;
}

void BigInt::increase_digit(int idx, int n) {
	if (parts.size() <= idx) parts.resize(idx + 1);
	parts[idx] += n;
	int mod_g = parts[idx] % dec_mod;
	int extra = parts[idx] / dec_mod;
	parts[idx] = mod_g;

	if (extra > 0) {
		increase_digit(idx + 1, extra);
	}
}

BigInt& BigInt::operator*(int x) {
	int extra = 0;
	for (auto& g : parts) {
		g = g * x + extra;
		int mod_g = g % dec_mod;
		extra = g / dec_mod;
		g = mod_g;
	}

	while (extra > 0) {
		parts.push_back(extra % dec_mod);
		extra /= dec_mod;
	}

	return *this;
}

BigInt& BigInt::operator*(const BigInt& rhs) const {
	BigInt* mul = new BigInt();

	int size_lhs = parts.size();
	int size_rhs = rhs.parts.size();

	for (int i_lhs = 0; i_lhs < size_lhs; i_lhs++) {
		for (int i_rhs = 0; i_rhs < size_rhs; i_rhs++) {
			mul->increase_digit(i_lhs + i_rhs, parts[i_lhs] * rhs.parts[i_rhs]);
		}
	}

	return *mul;
}

BigInt& BigInt::operator+(const BigInt& rhs) const {
	BigInt& sum = const_cast<BigInt&>(*this);

	int size_rhs = rhs.parts.size();
	for (int i = 0; i < size_rhs; i++) {
		sum.increase_digit(i, rhs.parts[i]);
	}

	return sum;
}

ostream& operator<<(ostream& os, const BigInt& bi) {
	os.fill('0');
	for (auto pg = bi.parts.rbegin(); pg != bi.parts.rend(); pg++) {
		if (pg == bi.parts.rbegin()) {
			os << *pg;
		}
		else {
			os << std::setw(4) << *pg;
		}
	}
	return os;
}

void lr1() {
	BigInt a(21);
	BigInt b(131);
	a = a.pow(21);
	b = b.pow(41);
	BigInt c = a + b;
	std::cout << c.pow(2) << std::endl;
}