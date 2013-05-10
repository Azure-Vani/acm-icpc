#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define maxn 600*600
#define len 1150
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
bool hash[len][len]={true},map[len][len]={0};
long n,x,y,fim[5][2]={{0,0},{1,0},{0,1},{-1,0},{0,-1}};
struct node{
                long x,y,s;
                node(){}
                node(long x,long y,long s):x(x),y(y),s(s){}
};
int main(int argc,char** argv){
                node *d=new node[maxn];
                cin >>x>>y>>n;
                if(x==0&&y==0){
                        cout <<0<<endl;
                        exit(0);
                }   
                x+=600,y+=600;
                long l1,l2;
                rep(i,n){cin >>l1>>l2;map[l1+600][l2+600]=true;}
                long head=1,tail=1,sum=1;
                d[1]=node(600,600,0);
                while(sum){
                        long lx=d[head].x,ly=d[head].y,s=d[head++].s;
                        if(head>maxn-2)head=1;sum--;

                        rep(i,4){
                                long rx=lx+fim[i][0],ry=ly+fim[i][1];
                                if(!map[rx][ry]&&!hash[rx][ry]&&abs(rx-600)<=502.0&&abs(ry-600)<=502.0){
                                        if(rx==x&&ry==y){
                                                cout <<s+1<<endl;
                                                exit(0);
                                        }
                                        d[++tail]=node(rx,ry,s+1);if(tail>maxn-2)tail=1;sum++;
                                        hash[rx][ry]=true;
                                }
                        }
                }
                return 0;
}