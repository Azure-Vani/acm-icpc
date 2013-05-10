#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 2405
#define MAXM (1200 * 1200 + 1200 * 2) * 2

#define INFINITE 0x3f3f3f3f
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define OP(x) ((((x) - 1) ^ 1) + 1)


using namespace std;


#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}


int n, m;
int S, T, N;
int ans = 0;

int Count = 0;
int begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1], c[MAXM + 1];
void AddEdge(int a, int b, int f)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
	c[Count] = f;

	Count ++;
	next[Count] = begin[b];
	begin[b] = Count;
	end[Count] = a;
	c[Count] = 0;
}

void Init()
{
	scan(n); scan(m);
	N = n + m;
	S = ++ N, T = ++ N;
	for (int i = 1; i <= n; i ++)
	{
		int v, cnt;
		scan(v); scan(cnt);
		ans += v;
		AddEdge(S, i, v);
		for (int j = 1; j <= cnt; j ++)
		{
			int id, rent_fee;
			scan(id); scan(rent_fee);
			AddEdge(i, id + n, rent_fee);
		}
	}
	for (int i = 1; i <= m; i ++)
	{
		int s;
		scan(s);
		AddEdge(i + n, T, s);
	}
}


int cur[MAXN + 1], d[MAXN + 1], pre[MAXN + 1], a[MAXN + 1], cnt[MAXN + 1];
int sap()
{
	int flow = 0;
	int register now, tmp, u;
	a[u = S] = INFINITE;
	cnt[0] = N;
	memcpy(cur, begin, sizeof(begin[0]) * N);
	while (d[S] < N)
	{
		for (now = cur[u]; now; now = next[now])
			if (c[now] && d[u] == d[end[now]] + 1)
				break;
		if (now)
		{
			tmp = end[now];
			pre[tmp] = cur[u] = now;
			a[tmp] = MIN(a[u], c[now]);
			if ((u = tmp) == T)
			{
				flow += (tmp = a[T]);
				do
				{
					c[pre[u]] -= tmp;
					c[OP(pre[u])] += tmp;
					u = end[OP(pre[u])];
				}
				while (u != S);
				a[S] = INFINITE;
			}
		}
		else
		{
			if ((--cnt[d[u]]) == 0)
				break;
			cur[u] = begin[u], d[u] = N;
			for (now = begin[u]; now; now = next[now])
				if (c[now] && d[u] > d[end[now]] + 1)
					d[u] = d[end[now]] + 1, cur[u] = now;
			cnt[d[u]] ++;
			if (u != S)
				u = end[OP(pre[u])];
		}
	}
	return flow;
}

void Solve()
{
	printf("%d\n", ans - sap());
}

int main()
{
	Init();
	Solve();
	return 0;
}
