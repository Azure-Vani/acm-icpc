#include <algorithm>
#include <set>
#include <queue>
#include <cstdio>
#include <map>
#include <cstring>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define REP(i, l, r) for(int i = l; i <= r; i++)
struct Point {
	int x, y;
	Point(int x, int y):x(x), y(y){}
	Point(){};
	inline int operator ^(const Point& oth) {
		return x * oth.y - y * oth.x;
	}
	inline Point operator +(const Point &oth) {
		Point ret(x + oth.x, y + oth.y);
		return ret;
	}
	inline Point operator -(const Point &oth) {
		Point ret(x - oth.x, y - oth.y);
		return ret;
	}
	inline int operator *(const Point &oth) {
		int ret = x * oth.x + y * oth.y;
		return ret;
	}
	inline bool operator ==(const Point &oth) {
		return x == oth.x && y == oth.y;
	}
}S, T;

struct Line {
	Point s, t;
	inline void Scan(void) {
		scanf("%d%d%d%d", &s.x, &s.y, &t.x, &t.y);
	}
}a[10];

const int N = 66;
int n, m, K, dx[] = {1, 0, -1, 0, 0}, dy[] = {0, -1, 0, 1, 0};
typedef pair<pair<int, int>, pair<int, int> > PP;
map<PP, int> dis;
set<PP> vis;
queue<PP> Q;


inline bool Out(const Point& y1) {
	if (y1.x < 0 || y1.y < 0 || y1.x >= n || y1.y >= m) return true; else return false;
}
/*
inline bool on (Point x1, Point y1, Point a)
{
	return ((a - x1) ^ (a - y1)) == 0 && ((a - x1) * (y1 - x1)) >= 0 && ((a - y1) * (x1 - y1)) >= 0;
}
inline bool intersect (Point x1, Point y1, Point x2, Point y2)
{
	if (x1 == y1 && x2 == y2) return x1 == x2;
	else if (x1 == y1) return on(x2, y2, x1);
	else if (x2 == y2) return on(x1, y1, x2);
	else if (((y1 - x1) ^ (y2 - x2)) == 0)
	{
		return on(x1, y1, x2) || on(x1, y1, y2) || on(x2, y2, x1) || on(x2, y2, y1);
	}
	else
	{
		int q = ((y2 - y1) ^ (x2 - y1)) * ((x2 - x1) ^ (y2 - x1));
		if (q != 0) return q > 0;
	}
}
*/
int test(Point x, Point l, Point r) {
	if (l.x > r.x || l.x == r.x && l.y > r.y) {
		Point t; t = l, l = r, r = t;
	}
	if (l.x == r.x) {
		int t = l.x; l.x = l.y, l.y = t;
		t = r.x, r.x = r.y, r.y = t;
		t = x.x, x.x = x.y, x.y = t;
	}
	if (x.x < l.x) return -2;
	else if (x.x == l.x) return -1;
	else if (x.x == r.x) return 1;
	else if (x.x > r.x) return 2;
	else return 0;
}
int test_intersection(Point l1, Point r1, Point l2, Point r2) {
	if (l1 == r1 && l2 == r2)
		if (l1 == l2) return 1; else return 0;
	else if (l1 == r1) {
		if ((l1 - l2) ^ (r2 - l2)) return 0;
		int f = test(l1, l2, r2);
		if (f == -2 || f == 2) return 0;
		else return 1;
	} else if (l2 == r2) {
		if ((l2 - l1) ^ (r1 - l1)) return 0;
		int f = test(l2, l1, r1);
		if (f == -2 || f == 2) return 0;
		else return 1;
	}
	Point k1 = r1 - l1, k2 = r2 - l2;
	long long x = k1 ^ k2, y = (l2 - l1) ^ k1;
	if (!x && !y) {
		int f1 = test(l2, l1, r1), f2 = test(r2, l1, r1);
		if (f1 < 0 && f2 > 0 || f1 > 0 && f2 < 0 || !f1 || !f2) return 2;
		else if (f1 == -2 && f2 == -2 || f1 == 2 && f2 == 2) return 0;
		else if (f1 == -1 || f1 == 1) return 1;
		else return 1;
	} else if (!x) return 0;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	y = (l2 - l1) ^ k2;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	return 1;
} 
/*
inline bool intersect(Point x1, Point y1, Point x2, Point y2) {
	if (max(x1.x, y1.x) < min(x2.x, y2.x) || min(x1.x, y1.x) > max(x2.x, y2.x)) return false;
	if (max(x1.y, y1.y) < min(x2.y, y2.y) || min(x1.y, y1.y) > max(x2.y, y2.y)) return false;
	if (((x2 - x1) ^ (y1 - x1)) == 0) return true;
	if (((y2 - x1) ^ (y1 - x1)) == 0) return true;
	if (((x1 - x2) ^ (y2 - x2)) == 0) return true;
	if (((y1 - x2) ^ (y2 - x2)) == 0) return true;
	int t1 = ((x2 - x1) ^ (y1 - x1)) * ((y2 - x1) ^ (y1 - x1));
	int t2 = ((x1 - x2) ^ (y2 - x2)) * ((y1 - x2) ^ (y2 - x2));
	return t1 * t2 < 0;
}*/

int main(void) {
	//freopen("in", "r", stdin);
	while (scanf("%d%d%d%d%d%d", &n, &m, &S.x, &S.y, &T.x, &T.y) == 6) {
		scanf("%d", &K); REP(i, 1, K) a[i].Scan();
		vis.clear();
		dis.clear(); while (!Q.empty()) Q.pop();
		vis.insert(mp(mp(S.x, S.y), mp(0, 0))); dis[mp(mp(S.x, S.y), mp(0, 0))] = 0; Q.push(mp(mp(S.x, S.y), mp(0, 0)));
		while (!Q.empty()) {
			PP now = Q.front(); Q.pop(); int tim = dis[now];
			if (now.X.X == T.x && now.X.Y == T.y && now.Y.X == 0 && now.Y.Y == 0) break;
			for (int i = 0; i < 5; i++) {
				int vx = now.Y.X + dx[i], vy = now.Y.Y + dy[i];
				Point next(now.X.X + vx, now.X.Y + vy);
				PP NEXT = mp(mp(next.x, next.y), mp(vx, vy));
				if (Out(next) || vis.find(NEXT) != vis.end()) continue;				
				bool ok = true;
				for (int j = 1; j <= K; j++) 
					if (0 != test_intersection(Point(now.X.X, now.X.Y), next, a[j].s, a[j].t)) {
						ok = false; break;
					}
				if (ok) {
					dis[NEXT] = tim + 1;
					vis.insert(NEXT);
					Q.push(NEXT);
				}
			}
		}
		printf("%d\n", dis[mp(mp(T.x, T.y), mp(0, 0))]);
	}
	return 0;
}

