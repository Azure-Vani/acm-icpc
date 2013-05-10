// BEGIN CUT HERE
PROBLEM STATEMENT
Warning: This problem statement contains superscripts and/or subscripts. It may not display properly outside of the applet.


Tomek and Wojtek are going to participate as a team in their local ICPC competition next week. The organizers allow the contestants to bring their own printed materials such as books to the contest site. Their university has some books they could borrow; the i-th of those books weighs books[i] grams. Our heroes would like to have as much material available as possible, however neither of them wishes to be carrying too much weight. Let T be the total weight of books that Tomek will take, and W be the total weight of books that Wojtek will take. Then, Tomek wants to maximize W - T, while Wojtek wants to maximize T - W; if they would have multiple optimal choices, both of them want to maximize T + W as a tie-breaker. The way it will be decided who carries which books to the contest will be as follows:

First, Tomek selects any moves[0] books from the library, and put them in Wojtek's backpack. These will be the books that their team will take to the contest.
Then, Wojtek selects any moves[1] books from his backpack, and moves them to Tomek's backpack.
Then, Tomek selects any moves[2] books from his backpack, and moves them to Wojtek's backpack, and so on...

This process continues for a total of n moves, where n is the number of elements in moves. If there are less than moves[i] books available in the i-th move, the player simply moves all the available books.



You are given a vector <int> books and a vector <int> moves. Return a vector <int> containing exactly two elements, (T, W), with the first element equal to the total weight of books that Tomek will carry, and the second element equal to the total weight of books that Wojtek will carry. Assume that both Tomek and Wojtek make optimal choices during the process described above.


DEFINITION
Class:HeavyBooks
Method:findWeight
Parameters:vector <int>, vector <int>
Returns:vector <int>
Method signature:vector <int> findWeight(vector <int> books, vector <int> moves)


NOTES
-The books may be very heavy.
-The correct return value is always uniquely determined by the problem statement.


CONSTRAINTS
-books will contain between 1 and 50 elements, inclusive.
-Each element of books will be between 1 and 106, inclusive.
-moves will contain between 1 and 50 elements, inclusive.
-Each element of moves will be between 1 and the number of elements in books, inclusive.


EXAMPLES

0)
{5,2,3,1}
{3,2,1,1,1}

Returns: {3, 7 }

The process can go as follows:


First, Tomek will pick books with weights 5, 2 and 3 and put them in Wojtek's backpack.
Wojtek will move the books with weights 5 and 3 to Tomek's backpack.
Tomek will move the book with weight 5 back to Wojtek's backpack.
Wojtek will move the book with weight 5 back to Tomek's backpack.
Finally, Tomek will move the book with weight 5 back to Wojtek's backpack again.


1)
{10, 100, 1000}
{2, 3}

Returns: {110, 0 }

Wojtek has only two books after Tomek's opening move, so he empties his backpack in his move.

2)
{155870,565381}
{1,1,1}

Returns: {0, 565381 }

3)
{500,500,500,500}
{4,1,1,3,2}

Returns: {500, 1500 }

Here, all the books have the same weight.

4)
{1,1,1,1,1000000}
{1}

Returns: {0, 1000000 }



5)
{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
{20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1}

Returns: {110, 100 }



// END CUT HERE

#define OJ

#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <cstdio> 
#include <iterator>
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,r) for(int i = 1; i <= r; i++)
#define REP(i,l,r) for(inti = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

class HeavyBooks {
	public:
	vector <int> findWeight(vector <int> books, vector <int> moves) {
	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {5,2,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,2,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 7 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, findWeight(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {10, 100, 1000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {110, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, findWeight(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {155870,565381}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 565381 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, findWeight(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {500,500,500,500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,1,1,3,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500, 1500 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, findWeight(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1000000 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, findWeight(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {110, 100 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, findWeight(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	HeavyBooks ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE
