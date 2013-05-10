/* @title: Matching
 * @source: CEOI '11
 * @state: accepted
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std; 

const int MAX_NUM = 1000000 + 10000; 
const int MAX_N = 1000000 + 10000; 

struct ListNode {
     int v; 
     ListNode *prev, *next; 
}; 

int n, m; 
int P[MAX_N], S[MAX_N]; 
ListNode *vani[MAX_N];
int U[MAX_N], W[MAX_N]; 
pair<int, int> tmp[MAX_N];
vector<int> ans; 

int next[MAX_N];

void doit(void) {
     int j = 0; 
     for (int i=2; i<=n; i++) {
          while (j != 0) {
               int a = i - (j + 1 - U[j + 1]); 
               int b = i - (j + 1 - W[j + 1]); 
               if (!((U[j + 1] == 0 || P[a] < P[i]) && 
                     (W[j + 1] == 0 || P[i] < P[b]))) j = next[j]; 
               else break; 
          }
          int a = i - (j + 1 - U[j + 1]); 
          int b = i - (j + 1 - W[j + 1]);
          if ((U[j + 1] == 0 || P[a] < P[i]) &&
              (W[j + 1] == 0 || P[i] < P[b])) j++; 
          next[i] = j; 
     }

     j = 0; 
     for (int i=1; i<=m; i++) {
          // cout << i << endl; 
          while (j != 0) {
               int a = i - (j + 1 - U[j + 1]); 
               int b = i - (j + 1 - W[j + 1]); 
               if (!((U[j + 1] == 0 || S[a] < S[i]) &&
                     (W[j + 1] == 0 || S[i] < S[b]))) j = next[j]; 
               else break; 
          }
          int a = i - (j + 1 - U[j + 1]); 
          int b = i - (j + 1 - W[j + 1]); 
          if ((U[j + 1] == 0 || S[a] < S[i]) &&
              (W[j + 1] == 0 || S[i] < S[b])) j++; 
          if (j == n) ans.push_back(i - n + 1), j = next[j]; 
     }
}

int get_int(void) {
     int ans = 0; 
     char c; 
     while (!isdigit(c = getchar())) NULL;
     ans += c - '0'; 
     while (isdigit(c = getchar())) ans = ans * 10 + c - '0'; 
     return ans; 
}

int main(void) {
     // freopen("matching.in", "r", stdin);

     scanf("%d%d", &n, &m); 

     for (int i=1; i<=n; i++) {
          int k; k = get_int(); 
          P[k] = i; 
     }

     for (int i=1; i<=m; i++) S[i] = get_int(); 

     for (int i=1; i<=n; i++) {
          tmp[i] = make_pair(P[i], i); 
     }

     sort(tmp + 1, tmp + n + 1);

     for (int i=0; i<=n+1; i++) vani[i] = new ListNode; 

     tmp[0].second = 0; tmp[n + 1].second = n + 1; 

     for (int i=0; i<=n; i++) {
          vani[i]->v = i; 
          vani[tmp[i].second]->next = vani[tmp[i + 1].second]; 
          vani[tmp[i + 1].second]->prev = vani[tmp[i].second];
     }
     vani[n + 1]->v = 0; 

     for (int i=n; i>=1; i--) {
          U[i] = vani[i]->prev->v; 
          W[i] = vani[i]->next->v; 
          vani[i]->prev->next = vani[i]->next; 
          vani[i]->next->prev = vani[i]->prev; 
     }

     doit(); 

     printf("%d\n", ans.size()); 

     for (int i=0; i<ans.size(); i++) {
          printf("%d", ans[i]); 
          if (i == ans.size() - 1) printf("\n"); 
          else printf(" "); 
     }

     return 0;
}
