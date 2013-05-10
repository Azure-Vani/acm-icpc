def gcd(a, b):
	if b == 0: return a
	return gcd(b, a % b)

T = int(raw_input())
while T != 0:
	T -= 1
	n, k = map(int, raw_input().split())
	if n > k:
		print "0 1"
		continue
	A = k ** n
	B = ((k + 1) ** (n - 1)) * (k + 1 - n)
	g = gcd(A, B)
	A /= g
	B /= g
	print B, A