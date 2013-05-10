#include <cstdio>
#define R(i,n) for(int i=0;i<n;i++)
#define P(a,b,c,d,e,f) printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",a,b,c,d,e,f,c,b)
char q[5][10]={"iceman","lion","wolf","ninja","dragon"},f[2][5]={"red","blue"};
int A[3][5]={{0,1,2,3,4},{1,4,3,0,2},{4,3,0,1,2}},m[2],c[5],y,r[2][5],t,n[2],V[2];
int main(void) {
	scanf("%d",&y);R(_,y){
		printf("Case:%d\n",_+1);
		scanf("%d",m);1[m]=*m;R(i,5)scanf("%d", c+A[2][i]),r[0][i]=r[1][i]=0;V[0]=V[1]=0,n[0]=n[1]=0;
		R(o,50) {bool v[2]={};
			R(k,2) {R(j,5) if (m[k] >= c[t=A[k][(V[k]+j)%5]]) {
				m[k]-=c[t], P(o,f[k],q[t],++n[k],c[t],++r[k][t]),v[k]=true;V[k]+=j+1,V[k]%=5;
				break;
			}
			if (!v[k]&&V[k]>=0) V[k]=-1,printf("%03d %s headquarter stops making warriors\n",o,f[k]);}
		}
		if (V[0]+V[1]==-2) continue;
	}
	return 0;
}

