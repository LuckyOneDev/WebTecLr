#include "bigint.h"
#include "rsa.h"
#include "kuzv2.h"
#include "stribog.h"

int main()
{
	std::ifstream inp("input.txt");
	std::string test_string((std::istreambuf_iterator<char>(inp)),
		std::istreambuf_iterator<char>());
	std::ofstream out("output.txt");

	lr1(out); // BigInt
	//lr2(test_string, out); // RSA-1024
	//lr2(test_string, out, 65536); // RSA-65536
	//lr3(test_string, out); // kuznechik
	//lr4(test_string, out); // stribog

	inp.close();
	out.close();
	return 0;
}