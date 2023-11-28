#include <iostream>
#include "bigint.h"
#include <algorithm>
#include <execution>
#include <random>

bool is_prime(BigInt num) {
	for (BigInt i = 2; i <= num.sqrt(); i += 1) \
		if (num % i == 0)
			return false;
	return true;
}

bool is_coprime(BigInt num1, BigInt num2) {
	return true;
}
BigInt gen_coprime(BigInt num) {
	return num;
}

void lr_1() {
	BigInt a("17");
	//a = a.pow(82589933) - 1;
	std::cout << is_prime(a);
}

BigInt gen_prime(int bit_size) {
	BigInt num;
	do {
		num = num.random_bits(bit_size, [](uint8_t* bytes, size_t n_bytes) {
			for (size_t i = 0; i < n_bytes; i++)
			{
				bytes[i] = rand();
			}});
	} while (!is_prime(num));
	return num;
}

void lr_2() {
	BigInt p = gen_prime(1024);
	BigInt q = gen_prime(1024);
	BigInt n = p * q;
	BigInt fi = (p - 1) * (q - 1);
	BigInt e = gen_coprime(fi);
}

int main()
{
	lr_2();
}