n = int(raw_input())
name = [""]
st_ = [[[] for j in range(0, 120)] for i in range(0, 120)]
R = [0 for i in range(0, 1000)]
C = [0 for i in range(0, 1000)]
Ans = ['' for i in range(0, 1000)]
for i in range(1, n + 1):
	t, tmp_name = raw_input().split()
	t = int(t)
	R[i] = t
	name.append(tmp_name)
	for j in range(1, t + 1):
		tmp = raw_input().strip().split(',')
		st_[i][j] = tmp
		C[i] = max(C[i], len(tmp))

for i in range(1, max(R) + 1):
	Ans[i] = ""
	for j in range(1, n + 1):
		if i <= R[j]:
			for k in st_[j][i]:
				Ans[i] += k + ','
		for k in range(1, C[j] - len(st_[j][i]) + 1):
			Ans[i] += ','

for i in range(1, n + 1):
	Ans[0] += name[i] + ','
	for j in range(1, C[i]):
		Ans[0] += ','

for i in range(0, max(R) + 1):
	print Ans[i][0:-1]