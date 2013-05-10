import sys
def OK(a, b):
	if (a == 'C' and b == 'G') or (a == 'G' and b == 'C'): return True
	if (a == 'A' and b == 'T') or (a == 'T' and b == 'A'): return True
	return False
n, m = map(int, raw_input().split())
s1 = "." + raw_input()
s2 = "." + raw_input()
f = [[0 for i in range(0, 2012)] for j in range(0, 2)]
f[1][0] = 1
for i in range(1, n + 1):
	now = i % 2
	last = (i + 1) % 2
	f[last][0] = 1
	for j in range(1, m + 1):
		f[now][j] = f[last][j]
		if (OK(s1[i], s2[j])):
			f[now][j] += f[last][j - 1]

print f[n % 2][m]