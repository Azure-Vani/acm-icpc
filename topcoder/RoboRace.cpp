// BEGIN CUT HERE

// END CUT HERE

#define OJ

#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)
#define In(x, y) ((x) < n && (x) >= 0 && (y) < m && (y) >= 0)

typedef long long Int64;

using namespace std; 

const int MAXN = 2510;
const int MAXM = 51;

int n, m, a[MAXM][MAXM], L;
int f[MAXN][MAXM][MAXM];

class RoboRace {
	public:

	int x1, y1, x2, y2, gx, gy;
	string st;

	int startTime(vector <string> board, vector <string> commands) {
		foreach(it, commands) st += *it;
		n = board.size(), m = board[0].length(), L = st.length();
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= m - 1; j++) {
				if (board[i][j] != '#') a[i][j] = 1;
				if (board[i][j] == 'Y') x1 = i, y1 = j;
				if (board[i][j] == 'F') x2 = i, y2 = j;
				if (board[i][j] == 'X') gx = i, gy = j;
			}
		int ret = -1;
		memset(f[L], 60, sizeof f[L]);
		f[L][gx][gy] = L;
		for (int i = L - 1; i >= 0; i--) {
			int lx = 0, ly = 0;
			if (st[i] == 'N') lx = -1;
			if (st[i] == 'S') lx =  1;
			if (st[i] == 'W') ly = -1;
			if (st[i] == 'E') ly =  1;
			for (int x = 0; x < n; x++) {
				for (int y = 0; y <= m - 1; y++) {
					if (x == gx && y == gy) {
						f[i][x][y] = i;
						continue;
					}
					int nx = x + lx, ny = y + ly;
					f[i][x][y] = f[i + 1][x][y];
					if (!In(nx, ny) || !a[nx][ny]) continue;
					f[i][x][y] = std::min(f[i][x][y], f[i + 1][nx][ny]);
				}
			}
			if (f[i][x1][y1] < f[i][x2][y2]) ret = i;
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"#F",
 "YX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NES"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, startTime(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"########",
 "#......#",
 "#.Y....#",
 "#.F.#..#",
 "#...X..#",
 "#...#..#",
 "#......#",
 "########"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"SSEEESSW"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, startTime(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"########",
 "#......#",
 "#.Y....#",
 "#.F.#..#",
 "#...X..#",
 "#...#..#",
 "#......#",
 "########"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ESSEESSW"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, startTime(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"##.#.#.",
 "..##...",
 "..#...X",
 "Y...##.",
 "#...#.#",
 "..#..F."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"SSSNWSSSEWNSENENENNNNENWNEWESE"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(3, Arg2, startTime(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"#..#.........#...X##....",
 "#........#..........##.#",
 ".#.#........#.....#.#...",
 "..###...#..##.##...#....",
 "..#.#.....#....#.#.####.",
 "#...##.##.##..#.....##..",
 ".##...#.#....#.......#.#",
 "....##.#..#....#....#...",
 "....###.##.....###...#..",
 "#.#.......#.#......#..#.",
 ".##....##.#.##.......#.#",
 "......###...####......#.",
 "..#.##.#..#.#...#...#...",
 ".....#.#..........#...#.",
 "##.#....##F#.....#.##.#.",
 ".##....#.......##.##.##.",
 "..#...#..##....#..#...Y.",
 "#...........#...###..###",
 ".....#...#..#.........#.",
 ".#...##..#.#...#..#.##..",
 "#..#...######....###.#..",
 "#.#.....#.......#.##....",
 "#..#....###....#.#..#...",
 "..#...#.##.##.#.##.##..#",
 "#....##.##..........#..#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NWWSEWSSNWESSWES",
 "ESEEENSNWNNWSNSNWWNWWNNNWE",
 "NSNENENNSEENWWNSNNNNWWSSN",
 "EENEWNWESESEEESNNNSEENNEWNNESNEESSEESEEENENNNWSSW",
 "NWNNWSNWSWSSSSEEWSSWSESWWNNWWENSNNWWSSWWNNE",
 "NWEWNEWSNEN",
 "NNNEWNSWSNWESWNNNSWWNNNWWWNNEWNEEWSSWNSSWWNNWESEWS",
 "WSSSEESSEEEEENNSWEWWWENSENWNSEENES",
 "NNSNESESWNESNENSEESESWSENNESESNESNESEEW",
 "ESNENEENWSNS"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 18; verify_case(4, Arg2, startTime(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RoboRace ___test;  
 	___test.run_test(4); 
	return 0;
}
// END CUT HERE
