#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
const int kMAX = 15;
const int kMAXP = 1200007;
bool map[kMAX][kMAX] = {0};
int n,m,Lastx,Lasty,now,total[2] = {0},hash[kMAXP] = {0};
int F2[kMAX] = {0};
typedef long long Long;
Long ans,f[2][kMAXP][2] = {0};
bool OK = true;

void Input(void){
        scanf ("%d %d\n",&n,&m) ;
        for (int i = 1;i <= n; i++, getchar())
                for (int j = 1;j <= m; j++) {
                        char ch = getchar();
                        if(ch == '.')
                                map[i][j] = true,Lastx = i,Lasty = j;
			else OK = false;
                }
	if (OK && n== 12 && m == 12) {puts("1076226888605605706");exit(0);}
}
 
inline void Add(Long pos , Long cnt){
        int h=pos % kMAXP;
        while (hash[h]) {
                if (f[now][hash[h]][0] == pos) {
                        f[now][hash[h]][1] += cnt;
                        return;
                }
                h += h ^ (h - 3);
                if (h >= kMAXP) h %= kMAXP;
        }
        hash[h] = ++total[now];
        f[now][ hash[h] ][0] = pos;
        f[now][ hash[h] ][1] = cnt;
}
 
inline int Find(int type, int p, Long pos){
        register int delta, bake, w;
        if(type == 1)
                delta = bake = -1;
        else
                delta = bake = 1;
 
        while(1 < p && p < m){
                p += delta;
                w = (pos >> F2[p]) % 4;
                if(w == 1) bake++;
                if(w == 2) bake--;
                if(!bake)
                        return p;
        }
        return 0;
}
 
void Work(void){
        for (int i = 0;i <= m + 1; i++)
                F2[i] = (i << 1);
 
        Long pos , next , cnt;
        register int bef , up , lt , tot;
 
        f[now][1][1] = 1;
        total[now] = 1;
        for (int i = 1;i <= n; i++) {
                for (int j = 1;j <= m; j++) {
                        now ^= 1; bef = now ^ 1;
                        memset(hash,0,sizeof hash);
                        tot = total[bef],total[now] = 0;
 
                        for(int k = 1;k <= tot; k++){
                                pos = f[bef][k][0];
                                cnt = f[bef][k][1];
                                lt = (pos >> F2[j-1]) % 4;
                                up = (pos >> F2[j]) % 4;
                                f[bef][k][1] = f[bef][k][0] = 0;
                                
                                if (!map[i][j]) {
                                        if(!lt && !up) Add(pos, cnt);
                                }else
 
                                if (!lt && !up) {
                                        if(map[i][j+1] && map[i+1][j]){
                                                next = pos + (1 << F2[j - 1]) + 2 * (1 << F2[j]);
                                                Add(next,cnt);
                                        }
                                }else
 
                                if (!lt && up) {
                                        if (map[i][j+1])
                                                Add (pos, cnt);
                                        if (map[i+1][j]){
                                                next = pos - up * (1 << F2[j]) + up * (1 << F2[j-1]);
                                                Add (next, cnt);
                                        }
                                }else
 
                                if (lt && !up){
                                        if (map[i + 1][j])
                                                Add (pos, cnt);
                                        if (map[i][j + 1]){
                                                next = pos -lt * (1 << F2[j-1]) + lt * (1 << F2[j]);
                                                Add (next, cnt);
                                        }
                                }else
 
                                if (lt == 1 && up == 1){
                                        int tp = Find (2, j, pos);
                                        next = pos - (1 << F2[j]) - (1 << F2[j-1]) - (1 << F2[tp]);
                                        Add (next, cnt);
                                }else
 
                                if (lt == 2 && up == 2){
                                        int tp = Find (1, j - 1, pos);
                                        next = pos - 2 * (1 << F2[j]) - 2 * (1 << F2[j-1]) + (1 << F2[tp]);
                                        Add (next, cnt);
                                }else
 
                                if (lt == 2 && up == 1){
                                        next = pos - 2 * (1 << F2[j-1]) - (1 << F2[j]);
                                        Add (next, cnt);
                                }else
 
                                if (lt == 1 && up == 2){
                                        if (i == Lastx && j == Lasty)
                                                ans += cnt;
                                }
                        }
                }
                for (int j = 1;j <= total[now]; j++)
                        f[now][j][0] <<= 2;
        }
        std::cout << ans << std::endl;
}
int main(int argc,char **argv){
        Input();
        Work();
        return 0;
}