//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
namespace Solve {
	typedef unsigned long long Int64;
	const int MAXN = 100050;
	const int Base = 13331;
	const int plen = 6000;
	const int MAXQ = plen + 3;

	Int64 pow[MAXN];

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline int ScanChr(void) {
		int c;
		while (c = getchar(), c == ' ' || c == '\n' || c == '\r') {}
		return c;
	}
	inline int ScanStr(int a[]) {
		int c;
		while (c = getchar(), c == ' ' || c == '\n' || c == '\r') {}
		a[0] = c;
		int l = 1;
		while (c = getchar(), c != ' ' && c != '\n' && c != '\r') a[l++] = c;
		return l;
	}

	class Node {public:
		Node *next, *prev;
		int size, a[MAXQ]; Int64 hash[MAXQ];
		
		inline void Set(int*, int);
		Node():size(0){memset(a, 0, sizeof a); memset(hash, 0, sizeof hash);}

		inline void Remove(int l, int r) {
			for (int i = l, j = r + 1; j <= size; i++, j++)
				a[i] = a[j];
			size -= r - l + 1;
			for (int i = l; i <= size; i++) hash[i] = hash[i - 1] * Base + a[i];
		}

		inline void Divide(int now) {
			if (now == size) return;
			Node *t = new Node;
			t->Set(a + now + 1, size - now);
			t->next = next, t->prev = this;
			next->prev = t, next = t;
			size = now;
		}
		
		inline Int64 GetHash(int l, int r) {
			return hash[r] - hash[l - 1] * pow[r - l + 1];
		}
		inline void Add(Node *t) {
			t->next = next, t->prev = this;
			next->prev = t, next = t;
		}
		inline bool Union(void);
	}*root, Tnull, *null = &Tnull;

	inline void Node::Set(int c[], int n) {
		memset(hash, 0, sizeof hash); memset(a, 0, sizeof a);
		next = prev = null;
		for (int i = 1; i <= n; i++)
			hash[i] = hash[i - 1] * Base + (a[i] = c[i - 1]);
		size = n;
	}
	
	inline bool Node::Union(void) {
		if (next == null || size + next->size > plen) return false;
		for (int i = size + 1, j = 1; j <= next->size; i++, j++)
			hash[i] = hash[i - 1] * Base + (a[i] = next->a[j]);
		size += next->size;
		next->next->prev = this;
		next = next->next;
		return true;
	}

	inline Node* Pos(int t, int &ret) {
		ret = 0;
		for (Node *p = root; p != null;ret += p->size, p = p->next)
			if (ret + p->size >= t) return p;
	}

	inline void Insert(int now, int a[], int n) {
		int sum;
		Node *t = Pos(now, sum);
		t->Divide(now - sum);
		for (int L = 1, R; L <= n; L = R + 1) {
			R = std::min(n, L + plen - 1);
			Node *tmp = new Node;
			tmp->Set(a + L, R - L + 1);
			t->Add(tmp);
			if (!t->Union()) t = t->next;
		}
		t->Union();
	}

	inline void Delete(int l, int r) {
		int sum1, sum2;
		Node* L = Pos(l, sum1);
		Node* R = Pos(r, sum2);
		if (L == R) {
			L->Remove(l - sum1, r - sum1);
			return;
		}
		L->next = R, R->prev = L;
		L->Remove(l - sum1, L->size);
		R->Remove(1, r - sum2);
		L->Union();
		R->Union();
	}

	inline Int64 GetHash(int l, int r) {
		if (l > r) return 0;
		int sum1, sum2;
		Node *L = Pos(l, sum1);
		Node *R = Pos(r, sum2);
		if (L == R) {
			return L->GetHash(l - sum1, r - sum1);
		}
		Int64 ret = L->GetHash(l - sum1, L->size);
		for (Node *p = L->next; p != R; p = p->next) 
			ret = ret * pow[p->size] + p->hash[p->size];
		ret = ret * pow[r - sum2] + R->hash[r - sum2];
		return ret;
	}

	int Len;
	inline int Ask(int a, int b) {
		int l = 0, r = Len - b + 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			Int64 t1 = GetHash(a, a + mid - 1);
			Int64 t2 = GetHash(b, b + mid - 1);
			if (t1 == t2)
				l = mid + 1;
			else
				r = mid - 1;
		}
		return r;
	}

	int a[MAXN], n, Q;
	void Input(void) {
		Len = n = ScanInt(), Q = ScanInt();
		ScanStr(a + 1);
		root = new Node;
		root->next = root->prev = null;
		Insert(0, a, n); pow[0] = 1;
		for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * Base;
	}

	void solve(void) {
		Input();
		for (int i = 1; i <= Q; i++) {
			int type = ScanChr();
			if (type == 'L') {
				int l = ScanInt(), r = ScanInt();
				if (l > r) std::swap(l, r);
				int t = Ask(l, r);
				printf("%d\n", t);
			}else
			if (type == 'A') {
				int now = ScanInt(), tmp = ScanStr(a + 1); now--;
				Len += tmp;
				Insert(now, a, tmp);
			}else
			if (type == 'D') {
				int l = ScanInt(), r = ScanInt();
				Len -= r - l + 1;
				Delete(l, r);
			}else
			if (type == 'C') {
				int l = ScanInt(), r = ScanInt();
				Delete(l , r);
				int tmp = ScanStr(a + 1);
				Insert(l - 1, a, tmp);
			}
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
