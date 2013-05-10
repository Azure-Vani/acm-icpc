#include <iostream>
#include <cstdio>
#define MAXN 60
#define MAXM 9
#define Pos(x,y) ((x)*n+(y))
#define MAXNODE (MAXN*MAXM+MAXN+100)
#define MAXEDGE (MAXNODE*MAXN*2)
#define INFINIT 1000000000
#define OPPOSITE(x) (((x)&1)?((x)+1):((x)-1))
using namespace std;
 
int S = MAXNODE-1,T = MAXNODE-2;
int n,m;
int begin[MAXNODE+1],end[MAXEDGE+1],next[MAXEDGE+1],c[MAXEDGE+1],cost[MAXEDGE+1];
int Count = 0;
void AddEdge(int a,int b,int flow,int v){
    Count++;
    next[Count] = begin[a];
    begin[a] = Count;
    end[Count] = b;
    c[Count] = flow;
    cost[Count] = v;
    Count++;
    next[Count] = begin[b];
    begin[b] = Count;
    end[Count] = a;
    c[Count] = 0;
    cost[Count] = -v;
}
void Init(){
    scanf("%d%d",&m,&n);
    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++){
            int t;
            scanf("%d",&t);
            for (int k = 0; k<n; k++)
                AddEdge(Pos(j,k),MAXN*MAXM+i,1,(k+1)*t);
        }
    for (int i = 0; i<m; i++)
        for (int j = 0; j<n; j++)
            AddEdge(S,Pos(i,j),1,0);
    for (int i = 0; i<n; i++)
        AddEdge(MAXN*MAXM+i,T,1,0);
}
int Minpath[MAXNODE+1],pre[MAXNODE+1],q[MAXNODE+1],a[MAXNODE+1];
bool hash[MAXNODE+1];
void SPFA(){
    for (int i = 0; i<=MAXNODE; i++)
        Minpath[i] = INFINIT;
    Minpath[S] = 0;
    q[1] = S;
    hash[S] = true;
    a[S] = INFINIT;
    int head = 0,tail = 1;
    while (head!=tail){
        if ((++head)==MAXNODE) head = 0;
        int t = q[head],tmp;
        for (int now = begin[t];now;now=next[now])
            if (c[now]&&Minpath[t]+cost[now]<Minpath[tmp=end[now]]){
                Minpath[tmp] = Minpath[t]+cost[now];
                a[tmp] = min(a[t],c[now]);
                pre[tmp] = now;
                if (!hash[tmp]){
                    hash[tmp] = true;
                    if ((++tail) == MAXNODE) tail = 0;
                    q[tail] = tmp;
                }
            }
        hash[t] = false;
    }
}
int CostFlow(){
    int costflow = 0;
    while (true){
        SPFA();
        if (Minpath[T] == INFINIT) break;
        int u = T,tmp = a[T];
        do{
            costflow += cost[pre[u]]*tmp;
            c[pre[u]] -= tmp;
            c[OPPOSITE(pre[u])] += tmp;
            u = end[OPPOSITE(pre[u])];
        }while(u!=S);
    }
    return costflow;
}
void Solve(){
    printf("%.2lf\n",(double)CostFlow()/(double)n);
}
 
int main(){
    Init();
    Solve();
    return 0;
}
