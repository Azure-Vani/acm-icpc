#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

#define pb push_back
#define mp make_pair
#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)
using namespace std;

const int MAXN = 100010, mod = 1000000007;

typedef pair<int, int> PII;
typedef vector<PII> VII;

int n, Ans[MAXN]; VII Edge[MAXN], Ask[MAXN];

int father[MAXN], d[MAXN], deep[MAXN], hash[MAXN], pow[MAXN];

inline void Bfs(void) {
    int head = 1, tail = 1; d[1] = 1;
    while (head <= tail) {
        int now = d[head++];
        foreach(it, Edge[now]) if (it->second != father[now]) {
            father[it->second] = now;
            d[++tail] = it->second;
            deep[it->second] = deep[now] + 1;
            hash[it->second] = (hash[now] * 26ll + it->first) % mod;
        }
    }
    for (int i = 2; i <= n; i++) {
        foreach(it, Edge[i]) if (it->second == father[i]) {
            Edge[i].erase(it);
            break;
        }
    }
}

VII tmp;

inline void Merge(void) {
    int head = 1, tail = 1; d[1] = 1;
    while (head <= tail) {
        int now = d[head++]; sort(Edge[now].rbegin(), Edge[now].rend());
        VII::iterator L = Edge[now].begin(), R;
        int cnt = 0;
        while (L != Edge[now].end()) {
            tmp.clear(); R = L;
            while (R != Edge[now].end() && R->first == L->first) {
                tmp.insert(tmp.end(), Edge[R->second].begin(), Edge[R->second].end());
                Edge[R->second].clear(); if (R != L) R->first = -1;
                R++;
            }
            cnt++;
            Edge[L->second] = tmp;
            d[++tail] = L->second;
            L = R;
        }
        sort(Edge[now].rbegin(), Edge[now].rend());
        Edge[now].resize(cnt);
    }
}

inline int getH(int x, int y) {
    int ret = (hash[y] - (long long) hash[x] * pow[deep[y] - deep[x]]) % mod;
    if (ret < 0) ret += mod;
    return ret;
}

priority_queue<pair<int, PII> > Q;

bool vis[MAXN];

inline void Dfs(int u) {
    while (!Q.empty() && (-Q.top().first == deep[u] || vis[Q.top().second.first])) {
        if (!vis[Q.top().second.first]) Ans[Q.top().second.second] = getH(Q.top().second.first, u);
        Q.pop();
    }
    foreach(it, Ask[u]) Q.push(mp(-it->first - deep[u], mp(u, it->second)));
    foreach(it, Edge[u]) Dfs(it->second);
    vis[u] = true;
}

int main(void) {
    //freopen("in", "r", stdin);
    pow[0] = 1; for (int i = 1; i <= 100000; i++) pow[i] = (long long) pow[i - 1] * 26 % mod;
    int kase; scanf("%d", &kase); while (kase--) {
        memset(Ans, -1, sizeof Ans); memset(vis, 0, sizeof vis);
        scanf("%d", &n); for (int i = 1; i <= n; i++) Edge[i].clear(), Ask[i].clear();
        for (int i = 1; i < n; i++) {
            int x, y; char ch[3];
            scanf("%d %d %s", &x, &y, ch);
            Edge[x].pb(mp(ch[0] - 'a', y));
            Edge[y].pb(mp(ch[0] - 'a', x));
        }
        int q; scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            int x, len; scanf("%d%d", &x, &len);
            Ask[x].pb(mp(len, i));
        }
        Bfs();
        Merge();
        while (!Q.empty()) Q.pop();
        Dfs(1);
        for (int i = 1; i <= q; i++) {
            if (Ans[i] != -1) printf("%d\n", Ans[i]); else puts("IMPOSSIBLE");
        }
    }
    return 0;
}
