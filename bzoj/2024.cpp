n,k = map(int, raw_input().split())
a = [0]
b = [0]
for i in range(1, n + 1):
	b.append(int(raw_input()))
	b[i] += b[i] + 1
for i in range(1, n + 1):
	a.append(int(raw_input()))
	a[i] *= 2
a.sort()
b.sort()
f = [[0 for i in range(0, 255)] for i in range(0, 255)]
f[0][0] = 1
s = [0 for i in range(0, 255)]
t = [0 for i in range(0, 255)]
for i in range(1, n + 1):
	for j in range(1, i + 1):
		if a[j] > b[i]: s[i] += 1
		if b[j] > a[i]: t[i] += 1
for i in range(1, n + 1):
	for j in range(0, i + 1):
		if a[i] > b[i]:
			f[i][j] += f[i - 1][j - 1] * (s[i] + i - j) if j > 0 and s[i] + i - j > 0 else 0
			f[i][j] += f[i - 1][j] * (j - s[i] + 1) if j - s[i] + 1 > 0 else 0
		else:
			f[i][j] += f[i - 1][j - 1] * (i - j - t[i] + 1) if j > 0 and i - j - t[i] + 1 > 0 else 0
			f[i][j] += f[i - 1][j] * (j + t[i]) if j + t[i] > 0 else 0
ret = 0
for i in range(0, k + 1): ret += f[n][i]
print ret