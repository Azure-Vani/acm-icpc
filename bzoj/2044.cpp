class Node:
	def __init__(self):
		self.x = 0
		self.y = 0
		self.z = 0
	
	def Scan(self):
		self.x, self.y, self.z = map(int, raw_input().split())
		
	def __lt__(self, oth):
		return self.x < oth.x and self.y < oth.y and self.z < oth.z

def comp(a, b):
	if a.x < b.x:
		return -1
	else:
		return 1

n = int(raw_input())
a = [Node() for i in range(0, n + 1)]
for i in range(1, n + 1):
	a[i].Scan()

a.sort(key = lambda x: x.x)

f = [0 for i in range(0, n + 1)]
Edge = [[] for i in range(0, n + 1)]
f[1], Ans1 = 1, 1
for i in range(2, n + 1):
	f[i] = 1
	for j in range(1, i):
		if a[j] < a[i]:
			f[i] = max(f[i], f[j] + 1)
			Edge[j].append(i)
	Ans1= max(Ans1, f[i])
print Ans1

vis = [0 for i in range(0, n + 1)]
link = [0 for i in range(0, n + 1)]
cur,cnt = 1, n

def Dfs(u):
	for i in Edge[u]:
		if vis[i] != cur:
			vis[i] = cur
			if link[i] == 0 or Dfs(link[i]):
				link[i] = u
				return True
	return False

for i in range(1, n + 1):
	if Dfs(i):
		cnt -= 1
	cur += 1

print cnt
