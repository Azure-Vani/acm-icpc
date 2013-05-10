n, k = raw_input().split()
n = int(n)
k = int(k)
if (k > (n * (n - 1) // 2)):
	print 0
	exit()
f = [[0 for i in range(0, k + 1)] for i in range(0, n + 1)]
g = [[0 for i in range(0, k + 1)] for i in range(0, n + 1)]
f[1][0], g[1][0] = 1, 1
for i in range(1, k + 1):
	g[1][i] += g[1][i - 1]
for i in range(2, n + 1):
	for j in range(0, k + 1):
		f[i][j] = g[i - 1][j]
		if j - i >= 0:
			f[i][j] = (f[i][j] - g[i - 1][j - i]) % 10000
		g[i][j] = (f[i][j] + g[i][j - 1]) % 10000
if f[n][k] < 0:
	f[n][k] += 10000
print f[n][k]
