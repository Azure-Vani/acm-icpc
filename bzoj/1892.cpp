#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N=500010,W=10010;
int n,m,w,rank[N];
int a[N],b[N],C[W];
void Add(int x,int c)
{
	for (;x<=w;x+=x&(-x))
		C[x]+=c;
}
int Ask(int x)
{
	int ans=0;
	for (;x;x-=x&(-x))
		ans+=C[x];
	return ans;
}
void init()
{
	scanf("%d%d%d",&n,&m,&w);
	for (int i=1;i<=n;++i) scanf("%d",a+i);
	for (int i=1;i<=m;++i) scanf("%d",b+i);
	memset(C,0,sizeof(C));
	for (int i=1;i<=m;++i) 
	{
		Add(b[i],1);
		rank[i]=Ask(b[i]-1)+1;
	}
}
vector<int> Ans;
int next[N];
int Last;
int Rank(int *a,int now,int x)
{
	while (Last<now)
		Add(a[Last++],-1);
	return Ask(x-1)+1;
}
void solve()
{
	memset(C,0,sizeof(C));
	next[1]=0;
	int i,k=0;
	Last=1;Add(b[1],1);
	for (i=2;i<=m;++i)
	{
		while (k>0&&Rank(b,i-k,b[i])!=rank[k+1]) k=next[k];
		if (Rank(b,i-k,b[i])==rank[k+1]) ++k;
		next[i]=k;
		Add(b[i],1);
	}
	memset(C,0,sizeof(C));
	Last=1;
	k=0;
	for (i=1;i<=n;++i)
	{
		while (k>0&&Rank(a,i-k,a[i])!=rank[k+1]) k=next[k];
		if (Rank(a,i-k,a[i])==rank[k+1]) ++k;
		if (k==m)
		{
			Ans.push_back(i-k+1);
			k=next[k];
		}
		Add(a[i],1);
	}
	printf("%d\n",Ans.size());
	for (i=0;i<Ans.size();++i)
		printf("%d\n",Ans[i]);
}
int main()
{
	init();
	solve();
	return 0;
}
