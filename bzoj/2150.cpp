#include <cstring>
#include <cstdio>
const long kMAX_ARRAY=2550;
bool map[kMAX_ARRAY][kMAX_ARRAY]={0};long link[kMAX_ARRAY]={0};
bool vis[kMAX_ARRAY]={0};
long n,m,r,c;
 
inline long ID(long x,long y){return x*m+y+1;}
bool Dfs(long u){
        for(long i=1;i<=n*m;i++)
                if(map[u][i]&&!vis[i]){
                        vis[i]=true;
                        if(link[i]==0||Dfs(link[i])){
                                link[i]=u;
                                return true;
                        }
                }
        return false;
}
int main(int argc,char** argv){
        scanf("%ld%ld%ld%ld",&n,&m,&r,&c);
        
        char ch[55][55];
        for(long i=0;i<n;i++)
                scanf("%s",ch[i]);
 
        for(long i=0;i<n;i++)
                for(long j=0;j<m;j++)
                        if(ch[i][j]=='.'){
                                if(i-c>=0&&j+r<m&&ch[i-c][j+r]=='.')
                                        map[ID(i-c,j+r)][ID(i,j)]=true;
                                if(i-c>=0&&j-r>=0&&ch[i-c][j-r]=='.')
                                        map[ID(i-c,j-r)][ID(i,j)]=true;
                                if(i-r>=0&&j-c>=0&&ch[i-r][j-c]=='.')
                                        map[ID(i-r,j-c)][ID(i,j)]=true;
                                if(i-r>=0&&j+c<m&&ch[i-r][j+c]=='.')
                                        map[ID(i-r,j+c)][ID(i,j)]=true;
                        }
        
        long ans=0;
        for(long i=0;i<n;i++)
                for(long j=0;j<m;j++)
                        if(ch[i][j]=='.'){
                                memset(vis,0,sizeof vis);
                                ans+=!Dfs(ID(i,j));
                        }
        printf("%ld\n",ans);
        return 0;
}