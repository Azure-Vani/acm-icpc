#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200010;
const int inf = ~0U>>1;

int n, type[MAXN], a[MAXN], m;
pair<int, int> c[MAXN];

struct Node {
	Node *ch[2]; int l, r, d, Min;
	Node(){ch[0] = ch[1] = 0; d = 0; Min = inf;}
	inline void Lazy(int t) {d += t; Min -= t;}
	inline void Push(void) {if (ch[0] && d) ch[0]->Lazy(d), ch[1]->Lazy(d); d = 0;}
	int Cal(int L, int R) {
		if (L > R) return inf;
		if (L <= l && r <= R) return Min;
		int mid = (l + r) >> 1; Push();
		return min(ch[0]->Cal(L, min(mid, R)), ch[1]->Cal(max(mid + 1, L), R));
	}
	void Sub(int L, int R) {
		if (L > R) return;
		if (L <= l && r <= R) {Lazy(1); return;}
		int mid = (l + r) >> 1; Push();
		ch[0]->Sub(L, min(mid, R)); ch[1]->Sub(max(mid + 1, L), R);
		Min = min(ch[0]->Min, ch[1]->Min);
	}
}*root;

Node* Build(int L, int R) {
	Node *tmp = new Node();
	tmp->l = L, tmp->r = R;
	if (L == R) {
		if (type[L]) tmp->Min = inf; else tmp->Min = a[L];
		return tmp;
	}
	int mid = (L + R) >> 1;
	tmp->ch[0] = Build(L, mid); tmp->ch[1] = Build(mid + 1, R);
	tmp->Min = min(tmp->ch[0]->Min, tmp->ch[1]->Min);
	return tmp;
}

vector<int> stack;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d", &n); type[1] = 1;
	for (int i = 2; i <= n; i++) {
		char tmp[1]; scanf("%s %d", tmp, a + i);
		type[i] = (tmp[0] == 'd');
		if (type[i]) c[++m] = make_pair(a[i], -i);
	}
	sort(c + 1, c + m + 1);
	int Ans = 0; root = Build(1, n);
	for (int i = m; i >= 1; i--) {
		int now = c[i].first, pos = -c[i].second;
		if (root->Cal(pos, n - 1) > 1) {
			Ans += now;
			root->Sub(pos, n);
			stack.push_back(pos);
		}
	}
	sort(stack.begin(), stack.end());
	if ((int)stack.size() >= a[n]) {
		printf("%d\n", Ans);
		printf("%d\n", stack.size()); for (int i = 0; i < (int)stack.size(); i++) printf("%d ", stack[i]); puts("");
	}else puts("-1");
	return 0;
}

