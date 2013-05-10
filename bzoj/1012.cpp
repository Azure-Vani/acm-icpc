#include <fstream>
#include <iostream>
#include <cstring>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define len 200050
using namespace std;

long n=0;
long d,m,t=0,u;

class Tree{
	private:
		struct T{
			long l,r,mid,data;
		}*a;
		void build(long k,long l,long r){
			a[k].l=l,a[k].r=r,a[k].mid=(l+r)>>1,a[k].data=0;
			if(l==r)return;
			build(k<<1,l,a[k].mid);
			build(k*2+1,a[k].mid+1,r);
		}
	public:
		Tree(){
			a=new T[len*4];
			build(1,1,m);
		}
		void insert(long k,long u,long h){
			if(a[k].l==a[k].r){
				a[k].data=u;
				return;
			}
			if(h<=a[k].mid)
				insert(k<<1,u,h);
			if(h>a[k].mid)
				insert(k*2+1,u,h);
			a[k].data=max(a[k*2].data,a[k*2+1].data);
		}
		long ask(long k,long l1,long l2){
			if(l1>l2)
				return 0;
			if(l1<=a[k].l&&l2>=a[k].r)
				return a[k].data;
			long t1=ask(k*2,l1,min(l2,a[k].mid));
			long t2=ask(k*2+1,max(a[k].mid+1,l1),l2);
			return max(t1,t2);
		}
};

int main(int argc,char** argv){
	ios::sync_with_stdio(false);
	
	cin >>m>>d;cin.get();
	Tree tree;
	for(long i=1;i<=m;i++){
		char ch=cin.get();
		if(ch=='Q'){
			cin >>u;cin.get();
			cout <<(t=tree.ask(1,n-u+1,n))<<endl;
		}else{
			cin >>u;cin.get();
			tree.insert(1,(u%d+t%d)%d,++n);
		}
	}
	
	return 0;
}
