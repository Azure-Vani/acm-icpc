//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	typedef unsigned long long Int64;
	const int MAXN = 505;
	int Row_Base = 97;
	int Col_Base = 131;

	int a[MAXN][MAXN], n, m;
	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++, scanf("\n"))
			for (int j = 1; j <= m; j++)
				a[i][j] = getchar() - 'a' + 1;
	}

	Int64 hash[MAXN][MAXN];
	Int64 Row_pow[MAXN], Col_pow[MAXN];

	void Prepare(void) {
		Row_pow[0] = Col_pow[0] = 1;
		for (int i = 1; i <= m; i++) Row_pow[i] = Row_pow[i - 1] * Row_Base;
		for (int i = 1; i <= n; i++) Col_pow[i] = Col_pow[i - 1] * Col_Base;
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++)
				hash[i][j] = hash[i][j - 1] * Row_Base + a[i][j];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				hash[i][j] = hash[i - 1][j] * Col_Base + hash[i][j];
	}

	inline Int64 Cal(int x1, int y1, int x2, int y2) {
		Int64 ret = 0;
		ret = hash[x2][y2] - hash[x1 - 1][y2] * Col_pow[x2 - x1 + 1];
		ret -= hash[x2][y1 - 1] * Row_pow[y2 - y1 + 1];
		ret += hash[x1 - 1][y1 - 1] * Col_pow[x2 - x1 + 1] * Row_pow[y2 - y1 + 1];
		return ret;
	}

	struct Node {
		int x, y;
		Node(){}
		Node(int x, int y):x(x),y(y){}
	}A, B;

	const int Mod = 1200007;

	class Hash {public:
		struct Edge {
			Int64 index; Node value; Edge *next;
			Edge(){}
			Edge(Int64 index, Node value, Edge* next):index(index), value(value), next(next){}
			void* operator new(size_t, void* p) {return p;}
		}*a[Mod], Pool[MAXN * MAXN], *sid;
		Hash():sid(Pool){}

		inline void Push(Int64 index, int x, int y) {
			Int64 t = index % Mod;
			a[t] = new((void*)sid++) Edge(index, Node(x, y), a[t]);
		}

		inline Node Find(Int64 index) {
			Int64 t = index % Mod;
			for (Edge *p = a[t]; p; p = p->next)
				if (p->index == index)
					return p->value;
			return Node(-1, -1);
		}

		inline void clear(void) {
			sid = Pool;
			memset(a, NULL, sizeof a);
			memset(Pool, 0, sizeof Pool);
		}
	}T;

	inline bool Check(int L) {
		T.clear();
		for (int i = 1; i + L - 1 <= n; i++)
			for (int j = 1; j + L - 1<= m; j++) {
				Int64 tmp = Cal(i, j, i + L - 1, j + L - 1);
				Node ret = T.Find(tmp);
				if (ret.x != -1) {
					A = ret, B = Node(i, j);
					return true;
				}
				T.Push(tmp, i, j);
			}
		return false;
	}

	inline void Work(void) {
		int l = 0, r = std::min(n, m);
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Check(mid))
				l = mid + 1;
			else
				r = mid - 1;
		}
		printf("%d\n", r);
/*		if (r)
			printf("%d %d\n%d %d\n", A.x, A.y, B.x, B.y);*/
	}

	inline void solve(void) {
		Input();
		Prepare();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
