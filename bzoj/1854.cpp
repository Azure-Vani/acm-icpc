//#define Debug
#include <cstdio>
#include <cctype>

#ifdef Debug
	const long delta = 1;
#else
	const long delta = 10000;
#endif
const long MAXN = 100 * delta + 500;
const long BUF = 100 * 10 * delta + 500;
const long MSUM = 10 * delta + 500;
char buf[BUF + 1], *pb = buf;

#define Read(t) {\
		t = 0;\
		while( !isdigit(*pb) )pb++;\
		while( isdigit(*pb) ) t = t * 10 + (*pb) - '0', pb++;\
	}
long n;
struct Edge {
	long y; Edge* next;
	Edge() {}
	Edge(long y, Edge* next) : y(y), next(next) {}
	void* operator new(size_t, void* p) {return p;}
}POOL[MAXN << 1], *a[MAXN + MSUM], *data = POOL;

inline void Add(long y, long x) {
	a[x] = new((void*)data++) Edge(y, a[x]);
}

long r[MAXN] = {0}, hash[MAXN] = {0};

bool find(long u, long flag) {
	for (Edge* p = a[u];p; p = p -> next) {
		long y = p -> y;
		if( hash[y] != flag ) {
			hash[y] = flag;
			if( !r[y] || find(r[y], flag) ) {
				r[y] = u;
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	fread(buf, 1, BUF, stdin);

	Read(n);
	long x, y;
	for (long i = 1; i <= n; i++) {
		Read(x); Read(y);
		Add(i, x + n); Add(i, y + n);
	}
	
	for (long i = 1 + n; i <= 100001 + n; i++) {
		if( !find(i, i) ) {
			printf("%ld\n", i - 1 - n);
			break;
		}
	}
	return 0;
}
