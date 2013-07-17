#include <cstdio>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

template<class T> inline int sign(T x) { if (x < 0) return -1; else if (x > 0) return 1; else return 0;}
struct Point {
    double x, y;
    Point():x(0),y(0){}
    Point(double x, double y):x(x), y(y){}
    inline Point operator +(const Point& oth) const {
        return Point(x + oth.x, y + oth.y);
    }
    inline Point operator -(const Point& oth) const {
        return Point(x - oth.x, y - oth.y);
    }
    inline double operator ^(const Point& oth) const {
        return (double) x * oth.y - (double) oth.x * y;
    }
    inline double rotate(const Point& a, const Point& b) const {
        return sign((a - *this) ^ (b - *this));
    }
    inline bool operator<(const Point&) const;
}; Point M;

inline bool Point::operator <(const Point& b) const {
    return atan2(y - M.y, x - M.x) > atan2(b.y - M.y, b.x - M.x);
}

typedef set<Point> SII;

SII S;

template<class T> inline T prev(T now) {if (now != S.begin()) return --now; else {now = S.end(); return --now;} }
template<class T> inline T next(T now) {++now; if (now == S.end()) now = S.begin(); return now;}

inline void Init(void) {
    Point tmp[3]; double X = 0, Y = 0;
    for (int i = 0; i < 3; i++) {
        scanf("%*f%lf%lf", &tmp[i].x, &tmp[i].y);
      X += tmp[i].x, Y += tmp[i].y;
    }
    M.x = X / 3.0, M.y = Y / 3.0;
    for (int i = 0; i < 3; i++) S.insert(tmp[i]);
}

inline void Update(Point now) {
    S.erase(now); SII::iterator it = S.insert(now).first, b, c = it; if (it == S.end()) it = S.begin();
    it = prev(c);
    while (S.size() > 3 && now.rotate(*it, *prev(it)) <= 0) {
        b = it, it = prev(it);
        S.erase(b);
    }
    it = next(c);
    while (S.size() > 3 && now.rotate(*it, *next(it)) >= 0) {
        b = it, it = next(it);
        S.erase(b);
    }
}
inline bool tryTo(Point now) {
    SII::iterator it = S.lower_bound(now); if (it == S.end()) it = S.begin();
    int t = now.rotate(*prev(it), *it);
    if (t <= 0) return false; else return true;
}

inline void Insert(Point now) {
    if (tryTo(now)) {
        Update(now);
    }
}

inline int Ask(Point now) {
    return tryTo(now);
}

int main(void) {
   // freopen("in", "r", stdin);
    int q; scanf("%d", &q);
    Init(); q-=3;
    for (int i = 1; i <= q; i++) {
        int type; Point now;
        scanf("%d%lf%lf", &type, &now.x, &now.y);
        if (type == 1) {
            Insert(now);
        } else {
            int t = Ask(now);
            if (t) puts("NO"); else puts("YES");
        }
    }
    return 0;
}
