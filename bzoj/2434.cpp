#define STDIO
#define INPUT "type.in"
#define OUTPUT "type.out"

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
namespace Solve {
	const int MAXN = 100010;

	int n, m, cnt, nNode; char str[MAXN];

	struct TrieNode {
		TrieNode *ch[26], *p, *fail; int index, lab;
		TrieNode(TrieNode *p, int lab):p(p),index(0), lab(lab){}
	}*root;

	struct Edge {
		int y, index; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*ask[MAXN], *a[MAXN];
	inline void AddEdge(int x, int y) {
		a[x] = new Edge(y, a[x]);
	}

	int fim[MAXN];
	inline void Input(FILE *fin, FILE *fout) {
		fscanf(fin, "%s", str);
		int len = strlen(str);
		TrieNode *tmp = root = new TrieNode(NULL, ++nNode);
		cnt = 0;
		for (int i = 0; i < len; i++) {
			register char c = str[i];
			if (islower(c)) {
				tmp->ch[c - 'a'] = new TrieNode(tmp, ++nNode);
				tmp = tmp->ch[c - 'a'];
			}
			if (c == 'B')
				tmp = tmp->p;
			if (c == 'P')
				fim[tmp->index = ++cnt] = tmp->lab;
		}
		fscanf(fin, "%d", &m);
		for (int i = 1; i <= m; i++) {
			register int x, y;
			fscanf(fin, "%d%d", &x, &y);
			ask[y] = new Edge(x, ask[y]);
			ask[y]->index = i;
		}
	}

	TrieNode* d[MAXN];

	inline void MakeAC(void) {
		int head = 1, tail = 0;
		for (int i = 0; i < 26; i++)
			if (root->ch[i] != NULL) {
				(d[++tail] = root->ch[i])->fail = root;
				AddEdge(root->lab, root->ch[i]->lab);
			}

		while (head <= tail) {
			TrieNode *now = d[head++];
			for (int i = 0; i < 26; i++) if (now->ch[i] != NULL) {
				TrieNode *tmp = now->fail;
				d[++tail] = now->ch[i];
				while (tmp != root && tmp->ch[i] == NULL) tmp = tmp->fail;
				if (tmp->ch[i] != NULL) tmp = tmp->ch[i];
				now->ch[i]->fail = tmp;
				AddEdge(tmp->lab, now->ch[i]->lab);
			}
		}
	}

	struct Intreval {
		int l, r;
	}I[MAXN << 1]; int tim = 0;
	
	inline void Dfs(int u) {
		I[u].l = ++tim;
		for (Edge *p = a[u]; p; p = p->next)
			Dfs(p->y);
		I[u].r = ++tim;
	}
	
	int C[MAXN << 1];
	inline void Add(int t, int u) {
		for (;t<=tim;t+=t&-t) C[t] += u;
	}
	inline int Cal(int t) {
		int ret = 0;
		for (;t;t-=t&-t) ret+=C[t];
		return ret;
	}

	int Ans[MAXN];

	inline void Work(TrieNode *now) {
		int pos = now->lab;
		for (Edge *p = ask[now->index]; p; p = p->next) {
			Ans[p->index] = Cal(I[fim[p->y]].r);
			Ans[p->index] -= Cal(I[fim[p->y]].l - 1);
		}
		for (int i = 0; i < 26; i++)
			if (now->ch[i] != NULL) {
				Add(I[now->ch[i]->lab].l, 1);
				Work(now->ch[i]);
				Add(I[now->ch[i]->lab].l, -1);
			}
	}

	void solve(FILE *fin, FILE *fout) {
		Input(fin, fout);
		MakeAC();
		Dfs(1);
		Work(root);
		for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
	}
}

int main(int argc, char* argv[]) {
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
	     *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
}