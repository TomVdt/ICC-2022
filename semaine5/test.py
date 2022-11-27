
def trier(L):
	n = len(L)
	if n < 3:
		return L

	count = 0
	prev = L[1]
	K = [L[0], L[1]]
	for i in range(2, n):
		new = L[i]
		if new == prev:
			count += 1
		else:
			count = 0
		if count < 2:
			K.append(new)
		prev = new
	return K


print(trier([6, 6, 4, 4, 4, 12, 4, 6]))
