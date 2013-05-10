n = int(raw_input())
X = 0
for i in range(0, n):
	x, y = map(int, raw_input().split())
	X -= x - y;
for i in range(0, n):
	x, y = map(int, raw_input().split())
	X += x - y;
print X