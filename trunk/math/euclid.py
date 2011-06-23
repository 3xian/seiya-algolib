def euclid(a, b, x):
	if b == 0:
		x[0], x[1] = 1, 0
		return a 
	d = euclid(b, a % b, x)
	x[0], x[1] = x[1], x[0] - a / b * x[1]
