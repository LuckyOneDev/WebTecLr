#include <iostream>
#include <fstream>
#include "bigint.h"
#include "rsa.h"
#include "kuzv2.h"
#include "stribog.h"

int main()
{
	//lr1(); // BigInt
	std::ifstream out2("input.txt");
	std::string test_string((std::istreambuf_iterator<char>(out2)),
		std::istreambuf_iterator<char>());
	out2.close();
	//lr2(test_string); // RSA-1024
	//lr2(test_string, 65536); // RSA-65536
	//lr3(test_string); // kuznechik
	lr4(test_string); // stribog

	return 0;
}