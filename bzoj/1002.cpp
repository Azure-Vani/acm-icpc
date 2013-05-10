f = [0 for i in range(105)]
f[0] = 1
f[1] = 1
f[2] = 3
n = int(raw_input())
for i in range(3, n + 1):
	f[i] = f[i - 1] * 3 - f[i - 2]
print f[n] * 3 - f[n - 1] * 2 - 2
