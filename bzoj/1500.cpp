#include<cstdio> 
#include<iostream> 
#define cp freopen 
#define rzy inline  
#define Node node* 
#define maxn 500000*2 
#define rep(i,a,b) for (int i=a;i<=b;i++) 
using namespace std; 
const int inf=100000000; 
int dat[maxn],n;  
struct splay 
{int top; 
    struct node 
    { 
       int k,mx,lx,rx,sm,sa,s; 
       bool w,d; 
       node *c[2],*p;  
       void sc(Node p,bool d) 
       {c[d]=p;p->p=this;p->d=d;}     
    }*tmp,*root,*Null,*Now,*sk[maxn],Data[maxn]; 
    rzy splay() 
    {top=0,Now=Data; 
        root=new_node(-inf); root->p=root; 
        Null=new_node(0);    Null->s=0;  
        Null->lx=Null->rx=Null->mx=-inf;
    }  
    rzy Node rt(){return root;} 
    rzy Node new_node(int k) 
    { 
        if (top) tmp=sk[top--];else tmp=Now++; 
        tmp->k=tmp->lx=tmp->rx=tmp->sm=tmp->mx=k; 
        tmp->w=0;      tmp->c[0]=tmp->c[1]=Null;
        tmp->s=1;   tmp->sa=inf;     return tmp;  
    } 
    rzy void del_node(Node p) 
    {sk[++top]=p;} 
    rzy void t(Node p) 
    {Node f=p->p;bool d=p->d; 
        down(f); down(p); 
        f->sc(p->c[!d],d); f->p->sc(p,f->d); 
        p->sc(f,!d);      upd(f);  upd(p);   
    } 
    rzy void upd(Node x) 
    {
        x->s=x->c[1]->s+x->c[0]->s+1; 
        x->sm=x->c[0]->sm+x->k+x->c[1]->sm; 
        x->lx=max(x->c[0]->lx,x->c[0]->sm+x->k+max(0,x->c[1]->lx)); 
        x->rx=max(x->c[1]->rx,x->c[1]->sm+x->k+max(0,x->c[0]->rx)); 
        x->mx=max(x->c[0]->mx,x->c[1]->mx); 
        x->mx=max(x->mx,max(x->c[0]->rx,0)+x->k+max(x->c[1]->lx,0)); 
    } 
    rzy void ss(Node p,Node x) 
    {int sa=x->sa;bool w=x->w;  
        if (p==Null) return; 
        if (w!=0)    rev(p); 
        if (sa!=inf) same(p,sa); 
    } 
    rzy void down(Node x) 
    { 
        if (x==Null) return;  
        ss(x->c[1],x); ss(x->c[0],x); 
        x->w=0; x->sa=inf;  
    } 
    rzy void spl(Node x,Node f) 
    { 
       while (x->p!=f) 
         if (x->p->p==f) t(x); 
         else(x->d==x->p->d)?(t(x->p),t(x)):(t(x),t(x)); 
    } 
    rzy void build(Node t,int a,int b,bool d) 
    {int mid=(a+b)>>1; 
       if (a>b) return;  
       Node p=new_node(dat[mid]); t->sc(p,d);   
       build(p,a,mid-1,0);        build(p,mid+1,b,1); 
       upd(p); 
    } 
    rzy Node sel(int k) 
    {k--;int r;Node t=root->c[1];  
       for (;;) 
       {  down(t);
          if ((r=t->c[0]->s)==k)return t; 
          t=t->c[k>r];  if (k>r) k-=r+1; 
       } 
    } 
    rzy Node Get(int x,int y) 
    { 
        Node p=sel(x-1); spl(p,root); 
        Node v=sel(y+1); spl(v,p); 
        return v->c[0];  
    } 
    rzy void getmax() 
    {cout<<root->c[1]->mx<<endl;} 
    rzy void getsum() 
    {int x,y; scanf("%d %d",&x,&y); 
        y+=x-1;Node p=Get(x+1,y+1); 
        cout<<p->sm<<endl;  
    } 
    rzy Node buildlist(Node t,int y) 
    {Node last=t;  
        rep(i,1,y) 
        { 
           Node p=new_node(dat[i]); 
           last->sc(p,1); 
           last=p; 
        }return last;  
    } 
    rzy void insert() 
    {int x,y; scanf("%d %d",&x,&y); 
        rep(i,1,y) scanf("%d",&dat[i]); 
        Node p=new_node(-inf); 
        Node last=buildlist(p,y); 
        del_node(p);  p=p->c[1];  
        Node v=sel(x+1);spl(v,root); 
        Node q=sel(x+2);spl(q,v); 
        p->d=q->d; v->sc(p,p->d); 
        last->sc(q,1);   spl(q,root); 
    } 
    rzy void Delete() 
    {int x,y; scanf("%d %d",&x,&y); 
        y+=x-1;    Node p=Get(x+1,y+1); 
        Node f=p->p; f->c[p->d]=Null; 
        deltree(p);  spl(f,root); 
    } 
    rzy void rev(Node p) 
    {p->w^=1;
        swap(p->c[0],p->c[1]); 
        swap(p->lx,p->rx);
        p->c[0]->d=0,p->c[1]->d=1; 
    } 
    rzy void revers() 
    {int x,y; scanf("%d %d",&x,&y); 
        y+=x-1;    Node p=Get(x+1,y+1); 
        p->w^=1;   rev(p); p->w^=1; 
        spl(p,root); 
    } 
    rzy void same(Node p,int sa) 
    {p->sa=sa; 
        p->k=p->sa;p->sm=(p->s)*(p->sa); 
        if (p->sa>0) 
        {p->lx=p->rx=p->mx=p->sm;} 
        else{p->lx=p->rx=p->mx=p->sa;} 
    } 
    rzy void makesa() 
    {int x,y,z; scanf("%d %d %d",&x,&y,&z); 
        y+=x-1;    Node p=Get(x+1,y+1); 
        down(p);   p->sa=z;   same(p,z); 
        spl(p,root); 
    } 
    rzy void deltree(Node p) 
    { 
        if (p==Null) return; 
        del_node(p); 
        deltree(p->c[1]); deltree(p->c[0]); 
    } 
}sp;  
  
int main() 
{//cp("1.in","r",stdin); cp("1.out","w",stdout); 
    int m;cin>>n>>m; 
    rep(i,2,n+1) scanf("%d",&dat[i]); 
    dat[1]=dat[n+2]=-inf;
    sp.build(sp.rt(),1,n+2,1); 
    rep(i,1,m) 
    {char ar[20];  
        scanf("\n%s",ar); 
        if (ar[0]=='G') sp.getsum();else
        if (ar[2]=='X') sp.getmax();else
        if (ar[0]=='I') sp.insert();else
        if (ar[0]=='D') sp.Delete();else    
        if (ar[0]=='R') sp.revers();else; 
        if (ar[2]=='K') sp.makesa(); 
    } 
}