import static java.util.Arrays.*;
import static java.lang.Math.*;
import java.util.*;
import java.math.*;
import java.io.*;

public class a {

	void solve() throws Exception {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		node[] vs = new node[n];
		for (int i = 0; i < n; i++) {
			vs[i] = new node();
		}
		for (int i = 1; i < n; i++) {
			int x = sc.nextInt(), y = sc.nextInt(); x--; y --;
			vs[x].add(vs[y]);
			vs[y].add(vs[x]);
		}
		vs[0].Dfs(null);
		System.out.println(vs[0].g[0]);
	}

	void debug(Object... a) {
		System.out.println(Arrays.deepToString(a));
	}

	class node extends ArrayList<node> {

		int sum;
		BigInteger [] g;

		void Dfs(node father) {
			sum = 1;
			for (node next: this) if (next != father) {
				next.Dfs(this);
				sum += next.sum;
			}
			g = new BigInteger[sum + 1];
			fill(g, BigInteger.ZERO);
			g[0] = BigInteger.ONE;
			g[1] = BigInteger.ONE;
			for (node next: this) if (next != father) {
				for (int i = sum; i >= 1; --i) {
					BigInteger tmp = g[i];
					for (int j = 1; j <= next.sum; ++j) g[i] = g[i].max(next.g[j].multiply(tmp));
					for (int j = 1; j <= min(i - 1, next.sum); ++j) {
						g[i] = g[i].max(g[i - j].divide(BigInteger.valueOf(i - j)).multiply(BigInteger.valueOf(i)).multiply(next.g[j]).divide(BigInteger.valueOf(j)));
					}
				}
			}
		}
	}


	class Scanner {
		BufferedReader br;
		StringTokenizer st;
		Scanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(in));
			eat("");
		}
		void eat(String s) {
			st = new StringTokenizer(s);
		}
		String nextLine() {
			try {
				return br.readLine();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		boolean hasNext() {
			while (!st.hasMoreTokens()) {
				String s = nextLine();
				if (s == null) return false;
				eat(s);
			}
			return true;
		}
		String next() {
			hasNext();
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		long nextLong() {
			return Long.parseLong(next());
		}
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}

	static void Freopen() {
		try {
			System.setIn(new FileInputStream("in"));
		} catch (Throwable e) {
			return;
		}
	}

	public static void main(String[] args) throws Exception {
		Freopen();
		new a().solve();
	}
}

