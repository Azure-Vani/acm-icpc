//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 3005;

	int n, a[MAXN]; char ch[MAXN];
	void Input(void) {
		scanf("%d\n", &n);
		gets(ch + 1);
		for (int i = 1; i <= n; i++) a[i] = ch[i] - '0';
		a[n + 1] = -1;
	}

	class Node {public:
		Node *ch[2]; int tim;
		Node(){ch[0] = ch[1] = NULL; tim = 0;}
		inline void Insert(int *a) {
			Node *it = this;
			while (*a != -1) {
				if (!it->ch[*a]) it->ch[*a] = new Node;
				it = it->ch[*a];
				it->tim++;
				a++;
			}
		}
		void print(void) {
			if (tim > 1)
				printf("%d\n", tim);
			if (ch[0]) ch[0]->print();
			if (ch[1]) ch[1]->print();
		}
	}*root;

	void solve(void) {
		Input();
		root = new Node;
		for (int i = 1; i <= n; i++) 
			root->Insert(a + i);
		root->tim = 0;
		root->print();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
