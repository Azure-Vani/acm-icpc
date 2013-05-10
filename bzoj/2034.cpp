#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=5001;
struct node
{
	int S,T,w;
};
node P[N];
int n,x[N];
inline bool cmpS(const node &a,const node &b)
{return a.S<b.S;}
inline bool cmpT(const node &a,const node &b)
{return a.T<b.T;}
inline bool cmpW(const node &a,const node &b)
{return a.w>b.w;}
void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d%d%d",&P[i].S,&P[i].T,&P[i].w);
	sort(P+1,P+n+1,cmpS);
	x[0]=0;
	for (int i=1;i<=n;++i)
		x[i]=max(x[i-1]+1,P[i].S);
	int j=1;
	for (int i=1;i<=n;++i)
	{
		while (P[i].S>x[j]) ++j;
		P[i].S=j;
	}
	sort(P+1,P+n+1,cmpT);
	j=1;
	for (int i=1;i<=n;++i)
	{
		while (P[i].T>x[j]) ++j;
		P[i].T=j;
	}
	sort(P+1,P+n+1,cmpW);
}
int my[N];
bool find(int a,int b)
{
	if (b>P[a].T) return 0;
	if (!my[b])
	{
		my[b]=a;
		return 1;
	}
	int j=my[b];
	if (P[a].T>P[j].T) return find(a,b+1);else
	{
		if (find(j,b+1))
		{
			my[b]=a;
			return 1;
		}
	}
	return 0;
}
void solve()
{
	memset(my,0,sizeof(my));
	long long Ans=0;
	for (int i=1;i<=n;++i)
		if (find(i,P[i].S)) Ans+=P[i].w;
	printf("%lld\n",Ans);
}
int main()
{
	init();
	solve();
	return 0;
}
