#include <cstdio>
#include <iostream>
#include <cctype>

using namespace std;

const int MAXN = 3000010;
typedef long long Int64;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Node {
	Node *ch[2]; int size;
}POOL[MAXN], *stack[MAXN], Tnull, *null = &Tnull; int top = 0;

inline Node *Renew(void) {
	Node *ret = stack[top--];
	ret->ch[0] = ret->ch[1] = null; ret->size = 1;
	return ret;
}

inline void Delete(Node *x) {
	stack[++top] = x;
}

int n; Int64 revL = 0, revR = 0, Ans = 0;

Node* Build(int n, int x) {
	Node *tmp = Renew();
	if (n == 1) return tmp;
	int mid = n >> 1, d = x > mid;
	tmp->ch[d] = Build(d ? n - mid : mid, x - mid * d);
	return tmp;
}

Node* Merge(Node *l, Node *r) {
	if (l == null) return r;
	if (r == null) return l;
	revL += (Int64) l->ch[1]->size * r->ch[0]->size;
	revR += (Int64) l->ch[0]->size * r->ch[1]->size;
	Node *ret = Renew();
	ret->size = l->size + r->size;
	ret->ch[0] = Merge(l->ch[0], r->ch[0]);
	ret->ch[1] = Merge(l->ch[1], r->ch[1]);
	Delete(l); Delete(r);
	return ret;
}

Node* Dfs(void) {
	int val = ScanInt();
	if (val) return Build(n, val); else {
		Node *ret = Merge(Dfs(), Dfs());
		Ans += min(revL, revR);
		revL = revR = 0;
		return ret;
	}
}

int main(void) {
//	freopen("in", "r", stdin);
	n = ScanInt();
	for (int i = 0; i < MAXN; i++) stack[i] = POOL + i; top = MAXN - 1;
	Dfs();
	cout <<Ans<<endl;
	return 0;
}

