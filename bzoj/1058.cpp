#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
#include <functional>
#include <cmath>
#define len 500050
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;

multiset<long> list;
set<long>::iterator it;
long c[len]={0},a[len]={0},n,m,ask=0x6eeeeeee,ll[len]={0};

inline long min(long a,long b){return a<b?a:b;}
struct node{
	long i,x,l;bool pd;
	node(){}
	node(long i,long x,long l,bool pd):i(i),x(x),l(l),pd(pd){}
	friend bool operator <(const node& a,const node& b){return a.x>b.x;}
};priority_queue<node> heap;
void insert(long i,long x){
	ll[i]++;
	heap.push(node(i,abs(x-c[i]),ll[i],0));heap.push(node(i,abs(x-a[i+1]),ll[i],1));
	c[i]=x;
	it=list.insert(x);
	ask=min(ask,abs(x-*(--it))),++it;
	ask=min(ask,abs(x-*(++it)));
}
void wjmzbmr(void){
	node temp;
	while(temp=heap.top(),(temp.l<ll[temp.i]&&temp.pd))heap.pop();
	printf("%ld\n",temp.x);
}

int main(int argc,char** argv){
	scanf("%ld%ld",&n,&m);
	c[0]=-0x6eeeeeee;a[n+1]=-0x6eeeeeee;
	list.insert(-0x6eeeeeee);list.insert(0x6eeeeeee);
	rep(i,n){
		scanf("%ld",&a[i]),c[i]=a[i];
		it=list.insert(c[i]);
		ask=min(ask,abs(c[i]-*(--it))),++it;
		ask=min(ask,abs(c[i]-*(++it)));
		ll[i]=1;
		if(i!=1)heap.push(node(i-1,abs(a[i]-c[i-1]),ll[i]=1,1));
	}
	char ch[10];
	rep(i,m){
		scanf("%s",ch);
		if(ch[4]=='R'){long u,v;scanf("%ld%ld",&u,&v);
			insert(u,v);
		}
		if(ch[4]=='G')
			wjmzbmr();
		if(ch[4]=='S')
			printf("%ld\n",ask);
	}
	return 0;
}
