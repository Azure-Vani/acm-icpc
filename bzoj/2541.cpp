#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#define len 4005
#define ll 1000000
#define abs(x) ((x)<0?(-(x)):(x))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;


struct re{
	long x1,y1,x2,y2;
}g[len];
struct p{
	long i,k,step;
}d[ll];
long x1,y1,x0,y0,n;
bool hash[len][5]={0};
int main(int argc,char** argv){
	cin >>n>>y1>>x1>>y0>>x0;
	if(x1==x0&&y1==y0){
		cout <<0<<endl;
		exit(0);
	}
	for(long i=1;i<=n;i++){
		long x,y,xx,yy;
		cin >>y>>x>>yy>>xx;
		g[i].y1=max(y,yy);g[i].y2=min(y,yy);
		g[i].x1=min(x,xx);g[i].x2=max(x,xx);
	}
	++n;
	g[n].x1=g[n].x2=x0;
	g[n].y1=g[n].y2=y0;
	long head=1,tail=0,sum=0;
	long l1=0,l2=0,l3=0,l4=0,l1_min,l2_min,l3_min,l4_min;
	l1_min=l2_min=l3_min=l4_min=0x7ffffffd;
	for(long i=1;i<=n;i++){
		if(g[i].x1<=x1&&g[i].x2>=x1&&g[i].y2>y1&&abs(g[i].y2-y1)<l1_min){
			l1_min=abs(g[i].y1-y1);
			l1=i;
		}
		if(g[i].x1<=x1&&g[i].x2>=x1&&g[i].y1<y1&&abs(g[i].y1-y1)<l2_min){
			l2_min=abs(g[i].y2-y1);
			l2=i;
		}
		if(g[i].y1>=y1&&g[i].y2<=y1&&g[i].x2<x1&&abs(g[i].x2-x1)<l4_min){
			l4_min=abs(g[i].x2-x1);
			l4=i;
		}
		if(g[i].y1>=y1&&g[i].y2<=y1&&g[i].x1>x1&&abs(g[i].x1-x1)<l3_min){
			l3_min=abs(g[i].x1-x1);
			l3=i;
		}
	}
	if(l1==n||l2==n||l3==n||l4==n){
		cout <<1<<endl;
		exit(0);
	}
	head=1;tail=0;
	if(l1!=0){
		d[++tail].step=1;
		d[tail].k=l1;
		d[tail].i=1;
		sum++;
		hash[l1][1]=1;
	}
	if(l2!=0){
		d[++tail].step=1;
		d[tail].k=l2;
		d[tail].i=2;
		sum++;
		hash[l2][2]=1;
	}
	if(l3!=0){
		d[++tail].step=1;
		d[tail].k=l3;
		d[tail].i=3;
		sum++;
		hash[l3][3]=1;
	}
	if(l4!=0){
		d[++tail].step=1;
		d[tail].k=l4;
		d[tail].i=4;
		sum++;
		hash[l4][4]=1;
	}
	while(sum){
		long h=d[head].i,u=d[head].k,tim=d[head++].step;
		sum--;
		if(head>=ll-3)
			head=1;
		if(h<3){
			long ly=g[u].y1+1,lx=g[u].x1,v=0,e=0,v_min,e_min;
			v_min=0x7ffffffd;e_min=0x7ffffffd;
			if(h==1)ly=g[u].y2-1;
			for(long i=1;i<=n;i++){
				if(i==u)continue;
				if(g[i].y1>=ly&&g[i].y2<=ly&&g[i].x2<lx&&abs(g[i].x2-lx)<v_min){
					v_min=abs(g[i].x2-lx);
					v=i;
				}
				if(g[i].y1>=ly&&g[i].y2<=ly&&g[i].x1>lx&&abs(g[i].x1-lx)<e_min){
					e_min=abs(g[i].x1-lx);
					e=i;
				}
			}
			if(v==n||e==n){
				cout <<tim+1<<endl;
				exit(0);
			}
			if(v!=0&&!hash[v][4]){
				hash[v][4]=true;
				tail++;
				if(tail>ll-3)tail=1;
				d[tail].k=v;
				d[tail].i=4;sum++;
				d[tail].step=tim+1;
			}
			if(e!=0&&!hash[e][3]){
				hash[e][3]=true;
				tail++;
				if(tail>ll-3)tail=1;
				d[tail].k=e;
				d[tail].i=3;sum++;
				d[tail].step=tim+1;
			}
		}else{
			long lx=g[u].x2+1,ly=g[u].y1;
			if(h==3)lx=g[u].x1-1;
			long v=0,e=0,v_min=0x7ffffffd,e_min=0x7ffffffd;
			for(long i=1;i<=n;i++){
				if(i==u)continue;
				if(g[i].x1>lx||g[i].x2<lx)continue;
				if(g[i].y2>ly&&abs(g[i].y2-ly)<e_min){
					e=i;
					e_min=abs(g[i].y2-ly);
				}
				if(g[i].y1<ly&&abs(g[i].y1-ly)<v_min){
					v=i;
					v_min=abs(g[i].y1-ly);
				}
			}
			if(e==n||v==n){
				cout <<tim+1<<endl;
				exit(0);
			}
			if(e!=0&&!hash[e][1]){
				hash[e][1]=true;
				tail++;
				if(tail>ll-3)tail=1;
				d[tail].k=e;
				d[tail].i=1;sum++;
				d[tail].step=tim+1;
			}
			if(v!=0&&!hash[v][2]){
				hash[v][2]=true;
				tail++;
				if(tail>ll-3)tail=1;sum++;
				d[tail].k=v;
				d[tail].i=2;
				d[tail].step=tim+1;
			}
		}
	}
	cout <<0<<endl;
	return 0;
}
