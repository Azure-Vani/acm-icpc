#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define len 10050
using namespace std;
 
map<long,long> X;
map<long,long> Y;
set<long> XX;
set<long> YY;
set<long>::iterator it;
 
struct re{
        long x,y,fir,x1,y1;
        friend bool operator <(const re& a,const re& b){
                if(a.x!=b.x)
                        return a.x<b.x;
                if(a.fir!=b.fir)
                        return a.fir<b.fir;
                return a.y<b.y;
        }
}a[len],mode[len*2];
set<re> wjmzbmr;
struct T{
        long start,end;
}line[len];
 
long n,ans,xx=0,yy=0;
long lift[len]={0},reght[len]={0};
bool hash[len]={0},check=false;
 
class Tree{
        private:
                struct oo{
                        long l,r,mid,cnt;
                        bool cover;
                }a[len*8];
                void build(long k,long l1,long l2){
                        a[k].l=l1,a[k].r=l2,a[k].mid=(l1+l2)>>1;
                        if(l1==l2)
                                return;
                        build(k*2,l1,a[k].mid);
                        build(k*2+1,a[k].mid+1,l2);
                }
        public:
                Tree(){
                        memset(a,0,sizeof a);
                        build(1,1,max(xx,yy));
                }
                
                void insert(long k,long u){
                        if(a[k].l==a[k].r){
                                a[k].cnt++;
                                return;
                        }
                        if(u<=a[k].mid)
                                insert(k*2,u);
                        if(u>a[k].mid)
                                insert(k*2+1,u);
                        a[k].cnt=a[k*2].cnt+a[k*2+1].cnt;
                }
                
                void insert(long k,long l1,long l2){
                        if(l1>l2)
                                return;
                        if(l1<=a[k].l&&l2>=a[k].r){
                                if(a[k].cnt>0){
                                        check=false;
                                }
                                a[k].cover=true;
                                return;
                        }
                        insert(k*2,l1,min(l2,a[k].mid));
                        insert(k*2+1,max(a[k].mid+1,l1),l2);
                }
                
                void Delete(long k,long u){
                        if(a[k].l==a[k].r){
                                if(a[k].cnt>0)a[k].cnt--;
                                return;
                        }
                        if(u<=a[k].mid)
                                Delete(k*2,u);
                        if(u>a[k].mid)
                                Delete(k*2+1,u);
                        a[k].cnt=a[k*2].cnt+a[k*2+1].cnt;
                }
 
};
 
void dfs(long k,long sum,long p,long l){
        if(check)
                return;
        if(k)
                hash[k]=true;
        
        if(k==0&&sum==n&&p==0){
                check=true;
                ans=l;
                return;
        }
        line[sum].start=k;
        if(p==0){
                long t1=0,t2=0,min1=0,min2=0;
                t1=lift[k];
                t2=reght[k];
                min1=a[k].x-a[lift[k]].x;
                min2=a[reght[k]].x-a[k].x;
                if(t1!=0&&!hash[t1])
                        line[sum].end=t1,dfs(t1,sum+1,p^1,l+min1);
                if(t2!=0&&!hash[t2])
                        line[sum].end=t2,dfs(t2,sum+1,p^1,l+min2);
                
        }else{
                if(k-1>=0)
                        if(k-1>=0&&!hash[k-1]&&a[k-1].x==a[k].x)
                                line[sum].end=k-1,
                                dfs(k-1,sum+1,p^1,l+a[k].y-a[k-1].y);
                
                if(k+1<=n-1&&!hash[k+1]&&a[k+1].x==a[k].x)
                        line[sum].end=k+1,
                        dfs(k+1,sum+1,p^1,l+a[k+1].y-a[k].y);
        }
        if(k)
                hash[k]=false;
}
 
void Fuck_it(void){
        for(long i=0;i<n;i++){
                for(long j=i-1;j>=0;j--)
                        if(a[i].y==a[j].y){
                                lift[i]=j;
                                break;
                        }
                for(long j=i+1;j<n;j++)
                        if(a[i].y==a[j].y){
                                reght[i]=j;
                                break;
                        }
        }
}
 
int main(int argc,char** argv){
        ios::sync_with_stdio(false);
        
        cin >>n;
        for(long i=0;i<n;i++){
                cin >>a[i].x>>a[i].y;
                XX.insert(a[i].x);
                YY.insert(a[i].y);
        }
        for(it=XX.begin();it!=XX.end();it++)
                xx++,X.insert(map<long,long>::value_type(*it,xx));
        for(it=YY.begin();it!=YY.end();it++)
                yy++,Y.insert(map<long,long>::value_type(*it,yy));
        
        XX.clear();
        YY.clear();
        
        sort(a,a+n);
        Fuck_it();
        
        dfs(0,0,0,0);
        
        if(!check){
                cout <<0<<endl;
                exit(0);
        }
        
        long l=0;
        for(long i=0;i<n;i++){
                long l1=line[i].start,l2=line[i].end;
                if(a[l1].y==a[l2].y){
                        l++;
                        mode[l].x=X[a[l1].x];
                        mode[l].y=Y[a[l1].y];
                        l++;
                        mode[l].x=X[a[l2].x];
                        mode[l].y=Y[a[l2].y];
                        if(a[l1].x<a[l2].x)
                                mode[l].fir=0,mode[l-1].fir=2;
                        if(a[l1].x>a[l2].x)
                                mode[l].fir=2,mode[l-1].fir=0;
                }else{
                        l++;
                        mode[l].fir=1;
                        mode[l].x=X[a[l1].x];
                        mode[l].y=min(Y[a[l2].y],Y[a[l1].y]);
                        mode[l].x1=X[a[l2].x];
                        mode[l].y1=max(Y[a[l2].y],Y[a[l1].y]);
                }
        }
        X.clear();
        Y.clear();
        mode[0].x=-0x6eeeeeee;
        sort(mode,mode+l+1);
        
        Tree tree;
        check=true;
        for(long i=1;i<=l;i++){
                if(!check)
                        break;
                if(mode[i].fir==2)
                        tree.insert(1,mode[i].y);else
                if(mode[i].fir==1)
                        tree.insert(1,min(mode[i].y,mode[i].y1),max(mode[i].y,mode[i].y1));else
                if(mode[i].fir==0)
                        tree.Delete(1,mode[i].y);
        }
 
        if(check)
                cout <<ans<<endl;
        else
                cout <<0<<endl;
        return 0;
}