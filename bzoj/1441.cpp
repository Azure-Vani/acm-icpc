def gcd(a, b):
	if b:
		return gcd(b, a % b)
	else:
		return a
raw_input()
a = 0;
for i in map(int, raw_input().split()):
	a = gcd(a, abs(i))
print a
