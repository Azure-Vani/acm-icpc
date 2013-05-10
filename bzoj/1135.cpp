//#define Debug
#include <cstdio>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 200020;
	const int inf = 1050000000;
	
	int n, m; Int64 k, d;
	struct Node {
		int l, r; Node* ch[2];
		Int64 lmax, rmax, max, sum;
		Node(){lmax = rmax = max = sum = -k; ch[0] = ch[1] = NULL;}
		inline void Updata(void) {
			lmax = std::max(ch[0]->lmax, ch[0]->sum + ch[1]->lmax);
			rmax = std::max(ch[1]->rmax, ch[1]->sum + ch[0]->rmax);
			max  = std::max(std::max(ch[1]->max,  ch[0]->max), ch[0]->rmax + ch[1]->lmax);
			sum = ch[0]->sum + ch[1]->sum;
		}
		void Build(int L, int R) {
			l = L, r = R;
			if (L == R) return;
			int mid = (l + r) >> 1;
			(ch[0] = new Node)->Build(l, mid);
			(ch[1] = new Node)->Build(mid + 1, r);
			Updata();
		}
		void Insert(int h, int k) {
			if (l == r) {lmax = rmax = max = (sum += k); return;}
			int mid = (l + r) >> 1;
			if (h <= mid) ch[0]->Insert(h, k);
			else ch[1]->Insert(h, k);
			Updata();
		}
	}*root;
	
	void solve(void) {
		scanf("%d%d" LL LL, &n, &m, &k, &d);
		root = new Node;
		root->Build(1, n);
		for (int i = 1, x ,y; i <= m; i++) {
			scanf("%d%d", &x, &y);
			root->Insert(x, y);
			puts(root->max <= d * k ? "TAK":"NIE");
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
