#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int mx = 110;
int base; LL res[mx];

// 处理不断变化的后缀 
// rep: 每个数字在一个周期中重复的次数为 pwr(base, rep)
// tm: 周期数目为 pwr(base, tm)
// posi: 第一个数为正？
// change: 正负性交替变化？ 
void alt (int rep, int tm, bool posi, bool change)
{
	if (!change)
	{
		LL s = base * (base - 1) >> 1;
		res[rep + tm] += (posi ? 1 : -1) * s;
	}
	else
	{
		LL s = 0;
		for (int i = 0; i < base; i++)
		{
			int sg = rep ? (base & 1) : 1;
			s += (posi ? 1 : -1) * i * sg;
			if (sg) posi = !posi;
		}
		if (base & 1) res[0] += s;
		else res[tm] += s;
	}
}
// 处理相同的前缀 
// tm: 数字出现的次数为 pwr(base, tm)
void prefix (int d, int tm, bool posi, bool change)
{
	if (!change)
	{
		res[tm] += (posi ? 1 : -1) * d;
	}
	else
	{
		int sg = tm ? (base & 1) : 1;
		res[0] += (posi ? 1 : -1) * d * sg;
	}
}
int dn[50]; int len;
inline int di (int t)
{
	return dn[t - 1];
}
int main ()
{
	LL td; int cvt[50]; scanf("%d %lld", &base, &td);
	for (len = 0; td; ++len) dn[len] = td % base, td /= base;
	int rep, time; bool posi = true, tp;
	for (int i = 1; i < len; i++)
	{
		for (int f = 1; f < base; f++)
		{
			tp = posi;
			prefix(f, i - 1, tp, i & 1);
			for (int j = i - 1; j >= 1; j--)
			{
				tp = !tp;
				alt(j - 1, i - j - 1, tp, i & 1);
			}
			if (i == 1) posi = !posi;
			else if ((base & 1) && (i & 1)) posi = !posi;
		}
	}
	for (int i = len; i >= 1; i--)
	{
		int l = (i == len ? 1 : 0), r = (i == 1 ? di(i) : di(i) - 1);
		for (int f = l; f <= r; f++)
		{
			tp = posi;
			for (int j = len; j > i; j--)
			{
				prefix(di(j), i - 1, tp, len & 1);
				tp = !tp;
			}
			prefix(f, i - 1, tp, len & 1);
			for (int j = i - 1; j >= 1; j--)
			{
				tp = !tp;
				alt(j - 1, i - j - 1, tp, len & 1);
			}
			if (i == 1)
			{
				if (len & 1) posi = !posi;
			}
			else if ((base & 1) && (len & 1)) posi = !posi;
		}
	}
	for (int i = mx - 1; i >= 1; i--) res[i - 1] += base * res[i];
	printf("%lld\n", res[0]);
	return 0;
}