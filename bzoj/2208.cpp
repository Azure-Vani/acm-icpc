//#define Debug
#include <cstdio>
#include <algorithm>
namespace DataOrg {
	const int MAXN = 40;
	const int BASE = 60;

	typedef long long ll;
	struct Node {
		ll Interval[MAXN];int l, Num;
		void Renew(const Node& a) {
			for (int i = 1; i <= a.l; i++)
				Interval[i] |= a.Interval[i];
			l = std::max(l, a.l);
		}
		void Set(int i) {
			int where = i / BASE, delta = i % BASE;
			Interval[where + 1] |= (1ll << delta);
			l = std::max(where + 1, l);
		}
		int GetSum(int Sum[]) {
			int ret = 0, v = 0;
			for (int i = 1; i <= l; i++, v += BASE) {
				ll Temp = Interval[i], now = 0;
				while (Temp) {
					if (Temp & 1)
						ret += Num * Sum[now + v];
					Temp >>= 1;
					now++;
				}
			}
			return ret;
		}
	};
}

namespace Solve {
	const int MAXN = 2005;
	int n;
	char ch[MAXN];

	struct Edge {
		int y; Edge* next;
		Edge(int y, Edge* next):y(y), next(next){}
	}*a[MAXN], *e[MAXN];

	void Input(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) {
			gets(ch);
			for (int j = 0; j < n; j++)
				if (ch[j] == '1') 
					a[i] = new Edge(j + 1, a[i]);
		}
	}

	int Low[MAXN], Time[MAXN], Tim = 0, Belong[MAXN], Sum = 0, NumScc[MAXN];
	int Stack[MAXN], Top = 0;
	bool In_Stack[MAXN] = {0};

	void Tarjan(int u) {
		Low[u] = Time[u] = ++Tim;
		In_Stack[Stack[++Top] = u] = true;

		for (Edge* p = a[u]; p;p = p->next)
			if (!Time[p->y]) {
				Tarjan(p->y);
				Low[u] = std::min(Low[u], Low[p->y]);
			}else if (In_Stack[p->y]) Low[u] = std::min(Low[u], Time[p->y]);

		if (Low[u] == Time[u]) {
			Sum++;
			int t;
			do {
				t = Stack[Top--];
				In_Stack[t] = false;
				Belong[t] = Sum;
				NumScc[Sum]++;
			}while (t != u);
		}
	}

	int Inp[MAXN];
	void Connect(void) {
		for (int i = 1; i <= n; i++)
			for (Edge* p = a[i]; p; p = p->next)
				if (Belong[i] != Belong[p->y])
					e[Belong[p->y]] = new Edge(Belong[i], e[Belong[p->y]]), Inp[Belong[i]]++;
	}

	int d[MAXN], head = 1, tail = 0;
	DataOrg::Node f[MAXN];

	int TopSort_Dp(void) {
		n = Sum;
		for (int i = 1; i <= n; i++) {
			f[i].Num = NumScc[i];
			f[i].Set(i);
			if (!Inp[i])
				d[++tail] = i;
		}

		while (head <= tail) {
			int now = d[head++];
			for (Edge* p = e[now]; p; p = p->next) {
				int t = p->y;
				f[t].Renew(f[now]);
				if (!--Inp[t]) d[++tail] = t;
			}
		}

		int Ret = 0;
		for (int i = 1; i <= n; i++)
			Ret += f[i].GetSum(NumScc);
		
		return Ret;
	}

	void solve(void) {
		Input();
		for (int i = 1; i <= n; i++)
			if (!Time[i])
				Tarjan(i);
		Connect();
		int Ret = TopSort_Dp();
		printf("%d\n", Ret);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
