n, k = map(int, raw_input().split())
s = [0 for i in range(0, n + 5)]
for i in range(1, n + 1):
	s[i] = s[i - 1] + int(raw_input())
f = [0 for i in range(0, n + 5)]
g = [0 for i in range(0, n + 5)]

class Node:
	def __init__(self, a, b):
		self.index = a
		self.value = b

d = [Node(0, 0) for i in range(0, n + 5)]
head, tail = 1, 1

for i in range(1, n + 1):
	while head <= tail and i - d[head].index > k:
		head += 1
	f[i] = s[i] + d[head].value
	g[i] = max(g[i - 1], f[i - 1])

	while head <= tail and g[i] - s[i] >= d[tail].value:
		tail -= 1
	tail += 1
	d[tail] = Node(i, g[i] - s[i])

print max(f[n], g[n])
