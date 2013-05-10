//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>

namespace Solve {
	typedef long long int64;
	typedef std::pair<int64, int> II;
	#ifdef Debug
		#define LL "%I64d"
	#else
		#define LL "%lld"
	#endif
	const int MAXN = 100050;
	const int MAXM = 400050;
	const int64 inf = 100000000000000000ll;
	
	inline int ScanInt(void) {
		int r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct Edge {
		int y, z; Edge* next;
		Edge(){}
		Edge(int y, int z, Edge* next):y(y), z(z), next(next) {}
		void* operator new(size_t, void* p) {return p;}
	}*a[MAXN], POOL[MAXM], *data = POOL;
	
	int n, m, pb, p1, p2;
	
	void Input(void) {
		m = ScanInt(), n = ScanInt(), pb = ScanInt(), p1 = ScanInt(), p2 = ScanInt();
		while (m--) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new((void*)data++) Edge(y, z, a[x]);
			a[y] = new((void*)data++) Edge(x, z, a[y]);
		}
	}
	
	template <class T> 
	class Heap {
		public:
		T a[MAXN * 5];
		int n;
		
		void Clear(void) {
			n = 0;
		}
		
		void Push(T x) {
			int i = ++n;
			while (i > 1 && x < a[i >> 1]) a[i] = a[i >> 1], i >>= 1;
			a[i] = x;
		}
		
		void Pop(void) {
			T t = a[n--];
			int i = 1, j = 2;
			while (j <= n) {
				if (j < n && a[j + 1] < a[j]) j++;
				if (a[j] < t) {
					a[i] = a[j];
					i = j, j = i << 1;
				}else break;
			}
			a[i] = t;
		}
		T Top(void) {return a[1];}
	};
	
	int64 dis[MAXN];
	Heap<II> T;
	
	int64 Dijkstra(int vs, int vt) {
		for (int i = 0; i <= n; i++) dis[i] = inf;
		dis[vs] = 0;
		T.Clear();
		T.Push(std::make_pair(dis[vs], vs));
		
		for (int i = 1; i < n; i++) {
			II now;
			while (now = T.Top(), dis[now.second] < now.first) {T.Pop();}
			T.Pop();
			for (Edge* p = a[now.second]; p; p = p->next)
				if (dis[p->y] > now.first + p->z)
					T.Push(std::make_pair(dis[p->y] = now.first + p->z, p->y));
		}
		return dis[vt];
	}
	
	int64 Work(void) {
		int64 l1 = Dijkstra(pb, p1); int64 l2 = dis[p2];
		int64 l  = Dijkstra(p1, p2);
		return std::min(l1 + l, l2 + l);
	}
	
	void solve(void) {
		Input();
		printf(LL "\n", Work());
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
