#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1000050;
int n, m; long double f[MAXN], g[MAXN], delta, Sf, Sg;

int main(int argc, char** argv) {
	cin >> n >> m;
	g[1] = double(m - 1) / double(m), delta = 1.0 / double(m), Sg = g[1];
	for (int i = 2; i < n; i++) {
		delta /= m;
		Sg = (Sg + g[i - 1] * (m - 2) + f[i - 1] * (m - 1)) / m;
		g[i] = g[i - 1] / m+ Sg;
		Sf = (Sf + g[i - 1]) / m;
		f[i] = Sf + f[i - 1] / m;
	}
	long double Ans = delta * n, now = 1;
	for (int i = 1; i < n; i++, now /= m) Ans += g[n - i] * i * i * now;
	cout.precision(5);
	cout << fixed << Ans << endl;
	return 0;
}
