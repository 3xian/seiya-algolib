def euclid(a, b):
    if b == 0:
        return a, 1, 0
    d, y, x = euclid(b, a % b)
    return d, x, y-a/b*x
