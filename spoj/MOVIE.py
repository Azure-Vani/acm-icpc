def gcd(a, b):
	if (b == 0): return a
	else: return gcd(b, a % b)

t = int(raw_input())
while t > 0:
	t -= 1
	st = ""
	while True:
		st = raw_input()
		if st != "": break
	n, k = map(int, st.split())
	if k < n:
		print "1/1"
		continue
	ans = ((k + 1) ** (n - 1)) * (k + 1 - n)
	o = k ** n
	d = gcd(ans, o)
	ans /= d
	o /= d
	print "%d/%d"%(o - ans, o)
