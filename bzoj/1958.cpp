/*
   Step 1：首先Dfs出针对每一层的所有放置情况，先不管颜色，只记录放与不放和块数。
   
   Step 2：然后从1到n向上递推，注意要顺推，这样转移更加方便，推的时候要注意两点：
	  	1.积木不能悬空
		2.要保证和看到的颜色相符
   	   这两个性质可以写两个函数判断一下，觉得写成成员函数更加方便一些。然后对于每一层，能看到的积木的颜色肯定能确定，然后假设m个不能看到，那该层的方案数就是3^m。
   Step 3: 最后结果就是第h层的所有状态方案数之和

   Hint : 
   	   1.注意long long类型，以及int的转化
	   2.压状态时的为运算就写成宏吧
	   3.状态写成一个类，然后直接成员函数更新状态
     	   4.此程序里，x表示行，y表示列
*/

#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
namespace Solve {
	const int MAXN = 6;
	const int Len = 6;
	const int SUMSTATUS = 6500;
	const int nGrid = 36;
	typedef long long Int64;

	#define LL "%lld"
	#define Set(R, C) (1ll << ((R) * Len + (C)))
	struct Point{int R, C;};
	struct Status {
		int a[MAXN][MAXN];
		int RowLook[MAXN], ColLook[MAXN];
		Int64 S; Point Piece[nGrid];
		int nPiece;
		inline void Look(void) {
			for (int Row = 0; Row < Len; Row++) {
				RowLook[Row] = -1;
				for (int Col = Len - 1; Col >= 0; Col--)
					if (a[Row][Col] != 0) {
						RowLook[Row] = a[Row][Col];
						break;
					}
			}
			for (int Col = 0; Col < Len; Col++) {
				ColLook[Col] = -1;
				for (int Row = Len - 1; Row >= 0; Row--)
					if (a[Row][Col] != 0) {
						ColLook[Col] = a[Row][Col];
						break;
					}
			}
		}
		inline void GetPiece(void);
	};
	
	Status List[SUMSTATUS]; int nStatus;
	char L[MAXN + 1][MAXN + 1], R[MAXN + 1][MAXN + 1];
	int n, map[255];

	void Input(void) {
		scanf("%d\n", &n);
		for (int i = n; i >= 1; i--) scanf("%s\n", L[i]);
		for (int i = n; i >= 1; i--) scanf("%s\n", R[i]), std::reverse(R[i], R[i] + Len);
	}

	int hash[MAXN][MAXN];
	inline void Status::GetPiece (void) {
		bool vis[MAXN][MAXN] = {0};
		for (int i = 0; i < Len; i++) for (int j = 0; j < Len; j++) if (!vis[i][j] && hash[i][j]) {
			vis[i][j] = vis[i + 1][j] = vis[i][j + 1] = vis[i + 1][j + 1] = true;
			Piece[hash[i][j]].R = i, Piece[hash[i][j]].C = j;
		}
	}

	void Dfs(int N, int Row, int Col, Int64 Now) {
		if (Col == Len) Col = 0, Row++;
		if (Row < 0 || Row >= Len || Col < 0 || Col >= Len) {
			Status &S = List[++nStatus];
			S.nPiece = N - 1;
			memcpy(S.a, hash, sizeof hash);
			S.S = Now;
			List[nStatus].Look();
			List[nStatus].GetPiece();
			return;
		}

		//Nothing
		Dfs(N, Row, Col + 1, Now);

		//Put it at here (if it's OK)
		if (!hash[Row][Col] && !hash[Row][Col + 1] && Row + 1 < Len && Col + 1 < Len) {
			hash[Row][Col] = hash[Row + 1][Col] = hash[Row][Col + 1] = hash[Row + 1][Col + 1] = N;
			Int64 It = Now;
			It = Now | Set(Row, Col) | Set(Row + 1, Col) | Set(Row, Col + 1) | Set(Row + 1, Col + 1);
			Dfs(N + 1, Row, Col + 1, It);
			hash[Row][Col] = hash[Row + 1][Col] = hash[Row][Col + 1] = hash[Row + 1][Col + 1] = 0;
		}
	}

	Int64 f[MAXN + 1][SUMSTATUS]; bool In[MAXN + 1][SUMSTATUS];
	Int64 pow[50];
	
	inline int See(const Status& now, char L[], char R[]) {
		int color[36] = {0};
		for (int Row = 0; Row < Len; Row++) {
			int tmp = now.RowLook[Row];
			if (tmp == -1) if (R[Row] != '.') return -1; else continue;
			if (tmp != -1 && R[Row] == '.') return -1;
			if (color[tmp] == 0 || color[tmp] == R[Row])
				color[tmp] = R[Row];
			else return -1;
		}
		for (int Col = 0; Col < Len; Col++) {
			int tmp = now.ColLook[Col];
			if (tmp == -1) if ( L[Col] != '.') return -1; else continue;
			if (tmp != -1 && L[Col] == '.') return -1;
			if (color[tmp] == 0 || color[tmp] == L[Col])
				color[tmp] = L[Col];
			else return -1;
		}
		int ret = 0;
		for (int i = 1; i <= now.nPiece; i++) if (!color[i]) ret++;
		return pow[ret];
	}

	inline bool Check(const Status& D, const Status& U) {
		for (int i = 1; i <= U.nPiece; i++) {
			int R = U.Piece[i].R, C = U.Piece[i].C;
			if (!(D.a[R][C] || D.a[R + 1][C] || D.a[R][C + 1] || D.a[R + 1][C + 1])) return false;
		}
		return true;
	}

	int ID[7][SUMSTATUS], Num[7];
	void Dp(void) {
		f[0][nStatus] = 1; //The nStatus-th status is full.

		ID[0][1] = nStatus; Num[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int now = 1; now <= nStatus; now++) {
				int tmp = See(List[now], L[i], R[i]);
				if (tmp == -1) continue;
				ID[i][++Num[i]] = now;
				for (int j = 1; j <= Num[i - 1]; j++) {
					int pre = ID[i - 1][j];
					if (Check(List[pre], List[now])) {
						f[i][now] += f[i - 1][pre] * tmp;
					}
				}
			}
		}
		Int64 Ans = 0;
		for (int i = 1; i <= nStatus; i++) Ans += f[n][i];
		printf(LL "\n", Ans);
	}

	inline void GetPow(void) {
		pow[0] = 1;
		for (int i = 1; i <= 10; i++)
			pow[i] = pow[i - 1] * 3;
	}
	void solve(void) {
		Input();
		GetPow();
		Dfs(1, 0, 0, 0);
		Dp();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
