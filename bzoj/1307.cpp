#include <cstdio>
#include <cctype>
namespace Solve {
	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	int x, n, k;
	void Input(void) {n = ScanInt();while(n--) x < (k = ScanInt()) ? x = k : 0; printf("%d\n", x); }
}
int main(int argc, char** argv) {
	Solve::Input();
	return 0;
}
