for j in range(0, int(raw_input())):
	n = int(raw_input())
	r = 4 * n;
	for i in range(1, n):
		r = (r * 5) % 2007
	print r