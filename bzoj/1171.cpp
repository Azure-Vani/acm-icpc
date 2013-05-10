//#define Debug
#include <map>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
#include <list>
#include <cassert>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
const int MAXN = 250050;
int s[MAXN], f[MAXN], cur, L;
namespace DATA {
	const int inf = 100000000;
	struct Node {
		Node* ch[2]; int l, r, Min;
		std::list<int> T;

		void Build(int, int);
		void Insert(int, int);
		void Delete(int, int);
		int Ask(int, int);
		inline int Get(void) {
			if (T.empty()) return inf; else return f[T.front()];
		}
		inline void Maintrain(void) {
			while (!T.empty() && s[cur] - s[T.front()] > L) T.pop_front();
		}
		inline void Add(void) {
			while (!T.empty() && f[T.back()] >= f[cur]) T.pop_back();
			T.push_back(cur);
		}
		inline void Updata(void) {
			Min = Get();
			if (ch[0]) Min = min(Min, min(ch[0]->Min, ch[1]->Min));
		}
	};

	int Node::Ask(int L, int R) {
		if (L > R) return inf;
		if (L <= l && r <= R) return Min;
		int mid = (l + r) >> 1;
		int Lret = ch[0]->Ask(L, min(mid, R));
		int Rret = ch[1]->Ask(max(L, mid + 1), R);
		int tmp = Get();
		return min(Lret, min(tmp, Rret));
	}
	void Node::Build(int L, int R) {
		int mid = (L + R) >> 1;
		l = L, r = R, Min = inf, ch[0] = ch[1] = NULL, T.clear();
		if (l == r) return;
		ch[0] = new Node; ch[0]->Build(L, mid);
		ch[1] = new Node; ch[1]->Build(mid + 1, R);
	}


	void Node::Insert(int L, int R) {
		if (L > R) return;
		if (L <= l && r <= R) {
			Add();
			Updata();
			return;
		}
		int mid = (l + r) >> 1;
		ch[0]->Insert(L, min(mid, R));
		ch[1]->Insert(max(mid + 1, L), R);
		Updata();
	}

	void Node::Delete(int L, int R) {
		if (L > R) return;
		if (L <= l && r <= R) {
			Maintrain();
			Updata();
			return;
		}
		int mid = (l + r) >> 1;
		ch[0]->Delete(L, min(mid, R));
		ch[1]->Delete(max(mid + 1, L), R);
		Updata();
	}

	class SegmentTree{public:
		Node *root;
		SegmentTree(){root = new Node;};
		void Set(int n) {root->Build(1, n);}
		void Insert(int l, int r) {root->Insert(l, r);}
		void Delete(int l, int r) {root->Delete(l, r);}
		int Ask(int l, int r) {return root->Ask(l, r);}
	};
}
namespace Solve {
	typedef std::set<int> II;
	typedef std::map<int, int> VI;

	int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	int n, x[MAXN], y[MAXN], l = 1;
	II T;
	VI Q;
	
	void Input(void) {
		n = ScanInt(), L = ScanInt();
		for (int i = 2; i <= n; i++) T.insert(x[i] = ScanInt()), T.insert(y[i] = ScanInt()), s[i] = ScanInt();
		II::iterator it;
		for (it = T.begin(); it != T.end(); it++, l++)
			Q[*it] = l;l--;
		for (int i = 1; i <= n; i++) x[i] = Q[x[i]], y[i] = Q[y[i]];
	}

	DATA::SegmentTree T_T;
	inline void Cal(int u) {
		int now = T_T.Ask(x[u], y[u]);
		if (now >= DATA::inf) {f[u] = -1; return;}
		f[u] = now + 1;
		T_T.Insert(x[u], y[u]);
	}

	int Left = 1;
	inline void Adjust(int u) {
		while (s[u] - s[Left] > L) {
			T_T.Delete(x[Left], y[Left]);
			Left++;
		}
	}
	void solve(void) {
		Input();
		T_T.Set(l);
		cur = 1;
		T_T.Insert(1, l);
		x[1] = 1, y[1] = l;
		for (int i = 2; i <= n; i++) {
			cur = i;
			Adjust(i);
			Cal(i);
		}
		for (int i = 2; i <= n; i++)
			printf("%d\n", f[i]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
