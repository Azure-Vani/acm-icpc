class pair:
	def __init__(self, oth = []):
		if oth:
			self.a = oth
		else:
			self.a = [0 for i in range(0, 10)]
	
	def Output(self):
		for i in self.a:
			print int(i),

	def __add__(self, oth):
		return pair([i+j for (i,j) in zip(self.a, oth)])

def C(l):
	return [(10**(l-1) *  l) for i in range(0, 10)]


l,r = map(int,raw_input().split())
Ans = pair()
while (l <= r):
	p ,pow = 0, 1
	while (True):
		t_pow = pow * 10
		if l + t_pow - 1<= r and not l % t_pow:
			pow = t_pow
			p += 1
		else:
			break
	Ans += C(p)
	t = l / 10 ** p
	while t:
		Ans.a[t%10] += 10 ** p
		t /= 10
	l += pow
Ans.Output()