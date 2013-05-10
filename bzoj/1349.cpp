#include <cmath>
#include <iostream>
int main(int argc, char** argv) {
	unsigned long long a;
	std::cin >> a;
	std::cout <<(unsigned long long)(ceil(sqrt(a)))<<'\n';
	return 0;
}
