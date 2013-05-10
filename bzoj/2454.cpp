#include <vector> 
#include <algorithm> 
#include <cstdio> 
#include <cstring>

typedef long long Int64;

using namespace std; 

const Int64 Mod = 1000000007ll;
Int64 f[150][150][150];

class RabbitPuzzle {
	public:
	typedef vector<long long> V;
	
	V goup(V now) {
		Int64 L = now[1] - now[0], R = now[2] - now[1];
		if (L < R) {
			Int64 t = now[1];
			now[1] += L;
			now[0] = t;
		}
		if (L > R) {
			Int64 t = now[1];
			now[1] -= R;
			now[2] = t;
		}
		if (L == R) return V();
		else return now;
	}

	inline void Add(Int64 &a, Int64 b) {
		a = (a + b) % Mod;
	}

	vector<V> List;

	int theCount(vector<long long> rabbits, vector<long long> nests, int K) {
		List.clear(); memset(f, 0, sizeof f);
		V y = nests;
		int res_d = -1, res_t, limit = 0;
		for (int i = 0; i <= K && !nests.empty(); i++, nests = goup(nests)) {
			List.push_back(nests);
		}
		for (int i = 0; i <= K && !rabbits.empty(); i++, rabbits = goup(rabbits)) {
			vector<V>::iterator it = find(List.begin(), List.end(), rabbits);
			if (it != List.end()) {
				res_d = i;
				res_t = it - List.begin();
				break;
			}
		}
		if (res_d == -1) return 0;
		while (!y.empty() && limit <= 100) y = goup(y), limit++;
		f[0][0][0] = 1;
		for (register int res = 0; res < K; res++) {
			for (register int t = 0; t <= K; t++) {
				for (register int d = 0; d <= K; d++) if (f[res][t][d]) {
					register Int64 o = f[res][t][d];
					if (d) {
						Add(f[res + 1][t][d - 1], (d != 1 || t == 0) ? (o << 1) : o);
						Add(f[res + 1][t][d + 1], o);
					} else {
						if (t) Add(f[res + 1][t - 1][d], o);
						if (t + 1 < limit) Add(f[res + 1][t + 1][d], o);
						Add(f[res + 1][t][d + 1], o);
					}
				}
			}
		}
		return (int)f[K][res_t][res_d];
	}
	
};
int main(void) {
	RabbitPuzzle test;
	vector<Int64> a(3), b(3); int k;
	for (int i = 0; i <= 2; i++) scanf("%lld", &a[i]);
	for (int i = 0; i <= 2; i++) scanf("%lld", &b[i]); scanf("%d", &k);
	printf("%d\n", test.theCount(a, b, k));
	return 0;
}