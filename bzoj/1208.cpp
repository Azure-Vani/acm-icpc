#include <cctype>
#include <cstdio>
#include <iostream>
const long kMAX=80050;
namespace Solve{
	const long inf=2047483647;
	long S[kMAX]={0},L[kMAX]={0},R[kMAX]={0},K[kMAX]={0},sid=0,root=0;
	void LL(long& t){
		long k=R[t];R[t]=L[k],L[k]=t;
		S[k]=S[t],S[t]=1+S[L[t]]+S[R[t]];
		t=k;
	}
	void RR(long &t){
		long k=L[t];L[t]=R[k],R[k]=t;
		S[k]=S[t],S[t]=S[L[t]]+S[R[t]]+1;
		t=k;
	}
	void Maintrain(long &t){
		if(S[L[t]] < S[R[R[t]]]) LL(t), Maintrain(L[t]), Maintrain(t);else
		if(S[R[t]] < S[L[L[t]]]) RR(t), Maintrain(R[t]), Maintrain(t);else
		if(S[L[t]] < S[L[R[t]]]) RR(R[t]), LL(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);else
		if(S[R[t]] < S[R[L[t]]]) LL(L[t]), RR(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);
	}
	
	void Insert(long &t,long x){
		if(!t){
			K[t=++sid]=x;
			S[t]=1;L[t]=R[t]=0;
			return;
		}
		S[t]++;
		if(x<K[t])
			Insert(L[t],x);
		else
			Insert(R[t],x);
		Maintrain(t);
	}

	long Delete(long &t,long x){
		S[t]--;
		if(K[t]==x||(L[t]==0&&x<K[t])||(R[t]==0&&x>K[t])){
			long r=K[t];
			if(L[t]==0||R[t]==0)
				t=L[t]+R[t];
			else
				K[t]=Delete(L[t],x+1);
			return r;
		}
		if(x<K[t])
			return Delete(L[t],x);
		else
			return Delete(R[t],x);
	}
	
	long Small(long t,long x){
		if(!t)return -inf;
		if(K[t]==x)
			return x;
		if(x<K[t])
			return Small(L[t],x);
		else{
			long r=Small(R[t],x);if(r!=-inf)return r;else return K[t];
		}
	}
	long Large(long t,long x){
		if(!t)return inf;
		if(K[t]==x)
			return x;
		if(x>K[t])
			return Large(R[t],x);
		else{
			long r=Large(L[t],x);if(r!=inf)return r;else return K[t];
		}
	}
	
	long Read(void){
		long r;int ch;
		while(ch=getchar(),!isdigit(ch));
		r=ch-'0';
		while(ch=getchar(),isdigit(ch)) r=(r<<1)+(r<<3)+ch-'0';
		return r;
	}

	#define abs(x) ((x)<0?(-(x)):(x))
	void Work(void){
		long long ans=0;
		long Q=Read();
		bool type;Insert(root,-inf);Insert(root,inf);
		while(Q--){
			long flag=Read(),u=Read();

			if(S[root]==2)type=flag, Insert(root,u);else
			if(type==flag) Insert(root,u);else{
			long l1=Small(root,u),l2=Large(root,u);
			if(u-l1<=l2-u)
				ans+=(u-l1),Delete(root,l1);
			else
				ans+=(l2-u),Delete(root,l2);
			}
			ans%=1000000;
		}
		std::cout<<ans<<std::endl;
	}
}
int main(int argc,char** argv){
	//#define Debug
	#ifdef Debug
		freopen("1.in","r",stdin);
		//freopen("1.out","w",stdout);
	#endif
	Solve::Work();
	return 0;
}
