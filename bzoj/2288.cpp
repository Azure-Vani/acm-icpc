//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Data {
	struct Node {
		Node *ch[2]; int l, r;
		int sum;
		int max, lmax, rmax, lwhere, rwhere;
		int min, lmin, rmin, lminwhere, rminwhere;
		int Lc, Rc, cL, cR;
		bool opt;

		void Build(int, int, int*);
		void Updata(void);
		void Pass(void);
		void Reverse(int , int);
		inline void Opt(void);
	};

	void Node::Updata(void) {
		Pass();
		Node& L = *ch[0], &R = *ch[1];
		sum = L.sum + R.sum;

		if (L.lmax > L.sum + R.lmax) {
			lmax = L.lmax;
			lwhere = L.lwhere;
		}else {
			lmax = L.sum + R.lmax;
			lwhere = R.lwhere;
		}
		if (R.rmax > R.sum + L.rmax) {
			rmax = R.rmax;
			rwhere = R.rwhere;
		}else {
			rmax = R.sum + L.rmax;
			rwhere = L.rwhere;
		}
		max = L.rmax + R.lmax; Lc = L.rwhere, Rc = R.lwhere;
		if (max < L.max) max = L.max, Lc = L.Lc, Rc = L.Rc;
		if (max < R.max) max = R.max, Lc = R.Lc, Rc = R.Rc;
		if (Lc > Rc) Lc = l - 1, Rc = r + 1;

		if (L.lmin < L.sum + R.lmin) {
			lmin = L.lmin;
			lminwhere = L.lminwhere;
		}else {
			lmin = L.sum + R.lmin;
			lminwhere = R.lminwhere;
		}
		if (R.rmin < R.sum + L.rmin) {
			rmin = R.rmin;
			rminwhere = R.rminwhere;
		}else {
			rmin = R.sum + L.rmin;
			rminwhere = L.rminwhere;
		}
		min = L.rmin + R.lmin; cL = L.rminwhere, cR = R.lminwhere;
		if (min > L.min) min = L.min, cL = L.cL, cR = L.cR;
		if (min > R.min) min = R.min, cL = R.cL, cR = R.cR;
		if (cL > cR) cL = l - 1, cR = r + 1;
	}

	void Node::Build(int l, int r, int a[]) {
		this->l = l, this->r = r;
		if (l == r) {
			sum = a[l];
			lmax = rmax = max = std::max(0, sum);
			if (max != sum)
				lwhere = l - 1, rwhere = l + 1;
			else 
				lwhere = l, rwhere = r;
			lmin = rmin = min = std::min(0, sum);
			if (min != sum)
				lminwhere = l - 1, rminwhere = l + 1;
			else 
				lminwhere = l, rminwhere = r;
			if (sum > 0) Lc = Rc = l, cL = l - 1, cR = r + 1;
			else cL = cR = l, Lc = l - 1, Rc = r + 1;
			opt = false;
			ch[0] = ch[1] = NULL;
			return;
		}
		int mid = (l + r) >> 1; 
		ch[0] = new Node; ch[0]->Build(l, mid, a);
		ch[1] = new Node; ch[1]->Build(mid + 1, r, a);
		Updata();
	}

	inline void Node::Opt(void) {
		opt ^= 1;
		lmax *= -1, rmax *= -1, lmin *= -1, rmin *= -1, sum *= -1, max *= -1, min *= -1;
		std::swap(lmax, lmin);
		std::swap(rmax, rmin);
		std::swap(max, min);
		std::swap(lwhere, lminwhere);
		std::swap(rwhere, rminwhere);
		std::swap(Lc, cL);
		std::swap(Rc, cR);
	}

	void Node::Pass(void) {
		if (opt) {
			opt ^= 1;
			if (ch[0]) ch[0]->Opt();
			if (ch[1]) ch[1]->Opt();
		}
	}


	void Node::Reverse(int linv, int rinv) {
		if (linv > rinv) return;
		Pass();
		if (linv <= l && r <= rinv) {
			Opt();
			return;
		}
		int mid = (l + r) >> 1;
		ch[0]->Reverse(linv, std::min(rinv, mid));
		ch[1]->Reverse(std::max(linv, mid + 1), rinv);
		Updata();
	}

	class SegTree {
		public:
		Node* root;
		SegTree(){root = new Node;}
		void Make(int a[], int n) {
			root -> Build(1, n, a);
		}
		void Reverse(int l, int r) {
			root->Reverse(l, r);
		}
		int Get(void) {
			int ret = root->max;
			int L = root->Lc, R = root->Rc;
			root->Reverse(L, R);
			return ret;
		}
	};
}
namespace Solve {
	const int MAXN = 100500;

	inline int ScanInt(void) {
		int r = 0, c, flag;
		while (flag = getchar(), flag != '-' && !isdigit(flag)) {}
		if (flag != '-') r = flag - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return flag == '-' ? -r : r;
	}


	int a[MAXN], n, m;
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
	}
	
	Data::SegTree T;
	int Ans;

	void Work(void) {
		T.Make(a, n);
		for (int _ = 1; _ <= m; _++) {
			int Now = T.Get();
			if (Now <= 0) break;
			Ans += Now;
		}
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
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
