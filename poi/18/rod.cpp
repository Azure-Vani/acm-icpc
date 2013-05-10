#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

const int MAXN = 3000010;

long long Ans = 0, Lrev = 0, Rrev = 0;

inline int clz(int x) {
	return !x?-1:31 - __builtin_clz(x);
}

struct Node {
	Node *l, *r; 
	int size, low, high; 
	char i;
};

Node POOL[MAXN], *stack[MAXN], Tnull, *null = &Tnull; int top;

inline Node* getnew(int x, int s = 1) {
	Node *ret = stack[top--];
	ret->l = ret->r = null; ret->size = s; ret->low = ret->high = x; ret->i = -1;
	return ret;
}
inline Node* getnew(Node *L, Node *R) {
	Node *ret = stack[top--];
	ret->l = L, ret->r = R; ret->size = L->size + R->size; ret->low = L->low, ret->high = R->high; ret->i = clz(ret->low ^ ret->high);
	return ret;
}
inline void Delete(Node *x) {
	stack[++top] = x;
}

inline Node* merge(Node *L, Node *R) {
	if (L == null) return R;
	if (R == null) return L;
	int v = clz(min(L->low, R->low) ^ max(L->high, R->high));
	if (v != L->i && v != R->i) 
		return L->low<R->low?(Rrev += (long long)R->size * L->size, getnew(L, R))
			:(Lrev += (long long)L->size * R->size, getnew(R, L));
	if (L->i == R->i) {
		Node *ll = L->l, *lr = L->r, *rl = R->l, *rr = R->r;
		Delete(L); Delete(R);
		Lrev += (long long)lr->size * rl->size;
		Rrev += (long long)rr->size * ll->size;
		return getnew(merge(ll, rl), merge(lr, rr));
	}
	long long *Lt = &Lrev, *Rt = &Rrev; bool rev = 0;
	if (R->i > L->i) swap(L, R), swap(Lt, Rt), rev = 1;
	Node *l = L->l, *r = L->r; char t = L->i; Delete(L);
	if (R->low & (1 << t)) return *Rt += (long long)R->size * l->size, getnew(l, merge(rev?R:r, rev?r:R));
	else return *Lt += (long long)R->size * r->size, getnew(merge(rev?R:l, rev?l:R), r);
}

inline Node* Dfs(void) {
	int tmp = ScanInt();
	if (tmp) {
		return getnew(tmp);
	} else {
		Node *l = Dfs();
		Node *r = Dfs();
		Lrev = 0, Rrev = 0;
		Node* ret = merge(l, r);
		Ans += min(Lrev, Rrev);
		return ret;
	}
}

int main(void) {
//	freopen("in", "r", stdin);
	ScanInt();
	for (int i = 0; i < MAXN; i++) stack[i] = POOL + i; top = MAXN - 1;
	Dfs();
	cout <<Ans<<endl;
	return 0;
}

